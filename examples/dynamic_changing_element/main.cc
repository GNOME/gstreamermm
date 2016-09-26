/*
 * main.cc
 *
 *  Created on: Aug 14, 2013
 *      Author: m.kolny
 *
 *      based on sample described here: http://gstreamer.freedesktop.org/data/doc/gstreamer/head/manual/html/section-dynamic-pipelines.html
 */

#include <gstreamermm.h>
#include <glibmm/main.h>
#include <iostream>
#include <vector>

using namespace Gst;
using Glib::RefPtr;

RefPtr<Pad> blockpad;
RefPtr<Element> conv_before,
conv_after,
curr_effect;
RefPtr<Pipeline> pipeline;
std::vector<Glib::ustring> effects = {"identity", "exclusion",
		"navigationtest", "agingtv", "videoflip", "vertigotv",
		"gaussianblur", "shagadelictv", "edgetv"};
int curr_position = 0;

RefPtr<Glib::MainLoop> main_loop;

PadProbeReturn event_probe_cb (const RefPtr<Pad>& pad, const PadProbeInfo& info)
{
	RefPtr<Event> event = info.get_event();
	if (event->get_event_type()!= EVENT_EOS)
		return PAD_PROBE_OK;

	pad->remove_probe(info.get_id());

	curr_effect->set_state(STATE_NULL);
	pipeline->remove(curr_effect);
	curr_effect = ElementFactory::create_element(effects[curr_position++ % effects.size()]);
	pipeline->add(curr_effect);
	conv_before->link(curr_effect)->link(conv_after);
	curr_effect->set_state(STATE_PLAYING);

	return PAD_PROBE_DROP;
}

PadProbeReturn pad_probe_cb(const RefPtr<Pad>& pad, const PadProbeInfo& info)
{
	pad->remove_probe(info.get_id());

	RefPtr<Pad> srcpad = curr_effect->get_static_pad("src");
	srcpad->add_probe(PAD_PROBE_TYPE_BLOCK | PAD_PROBE_TYPE_EVENT_DOWNSTREAM, sigc::ptr_fun(event_probe_cb));
	RefPtr<Pad> sinkpad = curr_effect->get_static_pad("sink");
	sinkpad->send_event(EventEos::create());
	return PAD_PROBE_OK;
}

bool on_bus_message(const Glib::RefPtr<Gst::Bus>&,
                    const Glib::RefPtr<Gst::Message>& message)
{
	switch (message->get_message_type())
	{
		case MESSAGE_ERROR:
			std::cerr << "Error." << std::endl;
			main_loop->quit();
			return false;
		default:
			break;
	}

	return true;
}
bool on_timeout()
{
	blockpad->add_probe(PAD_PROBE_TYPE_BLOCK_DOWNSTREAM, sigc::ptr_fun(&pad_probe_cb));
	return true;
}

int main(int argc, char** argv)
{
	init(argc, argv);
	main_loop = Glib::MainLoop::create();

	pipeline = Pipeline::create("effects-pipeline");

	RefPtr<Element> src = ElementFactory::create_element("videotestsrc"),
			sink = ElementFactory::create_element("xvimagesink");

	conv_before = ElementFactory::create_element("videoconvert");
	curr_effect = ElementFactory::create_element(effects[curr_position++]);
	conv_after = ElementFactory::create_element("videoconvert");

	blockpad = src->get_static_pad("src");
	src->property("is-live", true);

	pipeline->add(src)->add(conv_before)->add(curr_effect)->add(conv_after)->add(sink);
	src->link(conv_before)->link(curr_effect)->link(conv_after)->link(sink);

	RefPtr<Bus> bus = pipeline->get_bus();
	bus->add_watch(sigc::ptr_fun(on_bus_message));

	pipeline->set_state(STATE_PLAYING);

	Glib::signal_timeout().connect(sigc::ptr_fun(&on_timeout), 1000);
	main_loop->run();

	pipeline->set_state(STATE_NULL);

	return 0;
}



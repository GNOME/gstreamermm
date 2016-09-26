/*
 * main.cc
 *
 *  Created on: Aug 19, 2013
 *      Author: m.kolny
 */
#include <gstreamermm.h>
#include <glibmm/main.h>
#include <iostream>

using namespace Gst;
using Glib::RefPtr;

RefPtr<Element> src;
RefPtr<Element> convert;
RefPtr<Pipeline> pipeline;
RefPtr<Glib::MainLoop> main_loop;

bool on_timeout()
{
	static int pattern = 0;
	src->set_state(STATE_NULL);
	pipeline->remove(src);
	src = ElementFactory::create_element("videotestsrc");
	pattern = (pattern == 0) ? 18 : 0;
	src->property("pattern",  pattern);
	pipeline->add(src);
	src->link(convert);
	src->set_state(STATE_PLAYING);

	return true;
}

int main(int argc, char** argv)
{
	if (argc < 2)
	{
		std::cout << "Usage: " << argv[0] << " <avi output filename>" << std::endl;
		return 1;
	}

	init(argc, argv);
	main_loop = Glib::MainLoop::create();

	pipeline = Pipeline::create("effects-pipeline");

	if (!pipeline)
	{
		std::cout << "Cannot create pipeline element." << std::endl;
		return 1;
	}

	RefPtr<Element> queue1 = ElementFactory::create_element("queue"),
			queue2 = ElementFactory::create_element("queue"),
			tee = ElementFactory::create_element("tee"),
			autosink = ElementFactory::create_element("autovideosink"),
			sink = ElementFactory::create_element("filesink"),
			muxer = ElementFactory::create_element("avimux");

	src = ElementFactory::create_element("videotestsrc");
	src->property<int>("num-buffers", 100);
	sink->property<Glib::ustring>("location", argv[1]);
	convert = ElementFactory::create_element("videoconvert");

	if (!queue1 || !queue2 || !tee || !autosink ||
			!sink || !muxer || !src || !sink || !convert)
	{
		std::cout << "Cannot create one of the elements." << std::endl;
		return 1;
	}

	try
	{
		pipeline->add(src)->add(convert)->add(tee)->add(queue1)
				->add(autosink)->add(queue2)->add(muxer)->add(sink);

		src->link(convert)->link(tee)->link(queue1)->link(autosink);
		tee->link(queue2)->link(muxer)->link(sink);
	}
	catch (const std::exception& ex)
	{
		std::cout << "Exception occured during preparing pipeline. Message: " << ex.what() << std::endl;
		return 1;
	}

	pipeline->set_state(STATE_PLAYING);

	Glib::signal_timeout().connect(sigc::ptr_fun(&on_timeout), 2000);
	main_loop->run();

	pipeline->set_state(STATE_NULL);

  return 0;
}





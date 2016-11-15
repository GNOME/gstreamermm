/*
 * utils.cc
 *
 *  Created on: Aug 5, 2013
 *      Author: m.kolny
 */

#include <gstreamermm.h>
#include <gstreamermm/videotestsrc.h>
#include <gstreamermm/filesink.h>
#include <glibmm/main.h>
#include "utils.h"

using Glib::RefPtr;
using namespace Gst;
using namespace std;

RefPtr<Glib::MainLoop> utils_mainloop;

bool utils_on_bus_message(const RefPtr<Bus>&, const Glib::RefPtr<Message>& message)
{
  switch(message->get_message_type())
  {
  case Gst::MESSAGE_EOS:
    utils_mainloop->quit();
    return false;
  case Gst::MESSAGE_ERROR:
    utils_mainloop->quit();
    return false;
  default:
    break;
  }

  return true;
}

void GenerateSampleOggFile(int num_buffers, const Glib::ustring& filename)
{
  RefPtr<Pipeline> pipeline = Pipeline::create("create-ogg");
  RefPtr<Element> source = ElementFactory::create_element("videotestsrc", "testsource");
  RefPtr<Element> encoder = ElementFactory::create_element("theoraenc"),
      muxer = ElementFactory::create_element("oggmux");
  RefPtr<Element> sink = ElementFactory::create_element("filesink", "fsink");
    //RefPtr<Element> sink = ElementFactory::create_element("xvimagesink");

  Glib::RefPtr<Gst::Bus> bus = pipeline->get_bus();
  bus->add_watch(sigc::ptr_fun(&utils_on_bus_message));

  utils_mainloop = Glib::MainLoop::create();

  pipeline->add(source)->add(encoder)->add(muxer)->add(sink);

  source->set_property("num_buffers", num_buffers);
  sink->set_property("location", filename);

  muxer->link(sink);
  source->link(encoder);
  encoder->link(muxer);

  pipeline->set_state(Gst::STATE_PLAYING);

  utils_mainloop->run();
  pipeline->set_state(Gst::STATE_NULL);
}

bool FilesEqual(const string& filename1, const string& filename2)
{
  std::ifstream f1(filename1, ios::binary),
        f2(filename2, ios::binary);

  string buf(istreambuf_iterator<char>(f1),
             (istreambuf_iterator<char>()));

  return equal(buf.begin(), buf.end(),
            string(istreambuf_iterator<char>(f2),
                    (istreambuf_iterator<char>())).begin());
}

/*
 * test-integration-videoduration.cc
 *
 *  Created on: Aug 5, 2013
 *      Author: m.kolny
 */

#include "mmtest.h"
#include <gstreamermm.h>
#include <glibmm/main.h>
#include "utils.h"

using namespace Gst;
using Glib::RefPtr;

RefPtr<Glib::MainLoop> mainloop;
RefPtr<Element> decoder;
RefPtr<Gst::Pipeline> pipeline;

bool on_bus_message(const RefPtr<Bus>&, const Glib::RefPtr<Message>& message)
{
  switch(message->get_message_type())
  {
  case Gst::MESSAGE_EOS:
    mainloop->quit();
    return false;
  case Gst::MESSAGE_ERROR:
    mainloop->quit();
    return false;
  default:
    break;
  }

  return true;
}

void on_pad_added(const Glib::RefPtr<Gst::Pad>& newPad)
{
  RefPtr<Gst::Pad> sinkPad = decoder->get_static_pad("sink");
  PadLinkReturn ret = newPad->link(sinkPad);

  MM_ASSERT_TRUE(PAD_LINK_OK == ret || PAD_LINK_WAS_LINKED == ret);
}


bool on_timeout()
{
  gint64 len;

  if (pipeline->query_duration(FORMAT_TIME, len))
  {
    EXPECT_EQ(333333333, len);
    return FALSE;
  }

  return TRUE;
}

TEST(IntegrationVideodurationTest, CreateVideoAndCheckDuration)
{
  Glib::ustring input_filename = "videoduration-test.ogg";

  GenerateSampleOggFile(10, input_filename);

  RefPtr<Element> filesrc = Gst::ElementFactory::create_element("filesrc");
  MM_ASSERT_TRUE(filesrc);

  filesrc->set_property("location", input_filename);

  mainloop = Glib::MainLoop::create();
  pipeline = Pipeline::create("rewriter");
  RefPtr<Element> sink = ElementFactory::create_element("fakesink"),
        demuxer = ElementFactory::create_element("oggdemux");
  decoder = ElementFactory::create_element("theoradec");
  MM_ASSERT_TRUE(sink);
  MM_ASSERT_TRUE(demuxer);
  MM_ASSERT_TRUE(decoder);

  RefPtr<Bus> bus = pipeline->get_bus();
  bus->add_watch(sigc::ptr_fun(&on_bus_message));

  pipeline->add(filesrc)->add(demuxer)->add(decoder)->add(sink);
  filesrc->link(demuxer);
  decoder->link(sink);

  demuxer->signal_pad_added().connect(sigc::ptr_fun(&on_pad_added));

  pipeline->set_state(Gst::STATE_PLAYING);
  Glib::signal_timeout().connect(sigc::ptr_fun(&on_timeout), 0);
  mainloop->run();

  pipeline->set_state(Gst::STATE_NULL);

  remove(input_filename.c_str());
}

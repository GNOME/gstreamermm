/*
 * test-integration-seekonstartup.cc
 *
 *  Created on: 5 sie 2013
 *      Author: loganek
 */

#include "mmtest.h"
#include <gstreamermm.h>
#include <gstreamermm/fakesink.h>
#include <glibmm/main.h>
#include "utils.h"

using namespace Gst;
using Glib::RefPtr;

RefPtr<Glib::MainLoop> mainloop;
RefPtr<Bus> bus;
RefPtr<Pipeline> pipeline;
RefPtr<Pad> sink_pad;
static gint counter;
bool prerolled = false;
gboolean was_check = 0;

bool on_timeout()
{
  gint64 pos;

  if (pipeline->query_position(FORMAT_TIME, pos))
  {
    EXPECT_EQ(2000000000, pos);
    g_atomic_int_set(&was_check, 1);
    was_check = true;

    return FALSE;
  }

  return TRUE;
}

void dec_counter()
{
  if (prerolled)
    return;

  if (g_atomic_int_dec_and_test (&counter))
  {
    prerolled = true;
    bus->post(MessageApplication::create(pipeline, Structure("empty")));
  }
}

PadProbeReturn cb_blocked (const RefPtr <Pad>& /* pad */, const PadProbeInfo& /* info */)
{
  if (prerolled)
    return PAD_PROBE_REMOVE;

  dec_counter();

  return PAD_PROBE_OK;
}

bool on_bus_message(const RefPtr<Bus>&, const Glib::RefPtr<Message>& message)
{
  switch(message->get_message_type())
  {
  case MESSAGE_EOS:
    mainloop->quit();
    return false;
  case MESSAGE_ERROR:
    mainloop->quit();
    return false;
  case GST_MESSAGE_APPLICATION:
    pipeline->seek(1.0, FORMAT_TIME,
                   (SeekFlags)(SEEK_FLAG_FLUSH | SEEK_FLAG_ACCURATE),
                   SEEK_TYPE_SET, 2 * SECOND,
                   SEEK_TYPE_SET, 3 * SECOND);
    pipeline->set_state(STATE_PLAYING);
    break;
  default:
    break;
  }

  return true;
}

void on_pad_added(const RefPtr<Pad>& newPad)
{
  if (prerolled)
    return;

  g_atomic_int_inc(&counter);

  newPad->add_probe(PAD_PROBE_TYPE_BLOCK_DOWNSTREAM, sigc::ptr_fun(&cb_blocked));

  PadLinkReturn ret = newPad->link(sink_pad);

  MM_ASSERT_TRUE(PAD_LINK_OK == ret || PAD_LINK_WAS_LINKED == ret);
}

void no_more_pads()
{
  if (prerolled)
    return;

  dec_counter();
}

TEST(IntegrationSeekOnStartupTest, SeekToPositionWhenPipelineStarts)
{
  Glib::ustring input_filename = "seek-on-startup-test.ogg";

  GenerateSampleOggFile(100, input_filename);

  mainloop = Glib::MainLoop::create();
  pipeline = Pipeline::create("seekonstartup-pipeline");
  MM_ASSERT_TRUE(pipeline);
  bus = pipeline->get_bus();
  MM_ASSERT_TRUE(bus);
  bus->add_watch(sigc::ptr_fun(&on_bus_message));

  RefPtr<Element> src = ElementFactory::create_element("uridecodebin"),
      csp = ElementFactory::create_element("videoconvert"),
      vs = ElementFactory::create_element("videoscale"),
      sink = ElementFactory::create_element("ximagesink");

  MM_ASSERT_TRUE(src);
  MM_ASSERT_TRUE(csp);
  MM_ASSERT_TRUE(vs);
  MM_ASSERT_TRUE(sink);

  ASSERT_NO_THROW(src->set_property("uri", URIHandler::filename_to_uri(input_filename)));

  ASSERT_NO_THROW(pipeline->add(src)->add(csp)->add(vs)->add(sink));
  ASSERT_NO_THROW(csp->link(vs)->link(sink));

  sink_pad = csp->get_static_pad("sink");

  g_atomic_int_set(&counter, 1);

  src->signal_pad_added().connect(sigc::ptr_fun(&on_pad_added));
  src->signal_no_more_pads().connect(sigc::ptr_fun(&no_more_pads));

  pipeline->set_state(STATE_PAUSED);

  Glib::signal_timeout().connect(sigc::ptr_fun(&on_timeout), 0);
  mainloop->run();

  pipeline->set_state(Gst::STATE_NULL);

  MM_ASSERT_TRUE(was_check);

  remove(input_filename.c_str());
}

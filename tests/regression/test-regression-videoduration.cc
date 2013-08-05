/*
 * test-regression-videoduration.cc
 *
 *  Created on: Aug 5, 2013
 *      Author: m.kolny
 */

#include <gtest/gtest.h>
#include <gstreamermm.h>
#include <gstreamermm/fakesink.h>
#include <glibmm.h>
#include "utils.h"

using namespace Gst;
using Glib::RefPtr;

RefPtr<Glib::MainLoop> mainloop;

bool on_bus_message(const RefPtr<Bus>&, const Glib::RefPtr<Message>& message)
{
    switch(message->get_message_type())
    {
        case Gst::MESSAGE_EOS:
            mainloop->quit();
            return false;
        case Gst::MESSAGE_ERROR:
        {
            mainloop->quit();
            return false;
        }
        default:
            break;
    }

    return true;
}

static void
on_pad_added (GstElement *element,
              GstPad     *pad,
              gpointer    data)
{
    GstPad *sinkpad;
    GstElement *decoder = (GstElement *) data;

    sinkpad = gst_element_get_static_pad (decoder, "sink");

    gst_pad_link (pad, sinkpad);

    gst_object_unref (sinkpad);
}


static gboolean
cb_print_position (GstElement *pipeline)
{
    gint64 len;

    if (gst_element_query_duration (pipeline, GST_FORMAT_TIME, &len))
    {
        EXPECT_EQ(333333333, len);
        return FALSE;
    }

    return TRUE;
}

TEST(RegressionVideodurationTest, CreateVideoAndCheckDuration)
{
    Glib::ustring input_filename = "test.ogg";

    GenerateSampleOggFile(10, input_filename);

    Glib::RefPtr<Gst::Pipeline> pipeline;
    RefPtr<FileSrc> filesrc = Gst::FileSrc::create();
    ASSERT_TRUE(filesrc);

    filesrc->property_location() = input_filename;

    mainloop = Glib::MainLoop::create();
    pipeline = Pipeline::create("rewriter");
    RefPtr<Element> sink = ElementFactory::create_element("fakesink"),
            demuxer = ElementFactory::create_element("oggdemux"),
            decoder = ElementFactory::create_element("theoradec");
    ASSERT_TRUE(sink);
    ASSERT_TRUE(demuxer);
    ASSERT_TRUE(decoder);

    RefPtr<Bus> bus = pipeline->get_bus();
    bus->add_watch(sigc::ptr_fun(&on_bus_message));

    pipeline->add(filesrc)->add(demuxer)->add(decoder)->add(sink);
    filesrc->link(demuxer);
    decoder->link(sink);
    g_signal_connect (demuxer->gobj(), "pad-added", G_CALLBACK(on_pad_added), decoder->gobj());

    pipeline->set_state(Gst::STATE_PLAYING);
    g_timeout_add(0, (GSourceFunc) cb_print_position, pipeline->gobj());
    mainloop->run();

    pipeline->set_state(Gst::STATE_NULL);

    remove(input_filename.c_str());
}



/*
 * test-plugin-appsink.cc
 *
 *  Created on: 5 sie 2013
 *      Author: loganek
 */

#include <gtest/gtest.h>
#include <gstreamermm.h>
#include <gstreamermm/appsink.h>
#include <gstreamermm/appsrc.h>

using namespace Gst;
using Glib::RefPtr;

class AppSinkPluginTest : public ::testing::Test
{
protected:
    RefPtr<Element> source;
    RefPtr<Element> sink;
    RefPtr<Pipeline> pipeline;

    void CreatePipelineWithElements()
    {
        sink = Gst::ElementFactory::create_element("appsink", "sink");
        source = ElementFactory::create_element("appsrc", "source");

        ASSERT_TRUE(sink);
        ASSERT_TRUE(source);

        ASSERT_NO_THROW(pipeline->add(source)->add(sink));
        ASSERT_NO_THROW(source->link(sink));
    }
};

TEST_F(AppSinkPluginTest, CreatePipelineWithAppsink)
{
    CreatePipelineWithElements();
}

TEST_F(AppSinkPluginTest, UseAppSinkDuringDataFlowInPipeline)
{
    sink = Gst::ElementFactory::create_element("appsink", "sink");
    RefPtr<AppSink> appsink = appsink.cast_static(sink);
    source = ElementFactory::create_element("appsrc", "source");
    RefPtr<AppSrc> appsrc = appsrc.cast_static(source);
    pipeline->add(source)->add(sink);
    source->link(sink);

    pipeline->set_state(STATE_PLAYING);

    std::string data = "hello world";
    RefPtr<Buffer> buf = Buffer::create(data.length() + 1);

    RefPtr<MapInfo> map_info(new MapInfo());
    buf->map(map_info, MAP_WRITE);
    strcpy((char *)map_info->get_data(), data.c_str());
    buf->unmap(map_info);

    appsrc->push_buffer(buf);

    {
        State state;
        StateChangeReturn ret = pipeline->get_state(state, state, 1*Gst::SECOND);
        ASSERT_EQ(STATE_CHANGE_SUCCESS, ret);
   }

    RefPtr<Buffer> buf_out;
    RefPtr<Sample> sample = appsink->pull_sample();
    ASSERT_TRUE(sample);
    buf_out = sample->get_buffer();
    ASSERT_TRUE(buf_out);

    buf_out->map(map_info, MAP_READ);
    assert(std::string((char *)map_info->get_data()) == data);
    buf_out->unmap(map_info);

     appsrc->end_of_stream();

     RefPtr<Message> msg = pipeline->get_bus()->poll((MessageType)(MESSAGE_EOS | MESSAGE_ERROR) , 1*SECOND);
     ASSERT_TRUE(msg);
     ASSERT_EQ(MESSAGE_EOS, msg->get_message_type());

     pipeline->set_state(STATE_NULL);
}





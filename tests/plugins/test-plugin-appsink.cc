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
        pipeline = Gst::Pipeline::create();

        source = ElementFactory::create_element("appsrc", "source");
        sink = ElementFactory::create_element("appsink", "sink");

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
    CreatePipelineWithElements();
    RefPtr<AppSink> appsink = appsink.cast_static(sink);
    RefPtr<AppSrc> appsrc = appsrc.cast_static(source);

    pipeline->set_state(STATE_PLAYING);

    std::string data = "hello world";
    RefPtr<Buffer> buf = Buffer::create(data.length() + 1);

    RefPtr<MapInfo> map_info(new MapInfo());
    buf->map(map_info, MAP_WRITE);
    strcpy((char *)map_info->get_data(), data.c_str());
    buf->unmap(map_info);

    appsrc->push_buffer(buf);

    RefPtr<Buffer> buf_out;
    RefPtr<Sample> sample = appsink->pull_sample();
    ASSERT_TRUE(sample);
    buf_out = sample->get_buffer();
    ASSERT_TRUE(buf_out);

    ASSERT_TRUE(buf_out->memcmp(0, data.c_str(), data.length()) == 0);

    appsrc->end_of_stream();

    RefPtr<Message> msg = pipeline->get_bus()->poll((MessageType)(MESSAGE_EOS | MESSAGE_ERROR) , 1*SECOND);
    ASSERT_TRUE(msg);
    ASSERT_EQ(MESSAGE_EOS, msg->get_message_type());

    pipeline->set_state(STATE_NULL);
}





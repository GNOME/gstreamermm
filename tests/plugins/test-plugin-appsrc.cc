/*
 * test-plugin-appsrc.cc
 *
 *  Created on: Aug 1, 2013
 *      Author: m.kolny
 */

#include <gtest/gtest.h>
#include <gstreamermm.h>
#include <gstreamermm/appsrc.h>

using namespace Gst;
using Glib::RefPtr;

class AppSrcPluginTest : public ::testing::Test
{
protected:
    RefPtr<Element> source_element;
    RefPtr<Pipeline> pipeline;

    void CreatePipelineWithElements()
    {
        pipeline = Gst::Pipeline::create();

        RefPtr<Element> sink = Gst::ElementFactory::create_element("fakesink", "sink");
        source_element = ElementFactory::create_element("appsrc", "source");

        ASSERT_TRUE(sink);
        ASSERT_TRUE(source_element);

        ASSERT_NO_THROW(pipeline->add(source_element)->add(sink));
        ASSERT_NO_THROW(source_element->link(sink));
    }
};

TEST_F(AppSrcPluginTest, CorrectCreatedAppSrcElement)
{
    RefPtr<AppSrc> source = AppSrc::create("source");
    ASSERT_TRUE(source);

    source_element = ElementFactory::create_element("appsrc", "source");
    ASSERT_TRUE(source_element);

    source = source.cast_dynamic(source_element);
    ASSERT_TRUE(source);
}

TEST_F(AppSrcPluginTest, CreatePipelineWithAppSrcElement)
{
    CreatePipelineWithElements();
}

TEST_F(AppSrcPluginTest, SimpleDataFlowInPipelineWitAppSrcElement)
{
    CreatePipelineWithElements();

    pipeline->set_state(Gst::STATE_PLAYING);

    std::string data = "hello world";
    RefPtr<Buffer> buf = Buffer::create(data.length() + 1);
    RefPtr<MapInfo> mapinfo(new Gst::MapInfo());
    buf->map(mapinfo, MAP_WRITE);
    strcpy((char *)mapinfo->get_data(), data.c_str());

    RefPtr<AppSrc> appsrc;
    appsrc = appsrc.cast_dynamic(source_element);
    appsrc->push_buffer(buf);

    {
        State state;
        StateChangeReturn ret=pipeline->get_state(state, state, 1*SECOND);
        ASSERT_EQ(ret, STATE_CHANGE_SUCCESS);
    }

    appsrc->end_of_stream();

    RefPtr<Gst::Message> msg = pipeline->get_bus()->poll((Gst::MessageType)(Gst::MESSAGE_EOS | Gst::MESSAGE_ERROR) , 1*Gst::SECOND);
    ASSERT_TRUE(msg);
    ASSERT_EQ(msg->get_message_type(), Gst::MESSAGE_EOS);
    pipeline->set_state(Gst::STATE_NULL);
}


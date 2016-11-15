/*
 * test-plugin-appsrc.cc
 *
 *  Created on: Aug 1, 2013
 *      Author: m.kolny
 */

#include "mmtest.h"
#include <gstreamermm.h>

#ifndef GSTREAMERMM_DISABLE_DEPRECATED

#include <gstreamermm/appsrc.h>

using namespace Gst;
using Glib::RefPtr;

class AppSrcPluginTest : public ::testing::Test
{
protected:
  RefPtr<Element> source;
  RefPtr<Element> sink;
  RefPtr<Pipeline> pipeline;

  void CreatePipelineWithElements()
  {
    pipeline = Gst::Pipeline::create();

    sink = ElementFactory::create_element("fakesink", "sink");
    source = ElementFactory::create_element("appsrc", "source");

    MM_ASSERT_TRUE(sink);
    MM_ASSERT_TRUE(source);

    ASSERT_NO_THROW(pipeline->add(source)->add(sink));
    ASSERT_NO_THROW(source->link(sink));
  }
};

TEST_F(AppSrcPluginTest, CorrectCreatedAppSrcElement)
{
  RefPtr<AppSrc> source = AppSrc::create("source");
  MM_ASSERT_TRUE(source);

  RefPtr<Element> source_element = ElementFactory::create_element("appsrc", "source");
  MM_ASSERT_TRUE(source_element);

  source = source.cast_dynamic(source_element);
  MM_ASSERT_TRUE(source);
}

TEST_F(AppSrcPluginTest, CreatePipelineWithAppSrcElement)
{
  CreatePipelineWithElements();
}

TEST_F(AppSrcPluginTest, SrcPadQueryCapsShouldReturnProperCapsObjects)
{
  CreatePipelineWithElements();

  RefPtr<BaseSrc> basesrc;
  basesrc = basesrc.cast_dynamic(source);
  MM_ASSERT_TRUE(basesrc);

  RefPtr<Pad> src_pad = basesrc->get_src_pad();
  MM_ASSERT_TRUE(src_pad);
  MM_ASSERT_TRUE(GST_IS_PAD(src_pad->gobj()));
  RefPtr<Caps> caps = src_pad->query_caps(Caps::create_any());
  MM_ASSERT_TRUE(caps);
  MM_ASSERT_TRUE(caps->gobj());
  MM_ASSERT_TRUE(GST_IS_CAPS(caps->gobj()));
  RefPtr<Caps> template_caps = Glib::wrap(gst_pad_get_pad_template_caps(src_pad->gobj()), false);

  src_pad.reset();
  basesrc.reset();
  sink.reset();
  pipeline.reset();

  // query_caps may return just another ref to template_caps
  if (caps == template_caps)
  {
    // ...but template_caps might be just another ref to static caps with some higher unknown refcount
    //EXPECT_EQ(2, caps->get_refcount());
  }
  else
  {
    EXPECT_EQ(1, caps->get_refcount());
  }
}

TEST_F(AppSrcPluginTest, SimpleDataFlowInPipelineWithAppSrcElement)
{
  CreatePipelineWithElements();

  EXPECT_EQ(STATE_CHANGE_ASYNC, pipeline->set_state(STATE_PLAYING));

  std::string data = "hello world";
  RefPtr<Buffer> buf = Buffer::create(data.length() + 1);
  MM_ASSERT_TRUE(buf);
  MapInfo mapinfo;
  MM_ASSERT_TRUE(buf->map(mapinfo, MAP_WRITE));
  strcpy((char *)mapinfo.get_data(), data.c_str());

  RefPtr<AppSrc> appsrc;
  appsrc = appsrc.cast_dynamic(source);
  MM_ASSERT_TRUE(appsrc);

  EXPECT_EQ(FLOW_OK, appsrc->push_buffer(buf));

  {
    State state, pending;
    StateChangeReturn ret = pipeline->get_state(state, pending, 1*SECOND);
    EXPECT_EQ(STATE_CHANGE_SUCCESS, ret);
    EXPECT_EQ(STATE_PLAYING, state);
  }

  EXPECT_EQ(FLOW_OK, appsrc->end_of_stream());

  RefPtr<Message> msg = pipeline->get_bus()->poll((MessageType)(MESSAGE_EOS | MESSAGE_ERROR) , 1*SECOND);
  MM_ASSERT_TRUE(msg);
  EXPECT_EQ(MESSAGE_EOS, msg->get_message_type());
  EXPECT_EQ(STATE_CHANGE_SUCCESS, pipeline->set_state(STATE_NULL));
}

#endif

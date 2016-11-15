#include <gstreamermm.h>

#ifndef GSTREAMERMM_DISABLE_DEPRECATED

#include "mmtest.h"
#include <gstreamermm/appsrc.h>
#include <gstreamermm/appsink.h>

#include "derivedfromappsink.h"

using namespace Gst;
using Glib::RefPtr;

class DerivedFromAppSinkPluginTest : public ::testing::Test
{
protected:
  RefPtr<Element> source;
  RefPtr<Element> sink;
  RefPtr<Pipeline> pipeline;

  void CreatePipelineWithElements()
  {
    pipeline = Gst::Pipeline::create();

    sink = ElementFactory::create_element("derivedfromappsink", "sink");
    source = ElementFactory::create_element("appsrc", "source");

    MM_ASSERT_TRUE(sink);
    MM_ASSERT_TRUE(source);

    ASSERT_NO_THROW(pipeline->add(source)->add(sink));
    ASSERT_NO_THROW(source->link(sink));
  }

  virtual void SetUp()
  {
    Plugin::register_static(GST_VERSION_MAJOR, GST_VERSION_MINOR, "derivedfromappsink",
        "derivedfromappsink is an example of C++ element derived from Gst::AppSink",
        sigc::ptr_fun(&DerivedFromAppSink::register_element), "0.123",
        "LGPL", "source?", "package?", "http://example.com");
  }
};

TEST_F(DerivedFromAppSinkPluginTest, CreateRegisteredElement)
{
  RefPtr<Element> sink_element = ElementFactory::create_element("derivedfromappsink", "source");

  MM_ASSERT_TRUE(sink_element);
}

TEST_F(DerivedFromAppSinkPluginTest, CreatePipelineWithRegisteredElement)
{
  CreatePipelineWithElements();
}

TEST_F(DerivedFromAppSinkPluginTest, SinkPadQueryCapsShouldReturnProperCapsObjects)
{
  CreatePipelineWithElements();

  RefPtr<BaseSink> basesink;
  basesink = basesink.cast_dynamic(sink);
  MM_ASSERT_TRUE(basesink);

  RefPtr<Pad> sink_pad = basesink->get_sink_pad();
  MM_ASSERT_TRUE(sink_pad);
  MM_ASSERT_TRUE(GST_IS_PAD(sink_pad->gobj()));
  RefPtr<Caps> caps = sink_pad->query_caps(Caps::create_any());
  MM_ASSERT_TRUE(caps);
  MM_ASSERT_TRUE(caps->gobj());
  MM_ASSERT_TRUE(GST_IS_CAPS(caps->gobj()));
  RefPtr<Caps> template_caps = Glib::wrap(gst_pad_get_pad_template_caps(sink_pad->gobj()), false);

  sink_pad.reset();
  basesink.reset();
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

TEST_F(DerivedFromAppSinkPluginTest, UseAppSinkDuringDataFlowInPipeline)
{
  CreatePipelineWithElements();

  RefPtr<AppSink> appsink = appsink.cast_static(sink);
  RefPtr<AppSrc> appsrc = appsrc.cast_static(source);

  EXPECT_EQ(STATE_CHANGE_ASYNC, pipeline->set_state(STATE_PLAYING));

  std::string data = "hello world";
  RefPtr<Buffer> buf = Buffer::create(data.length() + 1);
  MM_ASSERT_TRUE(buf);
  MapInfo map_info;
  MM_ASSERT_TRUE(buf->map(map_info, MAP_WRITE));
  strcpy((char *)map_info.get_data(), data.c_str());
  buf->unmap(map_info);

  EXPECT_EQ(FLOW_OK, appsrc->push_buffer(buf));

  RefPtr<Buffer> buf_out;
  RefPtr<Sample> sample = appsink->pull_sample();
  MM_ASSERT_TRUE(sample);
  buf_out = sample->get_buffer();
  MM_ASSERT_TRUE(buf_out);

  EXPECT_TRUE(buf_out->memcmp(0, data.c_str(), data.length()) == 0);

  EXPECT_EQ(FLOW_OK, appsrc->end_of_stream());

  RefPtr<Message> msg = pipeline->get_bus()->poll((MessageType)(MESSAGE_EOS | MESSAGE_ERROR) , 1*SECOND);
  MM_ASSERT_TRUE(msg);
  EXPECT_EQ(MESSAGE_EOS, msg->get_message_type());
  EXPECT_EQ(STATE_CHANGE_SUCCESS, pipeline->set_state(STATE_NULL));
}

#endif

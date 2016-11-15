/*
 * test-plugin-register.cc
 *
 *  Created on: Aug 1, 2013
 *      Author: m.kolny
 */

#include "mmtest.h"
#include <gstreamermm.h>

// TODO re-write this tests to not use AppSrc/AppSink
#ifndef GSTREAMERMM_DISABLE_DEPRECATED

#include <gstreamermm/appsink.h>
#include <gstreamermm/appsrc.h>
#include <vector>
#include "foo.h"

using namespace Gst;
using Glib::RefPtr;

class RegisterPluginTest : public ::testing::Test
{
protected:
  RefPtr<AppSrc> source;
  RefPtr<Element> filter;
  RefPtr<AppSink> sink;
  RefPtr<Gst::Pipeline> pipeline;

  virtual void SetUp()
  {
    Plugin::register_static(GST_VERSION_MAJOR, GST_VERSION_MINOR, "foo",
        "foo is example of C++ element", sigc::ptr_fun(&Foo::register_foo), "0.123",
        "LGPL", "source?", "package?", "http://example.com");
  }

  void CreatePipelineWithElements()
  {
    pipeline = Gst::Pipeline::create("my-pipeline");

    source = AppSrc::create("source");
    filter = ElementFactory::create_element("foomm", "filter");
    sink = AppSink::create("sink");

    MM_ASSERT_TRUE(source);
    MM_ASSERT_TRUE(filter);
    MM_ASSERT_TRUE(sink);

    EXPECT_NO_THROW(pipeline->add(source)->add(filter)->add(sink));
    EXPECT_NO_THROW(source->link(filter)->link(sink));
  }
};

TEST_F(RegisterPluginTest, CreateRegisteredElement)
{
  filter = Gst::ElementFactory::create_element("foomm", "filter");

  MM_ASSERT_TRUE(filter);
}

TEST_F(RegisterPluginTest, CheckPropertyUsage)
{
  filter = Gst::ElementFactory::create_element("foomm", "filter");

  MM_ASSERT_TRUE(filter);

  Glib::ustring property_value;
  filter->get_property("sample_property", property_value);
  EXPECT_STREQ("def_val", property_value.c_str());

  Glib::ustring expected_property_value = "second_property_test";
  filter->set_property("sample_property", expected_property_value);
  filter->get_property("sample_property", property_value);
  EXPECT_STREQ(expected_property_value.c_str(), property_value.c_str());
}

TEST_F(RegisterPluginTest, CreatePipelineWithRegisteredElement)
{
  CreatePipelineWithElements();
}

TEST_F(RegisterPluginTest, CheckDataFlowThroughCreatedElement)
{
  CreatePipelineWithElements();

  EXPECT_EQ(STATE_CHANGE_ASYNC, pipeline->set_state(STATE_PLAYING));

  std::vector<guint8> data = {4, 5, 2, 7, 1};
  RefPtr<Buffer> buf = Buffer::create(data.size());
  MM_ASSERT_TRUE(buf);
  Gst::MapInfo mapinfo;

  MM_ASSERT_TRUE(buf->map(mapinfo, MAP_WRITE));
  std::copy(data.begin(), data.end(), mapinfo.get_data());
  EXPECT_EQ(FLOW_OK, source->push_buffer(buf));
  buf->unmap(mapinfo);

  RefPtr<Gst::Buffer> buf_out;
  RefPtr<Gst::Sample> samp = sink->pull_preroll();

  MM_ASSERT_TRUE(samp);
  buf_out = samp->get_buffer();
  MM_ASSERT_TRUE(buf_out->map(mapinfo, MAP_READ));
  MM_ASSERT_TRUE(mapinfo.get_data());
  std::sort(data.begin(), data.end());
  MM_ASSERT_TRUE(std::equal(data.begin(), data.end(), mapinfo.get_data()));
  buf_out->unmap(mapinfo);
  EXPECT_EQ(FLOW_OK, source->end_of_stream());

  EXPECT_EQ(STATE_CHANGE_SUCCESS, pipeline->set_state(Gst::STATE_NULL));
}

#endif

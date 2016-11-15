/*
 * test-plugin-pushsrc.cc
 *
 *  Created on: Aug 1, 2013
 *      Author: m.kolny
 */

#include "mmtest.h"
#include <gstreamermm.h>

// TODO re-write this tests to not use AppSrc/AppSink
#ifndef GSTREAMERMM_DISABLE_DEPRECATED

#include <string>
#include <gstreamermm/appsink.h>
#include <gstreamermm/private/pushsrc_p.h>

using namespace Gst;
using Glib::RefPtr;

class FooSrc : public Gst::PushSrc
{
  int count_left;

public:
  static const int COUNT = 5;
  static void class_init(Gst::ElementClass<FooSrc> *klass)
  {
    klass->set_metadata("foosrc_longname",
           "foosrc_classification", "foosrc_detail_description", "foosrc_detail_author");

    klass->add_pad_template(Gst::PadTemplate::create("src", Gst::PAD_SRC, Gst::PAD_ALWAYS,
                                                     Gst::Caps::create_from_string("x-application/x-foo1")));
  }

  explicit FooSrc(GstPushSrc *gobj)
  : Gst::PushSrc(gobj),
    count_left(COUNT)
  {
    set_format(Gst::FORMAT_TIME);
  }

  Gst::FlowReturn create_vfunc(guint64 /* offset */, guint /* size */, Glib::RefPtr<Gst::Buffer>& buffer)
  {
    if (count_left-- <= 0)
      return Gst::FLOW_EOS;

    std::string s = std::to_string(COUNT - count_left);
    buffer = Gst::Buffer::create(s.size());

    MapInfo info;
    buffer->map(info, MAP_WRITE);

    std::copy(s.begin(), s.end(), info.get_data());
    return Gst::FLOW_OK;
  }

  virtual bool negotiate_vfunc()
  {
    return true;
  }

  virtual bool start_vfunc()
  {
    count_left = COUNT;
    return true;
  }
};

bool register_foo(Glib::RefPtr<Gst::Plugin> plugin)
{
  Gst::ElementFactory::register_element(plugin, "foosrcmm", 10, Gst::register_mm_type<FooSrc>("foosrcmm"));
  return true;
}

class PushSrcPluginTest : public ::testing::Test
{
protected:
  virtual void SetUp()
  {
    Plugin::register_static(GST_VERSION_MAJOR, GST_VERSION_MINOR, "foo",
          "foo is example of C++ element", sigc::ptr_fun(register_foo), "0.123",
          "LGPL", "source?", "package?", "http://example.com");
  }

  RefPtr<Pipeline> CreatePipeline()
  {
    RefPtr<Pipeline> pipeline = Pipeline::create("my-pipeline");

    EXPECT_TRUE(!!pipeline);

    RefPtr<Element> source = ElementFactory::create_element("foosrcmm", "src");
    RefPtr<AppSink> sink = AppSink::create("sink");

    EXPECT_TRUE(!!source);
    EXPECT_TRUE(!!sink);

    pipeline->add(source)->add(sink);
    source->link(sink);

    return pipeline;
  }
};

TEST_F(PushSrcPluginTest, CreateRegisteredElement)
{
  Glib::RefPtr<Gst::Element> source = Gst::ElementFactory::create_element("foosrcmm", "src");

  MM_ASSERT_TRUE(source);
}

TEST_F(PushSrcPluginTest, DISABLED_CreatePipelineWithRegisteredElement)
{
  CreatePipeline();
}

#endif

#include "mmtest.h"
#include <gstreamermm.h>

// TODO re-write this tests to not use AppSrc/AppSink
#ifndef GSTREAMERMM_DISABLE_DEPRECATED

#include <gstreamermm/appsink.h>
#include <gstreamermm/appsrc.h>
#include <vector>
#include "derivedfrombasetransform.h"

using namespace Gst;
using Glib::RefPtr;

class DerivedFromBaseTransformPluginTest : public ::testing::Test
{
protected:
  RefPtr<AppSrc> source;
  RefPtr<Element> filter;
  RefPtr<AppSink> sink;
  RefPtr<Gst::Pipeline> pipeline;

  virtual void SetUp()
  {
    Plugin::register_static(GST_VERSION_MAJOR, GST_VERSION_MINOR, "derivedfrombasetransform",
        "derivedfrombasetransfrom is an example of C++ element derived from Gst::BaseTransform",
        sigc::ptr_fun(&DerivedFromBaseTransform::register_element), "0.123",
        "LGPL", "source?", "package?", "http://example.com");
  }

  void CreatePipelineWithElements()
  {
    pipeline = Gst::Pipeline::create("my-pipeline");

    source = AppSrc::create("source");
    filter = ElementFactory::create_element("derivedfrombasetransform", "filter");
    sink = AppSink::create("sink");

    MM_ASSERT_TRUE(source);
    MM_ASSERT_TRUE(filter);
    MM_ASSERT_TRUE(sink);

    EXPECT_NO_THROW(pipeline->add(source)->add(filter)->add(sink));
    EXPECT_NO_THROW(source->link(filter)->link(sink));
  }
};

TEST_F(DerivedFromBaseTransformPluginTest, CreateRegisteredElement)
{
  RefPtr<Element> filter_element = Gst::ElementFactory::create_element("derivedfrombasetransform", "filter");

  MM_ASSERT_TRUE(filter_element);
}

TEST_F(DerivedFromBaseTransformPluginTest, CreatePipelineWithRegisteredElement)
{
  CreatePipelineWithElements();
}

TEST_F(DerivedFromBaseTransformPluginTest, VFuncsShouldReturnProperlyRefcountedGobjs)
{
  bool plugin_registered = Plugin::register_static(GST_VERSION_MAJOR, GST_VERSION_MINOR, "derivedfrombasetransform", "exemplary element C++-derived from Gst::BaseTransform",
        sigc::ptr_fun(&DerivedFromBaseTransform::register_element), "0.123", "LGPL", "source?", "package?",
        "http://example.com");
  MM_ASSERT_TRUE(plugin_registered);

  Glib::RefPtr<Gst::Element> element = Gst::ElementFactory::create_element("derivedfrombasetransform");
  MM_ASSERT_TRUE(element);

  Glib::RefPtr<DerivedFromBaseTransform> derived_from_base_transform = Glib::RefPtr<DerivedFromBaseTransform>::cast_dynamic(element);
  MM_ASSERT_TRUE(derived_from_base_transform);

  {
    Glib::RefPtr<Caps> caps = derived_from_base_transform->transform_caps_vfunc(PAD_SINK, Caps::create_any(), Glib::RefPtr<Caps>());
    MM_ASSERT_TRUE(caps);
    MM_ASSERT_TRUE(caps->gobj());
    MM_ASSERT_TRUE(GST_IS_CAPS(caps->gobj()));
    ASSERT_EQ(1, caps->gobj()->mini_object.refcount);
  }

  {
    GstBaseTransform *gobj = derived_from_base_transform->gobj();
    Glib::RefPtr<Caps> caps = Glib::wrap(GST_BASE_TRANSFORM_GET_CLASS(gobj)->transform_caps(gobj, GST_PAD_SINK, Glib::unwrap(Caps::create_any()), NULL));
    MM_ASSERT_TRUE(caps);
    MM_ASSERT_TRUE(caps->gobj());
    MM_ASSERT_TRUE(GST_IS_CAPS(caps->gobj()));
    ASSERT_EQ(1, caps->get_refcount());
  }
}

TEST_F(DerivedFromBaseTransformPluginTest, CheckDataFlowThroughCreatedElement)
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
  MM_ASSERT_TRUE(std::equal(data.begin(), data.end(), mapinfo.get_data()));
  buf_out->unmap(mapinfo);
  EXPECT_EQ(FLOW_OK, source->end_of_stream());

  EXPECT_EQ(STATE_CHANGE_SUCCESS, pipeline->set_state(Gst::STATE_NULL));
}

#endif

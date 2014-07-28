/*
 * test-plugin-register.cc
 *
 *  Created on: Aug 1, 2013
 *      Author: m.kolny
 */

#include <gtest/gtest.h>
#include <gstreamermm.h>
#include <gstreamermm/appsink.h>
#include <gstreamermm/appsrc.h>
#include <vector>
#include "test-foo.h"

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

        ASSERT_TRUE(source);
        ASSERT_TRUE(filter);
        ASSERT_TRUE(sink);

        EXPECT_NO_THROW(pipeline->add(source)->add(filter)->add(sink));
        EXPECT_NO_THROW(source->link(filter)->link(sink));
    }
};

TEST_F(RegisterPluginTest, DISABLED_CreateRegisteredElement)
{
    filter = Gst::ElementFactory::create_element("foomm", "filter");

    ASSERT_TRUE(filter);
}

TEST_F(RegisterPluginTest, DISABLED_CheckPropertyUsage)
{
    filter = Gst::ElementFactory::create_element("foomm", "filter");

    Glib::ustring property_value;
    filter->get_property("sample_property", property_value);
    ASSERT_STREQ("def_val", property_value.c_str());

    Glib::ustring expected_property_value = "second_property_test";
    filter->set_property("sample_property", expected_property_value);
    filter->get_property("sample_property", property_value);
    ASSERT_STREQ(expected_property_value.c_str(), property_value.c_str());
}

TEST_F(RegisterPluginTest, DISABLED_CreatePipelineWithRegisteredElement)
{
    CreatePipelineWithElements();
}

TEST_F(RegisterPluginTest, DISABLED_CheckDataFlowThroughCreatedElement)
{
    CreatePipelineWithElements();

    pipeline->set_state(STATE_PLAYING);

    std::vector<guint8> data = {4, 5, 2, 7, 1};
    RefPtr<Buffer> buf = Buffer::create(data.size());
    RefPtr<Gst::MapInfo> mapinfo(new Gst::MapInfo());

    buf->map(mapinfo, MAP_WRITE);
    std::copy(data.begin(), data.end(), mapinfo->get_data());
    source->push_buffer(buf);
    buf->unmap(mapinfo);

    RefPtr<Gst::Buffer> buf_out;
    RefPtr<Gst::Sample> samp = sink->pull_preroll();

    buf_out = samp->get_buffer();
    buf_out->map(mapinfo, MAP_READ);
    ASSERT_TRUE(mapinfo->get_data());
    std::sort(data.begin(), data.end());
    ASSERT_TRUE(std::equal(data.begin(), data.end(), mapinfo->get_data()));
    buf_out->unmap(mapinfo);
    source->end_of_stream();

    pipeline->set_state(Gst::STATE_NULL);
    pipeline.reset();
    filter.reset();
}

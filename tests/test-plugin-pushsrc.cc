/*
 * test2.cpp
 *
 *  Created on: Feb 22, 2013
 *      Author: t.lakota
 */

/* gstreamermm - a C++ wrapper for gstreamer
 *
 * Copyright 2008 The gstreamermm Development Team
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free
 * Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#include <gstreamermm.h>
#include <iostream>
#include <cassert>
#include <algorithm>
#include <gstreamermm/appsrc.h>
#include <gstreamermm/appsink.h>
#include <cstring>

//this is a bit hacky, but for now necessary for Gst::Element_Class::class_init_function which is used by register_mm_type
#include <gstreamermm/private/pushsrc_p.h>

class FooSrc : public Gst::PushSrc
{
  int count_left;

public:
  static const int COUNT = 5;
  static void base_init(BaseClassType *klass)
  {
    /* This is another hack.
     * For now it uses pure C functions, which should be wrapped then.
     */
    gst_element_class_set_details_simple(GST_ELEMENT_CLASS(klass),
        "foosrc_longname", "foosrc_classification", "foosrc_detail_description",
        "foosrc_detail_author");

    gst_element_class_add_pad_template(GST_ELEMENT_CLASS(klass),
        Gst::PadTemplate::create("src", Gst::PAD_SRC, Gst::PAD_ALWAYS,
            Gst::Caps::create_from_string("x-application/x-foo1"))->gobj());
  }
  explicit FooSrc(GstPushSrc *gobj) :
      Gst::PushSrc(gobj)
  {
    set_format(Gst::FORMAT_TIME);
  }
  Gst::FlowReturn create_vfunc(guint64 offset, guint size, Glib::RefPtr<Gst::Buffer>& buffer)
  {
    if (count_left-- <= 0)
      return Gst::FLOW_UNEXPECTED;
    std::stringstream ss;
    ss << COUNT - count_left << "";
    std::string s = ss.str();
    buffer = Gst::Buffer::create(s.size());
    std::copy(s.begin(), s.end(), buffer->get_data());
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
  Gst::ElementFactory::register_element(plugin, "foosrcmm", 10,
      Gst::register_mm_type<FooSrc>("foosrcmm"));
  return true;

}

int main(int argc, char** argv)
{
  Gst::init(argc, argv);
  Gst::Plugin::register_static(GST_VERSION_MAJOR, GST_VERSION_MINOR, "foo",
      "foo is example of C++ element", sigc::ptr_fun(register_foo), "0.123",
      "LGPL", "source?", "package?", "http://example.com");

  Glib::RefPtr<Gst::Pipeline> pipeline;

  pipeline = Gst::Pipeline::create("my-pipeline");

  Glib::RefPtr<Gst::Element> source = Gst::ElementFactory::create_element(
      "foosrcmm", "src");
  Glib::RefPtr<Gst::AppSink> sink = Gst::AppSink::create("sink");

  assert(source);
  assert(sink);

  pipeline->add(source)->add(sink);
  source->link(sink);

  pipeline->set_state(Gst::STATE_PLAYING);

  for (int i = 0; i < FooSrc::COUNT; ++i)
  {
    std::cout << "pulling buffer " << i + 1 << std::endl;
    Glib::RefPtr<Gst::Buffer> buf_out;
    buf_out = sink->pull_buffer();
    assert(buf_out);
    assert(buf_out->get_data());
    assert(buf_out->get_data()[0]=='1'+i);
  }

  std::cout << "waiting for eos or error" << std::endl;
  Glib::RefPtr<Gst::Message> msg = pipeline->get_bus()->poll(
      (Gst::MessageType) (Gst::MESSAGE_EOS | Gst::MESSAGE_ERROR),
      1 * Gst::SECOND);
  assert(msg);
  assert(msg->get_message_type() == Gst::MESSAGE_EOS);
  std::cout << "shutting down" << std::endl;

  pipeline->set_state(Gst::STATE_NULL);
  pipeline.reset();
  source.reset();
  sink.reset();

  return 0;
}


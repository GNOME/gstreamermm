/*
 * foo.h
 *
 *  Created on: Aug 1, 2013
 *      Author: m.kolny
 */

#ifndef TESTS_PLUGINS_FOO_H_
#define TESTS_PLUGINS_FOO_H_

#include <gstreamermm.h>
#include <gstreamermm/private/element_p.h>
#include <assert.h>

class Foo : public Gst::Element
{
  Glib::RefPtr<Gst::Pad> sinkpad;
  Glib::RefPtr<Gst::Pad> srcpad;
  Glib::Property<Glib::ustring> sample_property;

public:
  static void class_init(Gst::ElementClass<Foo> *klass)
  {
    klass->set_metadata("foo_longname",
          "foo_classification", "foo_detail_description", "foo_detail_author");

    klass->add_pad_template(Gst::PadTemplate::create("sink", Gst::PAD_SINK, Gst::PAD_ALWAYS,
        Gst::Caps::create_any()));
    klass->add_pad_template(Gst::PadTemplate::create("src", Gst::PAD_SRC, Gst::PAD_ALWAYS,
        Gst::Caps::create_any()));
  }

  Gst::FlowReturn chain(const Glib::RefPtr<Gst::Pad> & /* pad */, Glib::RefPtr<Gst::Buffer> &buf)
  {
    buf = buf->create_writable();
    assert(buf->gobj()->mini_object.refcount==1);
    Gst::MapInfo mapinfo;
    buf->map(mapinfo, Gst::MAP_WRITE);
    std::sort(mapinfo.get_data(), mapinfo.get_data() + mapinfo.get_size());
    buf->unmap(mapinfo);
    assert(buf->gobj()->mini_object.refcount==1);
    return srcpad->push(std::move(buf));
  }

  explicit Foo(GstElement *gobj)
  : Glib::ObjectBase(typeid (Foo)), // type must be registered before use
    Gst::Element(gobj),
    sample_property(*this, "sample_property", "def_val")

  {
    add_pad(sinkpad = Gst::Pad::create(get_pad_template("sink"), "sink"));
    add_pad(srcpad = Gst::Pad::create(get_pad_template("src"), "src"));
    sinkpad->set_chain_function(sigc::mem_fun(*this, &Foo::chain));
  }

  static bool register_foo(Glib::RefPtr<Gst::Plugin> plugin)
  {
    Gst::ElementFactory::register_element(plugin, "foomm", 10, Gst::register_mm_type<Foo>("foo"));

    return true;
  }
};

#endif /* TESTS_PLUGINS_FOO_H_ */

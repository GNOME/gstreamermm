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

//this is a bit hacky, but for now necessary for Gst::Element_Class::class_init_function which is used by register_mm_type
#include <gstreamermm/private/element_p.h>

class Foo: public Gst::Element
{
	Glib::RefPtr<Gst::Pad> sinkpad;
	Glib::RefPtr<Gst::Pad> srcpad;

public:
	static void base_init(BaseClassType *klass)
	{
		/* This is another hack.
		 * For now it uses pure C functions, which should be wrapped then.
		 */
		gst_element_class_set_details_simple(klass,
				"foo_longname",
				"foo_classification",
				"foo_detail_description",
				"foo_detail_author");


		gst_element_class_add_pad_template(klass, Gst::PadTemplate::create("sink", Gst::PAD_SINK, Gst::PAD_ALWAYS, Gst::Caps::create_any())->gobj());
		gst_element_class_add_pad_template(klass, Gst::PadTemplate::create("src", Gst::PAD_SRC, Gst::PAD_ALWAYS, Gst::Caps::create_any())->gobj());
	}

	Gst::FlowReturn chain(const Glib::RefPtr<Gst::Pad> &pad, Glib::RefPtr<Gst::Buffer> &buf)
	{
    	assert(buf->gobj()->mini_object.refcount==1);
    	buf=buf->create_writable();
    	//run some C++ function
    	std::sort(buf->get_data(), buf->get_data() + buf->get_size());
    	assert(buf->gobj()->mini_object.refcount==1);
    	return srcpad->push(buf);
	}
	  explicit Foo(GstElement *gobj) :
			  Gst::Element(gobj)
	  {
			add_pad(sinkpad=Gst::Pad::create(get_pad_template("sink"), "sink"));
			add_pad(srcpad=Gst::Pad::create(get_pad_template("src"), "src"));
			sinkpad->set_chain_function(sigc::mem_fun(*this, &Foo::chain));
	  }
	  ~Foo()
	  {
		  printf("destroying foo\n");
	  }
};

bool register_foo(Glib::RefPtr<Gst::Plugin> plugin)
{
	Gst::ElementFactory::register_element(plugin, "foomm", 10, Gst::register_mm_type<Foo>("foomm"));
	return true;

}

int main(int argc, char** argv)
{
  Gst::init(argc, argv);
	Gst::Plugin::register_static(GST_VERSION_MAJOR, GST_VERSION_MINOR,
			"foo", "foo is example of C++ element",
			sigc::ptr_fun(register_foo), "0.123",
			"LGPL", "source?",
			"package?", "http://example.com"
			);

  Glib::RefPtr<Gst::Pipeline> pipeline;
  Glib::RefPtr<Gst::Element> source, filter1, filter2, sink;

  pipeline = Gst::Pipeline::create("my-pipeline");

  source = Gst::ElementFactory::create_element("fdsrc", "source");
  filter1 = Gst::ElementFactory::create_element("foomm", "filter1");
  sink = Gst::ElementFactory::create_element("fdsink", "sink");

  assert(source);
  assert(filter1);
  assert(sink);

  pipeline->add(source)->add(filter1)->add(sink);
  source->link(filter1)->link(sink);

  std::cout << "Successfully linked elements '" << source->get_name() <<
    "', '" << filter1->get_name() << "' and '" << sink->get_name() <<
      "'." << std::endl;

  pipeline->set_state(Gst::STATE_PLAYING);
  pipeline->get_bus()->poll(Gst::MESSAGE_EOS, -1);
  pipeline->set_state(Gst::STATE_NULL);
  pipeline.reset();
  filter1.reset();
  filter2.reset();

  return 0;
}





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

int main(int argc, char** argv)
{
  Gst::init(argc, argv);

  Glib::RefPtr<Gst::Pipeline> pipeline;
  Glib::RefPtr<Gst::Bin> bin;
  Glib::RefPtr<Gst::Element> source, sink;

  pipeline = Gst::Pipeline::create();
  bin = Gst::Bin::create();

  source = Gst::ElementFactory::create_element("fakesrc", "source");
  sink = Gst::ElementFactory::create_element("fakesink", "sink");

  bin->add(source)->add(sink);

  pipeline->add(bin);
  source->link(sink);

  pipeline->remove(bin);
  pipeline->add(bin);

  std::cout << "Successfully added elements '" << source->get_name() <<
    "' and '" << sink->get_name() << "' to bin '" <<
      bin->get_name() << "'." << std::endl;

  // use childproxy interface to get bin children count
  std::cout << "'" << bin->get_name() << "' children count  = " << bin->get_children_count() << "." << std::endl;

  // use childproxy interface to get bin's first child
  Glib::RefPtr<Gst::Element> element = Glib::RefPtr<Gst::Element>::cast_dynamic(bin->get_child(0));
  std::cout << "'" << bin->get_name() << "' first child is '" << element->get_name() << "'." << std::endl;

  return 0;
}

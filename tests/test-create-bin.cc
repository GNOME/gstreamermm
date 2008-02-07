/* gstreamermm - a C++ wrapper for gstreamer
 *
 * Copyright 2008 The gstreamermm Development Team
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the Free
 * Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#include <gstreamermm.h>
#include <iostream>

int main (int argc, char* argv[])
{
  Gst::init(argc, argv);

  Glib::RefPtr<Gst::Pipeline> pipeline;
  Glib::RefPtr<Gst::Bin> bin;
  Glib::RefPtr<Gst::Element> source, sink;

  pipeline = Gst::Pipeline::create("my-pipeline");
  bin = Gst::Bin::create("my-bin");

  source = Gst::Element::create("fakesrc", "source");
  sink = Gst::Element::create("fakesink", "sink");

  bin->add(source)->add(sink);

  pipeline->add(bin);
  source->link(sink);

  std::cout << "Successfully added elements '" << source->get_name() <<
    "' and '" << sink->get_name() << "' to bin '" <<
      bin->get_name() << "'." << std::endl;
}

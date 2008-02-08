// -*- Mode: C++; indent-tabs-mode: nil; c-basic-offset: 2 -*-

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
  Glib::RefPtr<Gst::Element> source, filter, sink;

  pipeline = Gst::Pipeline::create("my-pipeline");

  source = Gst::Element::create("fakesrc", "source");
  filter = Gst::Element::create("identity", "filter");
  sink = Gst::Element::create("fakesink", "sink");

  pipeline->add(source)->add(filter)->add(sink);
  source->link(filter)->link(sink);

  std::cout << "Successfully linked elements '" << source->get_name() <<
    "', '" << filter->get_name() << "' and '" << sink->get_name() <<
      "'." << std::endl;
}

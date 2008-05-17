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

int main(int argc, char** argv)
{
  Glib::RefPtr<Gst::Pipeline> pipeline;
  Glib::RefPtr<Gst::Element> element_source, element_filter, element_sink;

  // Initialize Gstreamermm:
  Gst::init(argc, argv);

  // Create pipeline:
  pipeline = Gst::Pipeline::create("my-pipeline");

  // Create elements:
  element_source = Gst::ElementFactory::create_element("fakesrc");
  element_filter = Gst::ElementFactory::create_element("identity");
  element_sink = Gst::ElementFactory::create_element("fakesink");

  // We must add the elements to the pipeline before linking them:
  pipeline->add(element_source)->add(element_filter)->add(element_sink);

  // Link the elements together:
  try
  {
    element_source->link(element_filter)->link(element_sink);
  }
  catch(const std::runtime_error& error)
  {
    std::cout << "Exception while linking: " << error.what() << std::endl;
  }

  return 0;
}

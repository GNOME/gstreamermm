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
  Glib::RefPtr<Gst::Bin> bin;
  Glib::RefPtr<Gst::Element> source, sink;

  pipeline = Gst::Pipeline::create("my-pipeline");
  bin = Gst::Bin::create("my-bin");

  source = Gst::ElementFactory::create_element("fakesrc", "source");
  sink = Gst::ElementFactory::create_element("fakesink", "sink");

  bin->add(source)->add(sink);

  pipeline->add(bin);
  source->link(sink);

  std::cout << "The following elements have been added to bin '" <<
    bin->get_name() << "'." << std::endl;

  int iterations = 0;
  Gst::Iterator<Gst::Element> elements = bin->iterate_elements();

  try
  {
    for ( ; !elements.is_last(); ++elements)
    {
      if (elements)
        std::cout << (*elements)->get_name() << std::endl;

      iterations++;
    }
    ++elements;
  }
  catch (std::runtime_error& e)
  {
    std::cout << "Runtime error while iterating through \"" <<
      bin->get_name() << "'s\" elements." << std::endl;
  }

  std::cout << "The loop iterated " << iterations << " to print bin '" <<
  bin->get_name() << "' elements." << std::endl;

  return 0;
}

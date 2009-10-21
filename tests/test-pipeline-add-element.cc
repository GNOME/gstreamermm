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

  Glib::RefPtr<Gst::Pipeline> pipeline = Gst::Pipeline::create("my-pipeline");
  Glib::RefPtr<Gst::Element> source = Gst::ElementFactory::create_element("fakesrc", "source");

  pipeline->add(source);

  Glib::RefPtr<Gst::Element> sourceCopy = pipeline->get_element("source");

  if(sourceCopy)
    std::cout << "Successfully added element '" << sourceCopy->get_name() <<
     "' to pipeline '" << pipeline->get_name() << "'." << std::endl;

  return 0;
}

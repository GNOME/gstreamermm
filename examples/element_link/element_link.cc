/* gstreamermm - a C++ wrapper for gstreamer
 *
 * Copyright 2008 The gstreamermm Development Team
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
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
  try
  {
    pipeline->add(element_source)->add(element_filter)->add(element_sink);
  }
  catch (std::runtime_error& ex)
  {
    std::cerr << "Exception while adding: " << ex.what() << std::endl;
    return 1;
  }

  // Link the elements together:
  try
  {
    element_source->link(element_filter)->link(element_sink);
  }
  catch(const std::runtime_error& error)
  {
    std::cerr << "Exception while linking: " << error.what() << std::endl;
  }
  return 0;
}

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
#include <stdexcept>
#include <iostream>

int main(int argc, char** argv)
{
  Glib::RefPtr<Gst::Pipeline> m_Pipeline;
  Glib::RefPtr<Gst::Element> m_Element_Source, m_Element_Filter, m_Element_Sink;

  // init Gstreamermm
  Gst::init(argc, argv);

  // create pipeline
  m_Pipeline = Gst::Pipeline::create("my-pipeline");

  // create elements
  try
  {
    m_Element_Source = Gst::Element::create("fakesrc", "source");
    m_Element_Filter = Gst::Element::create("identity", "filter");
    m_Element_Sink = Gst::Element::create("fakesink", "sink");
  }
  catch(std::runtime_error& error)
  {
    std::cout << error.what();
  }

  // we must add the elements to the pipeline before linking them
  m_Pipeline->add(m_Element_Source)->add(m_Element_Filter)->add(m_Element_Sink);

  // link
  try
  {
    m_Element_Source->link(m_Element_Filter)->link(m_Element_Sink);
  }
  catch(std::runtime_error& error)
  {
    std::cout << error.what();
  }

  return 0;
}

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

// Following code adapted from GStreamer Application Development Manual
// section 8.3.2 (feature negotiation)

int link_elements_with_filter (const Glib::RefPtr<Gst::Element> e1,
  const Glib::RefPtr<Gst::Element> e2)
{
  Gst::Structure structure("video/x-raw-yuv") ;
  structure.set_field("width", 384);
  structure.set_field("height", 288);
  structure.set_field("framerate", Gst::Fraction(25, 1));
  Glib::RefPtr<Gst::Caps> caps = Gst::Caps::create(structure);
    
  Gst::Structure structure2("video/x-raw-rgb");
  structure2.set_field("width", 384);
  structure2.set_field("height", 288);
  structure2.set_field("framerate", Gst::Fraction(25, 1));
  caps->append_structure(structure2);

  return e1->link(e2, caps);
}

void test_simple()
{
  int width;
  Gst::Fraction rate;
  std::string string;

  Glib::RefPtr<Gst::Caps> caps = Gst::Caps::create_simple("video/x-raw-yuv");
  caps->set_simple("width", 500);
  caps->set_simple("framerate", Gst::Fraction(25, 1));
  caps->set_simple("string", "A string");

  if(caps->get_structure(0).get_field("width", width))
  {
    std::cout << "Simple caps width after setting = " << width << "." <<
      std::endl;
  }
  else
    std::cout << "Getting of simple caps width field failed." << std::endl;

  if(caps->get_structure(0).get_field("framerate", rate))
  {
    std::cout << "Simple caps rate after setting = " << rate.num << "/" <<
      rate.denom << "." << std::endl;
  }
  else
    std::cout << "Getting of simple caps framerate field failed." << std::endl;

  if(caps->get_structure(0).get_field("string", string))
  {
    std::cout << "Simple caps string after setting = '" << string << "'." <<
      std::endl;
  }
  else
    std::cout << "Getting of simple caps sting field failed." << std::endl;
}

int main(int argc, char** argv)
{
  Glib::RefPtr<Gst::Pipeline> pipeline;
  Glib::RefPtr<Gst::Element> e1, e2;

  Gst::init(argc, argv);

  test_simple();

  pipeline = Gst::Pipeline::create("pipeline");

  e1 = Gst::ElementFactory::create_element("fakesrc", "source");
  e2 = Gst::ElementFactory::create_element("fakesink", "sink");

#ifdef GLIBMM_EXCEPTIONS_ENABLED
  try
  {
#endif
    pipeline->add(e1)->add(e2);
#ifdef GLIBMM_EXCEPTIONS_ENABLED
  }
  catch (std::runtime_error& ex)
  {
    std::cerr << "Exception while adding: " << ex.what() << std::endl;
    return 1;
  }
#endif

  if(!link_elements_with_filter(e1, e2))
    std::cerr << "Falied to link e1 and e2." << std::endl;
  else
    std::cerr << "Succeeded linking e1 and e2 with filter." << std::endl;

  return 0;
}

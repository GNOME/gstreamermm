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

int main (int argc, char* argv[])
{
  Gst::init(argc, argv);

  Glib::RefPtr<Gst::Pipeline> pipeline;
  Glib::RefPtr<Gst::Bin> bin;
  Glib::RefPtr<Gst::Element> e1, e2, e3, e4;

  pipeline = Gst::Pipeline::create("my-pipeline");
  bin = Gst::Bin::create("my-bin");

  e1 = Gst::ElementFactory::create_element("fakesrc", "element1");
  e2 = Gst::ElementFactory::create_element("fakesrc", "element2");
  e3 = Gst::ElementFactory::create_element("fakesrc", "element3");
  e4 = Gst::ElementFactory::create_element("fakesink", "element4");

  bin->add(e1)->add(e2)->add(e3)->add(e4);

  pipeline->add(bin);

  std::cout << "The following elements have been added to bin '" <<
    bin->get_name() << "'." << std::endl;

  int iterations = 0;
  Gst::Iterator<Gst::Element> elements = bin->iterate_elements();
  Gst::Iterator<Gst::Element> firstIter;
#ifdef GLIBMM_EXCEPTIONS_ENABLED
  try
  {
#endif
    for(elements.begin(); !elements.is_end(); ++elements, ++iterations)
    {
      if(!firstIter)
        firstIter = elements;

      std::cout << elements->get_name() << std::endl;
    }

    if(firstIter)
      std::cout << "The first element iterator processed is '" << 
        firstIter->get_name() << "'." << std::endl;

    if(elements)
      std::cout << "elements.is_end() == true && (elements) is valid." <<
        std::endl;
#ifdef GLIBMM_EXCEPTIONS_ENABLED
  }
  catch(std::runtime_error& e)
  {
    std::cout << "Runtime error while iterating through \"" <<
      bin->get_name() << "'s\" elements:" << std::endl << e.what() << std::endl;
  }
#endif

  std::cout << "The loop iterated " << iterations <<
    " time(s) to print bin '" << bin->get_name() << "' elements." << std::endl;

  std::cout << std::endl <<
    "The following are standard GStreamer query types:" << std::endl;

  Gst::IteratorBasic<const Gst::QueryTypeDefinition> queryTypes =
    Gst::Query::iterate_definitions();

#ifdef GLIBMM_EXCEPTIONS_ENABLED
  try
  {
#endif
    for(++queryTypes; !queryTypes.is_end(); ++queryTypes)
    {
      std::cout << queryTypes->nick << " -- " << queryTypes->description <<
        "." << std::endl;
    }
#ifdef GLIBMM_EXCEPTIONS_ENABLED
  }
  catch(std::runtime_error& e)
  {
    std::cout << "Runtime error while iterating through query types." <<
      std::endl << e.what() << std::endl;
  }
#endif
  std::cout << std::endl <<
    "The following are standard GStreamer formats:" << std::endl;

  Gst::IteratorBasic<const Gst::FormatDefinition> formats =
    Gst::iterate_format_definitions();
#ifdef GLIBMM_EXCEPTIONS_ENABLED
  try
  {
#endif
    for(++formats; !formats.is_end(); ++formats)
    {
      std::cout << formats->nick << " -- " << formats->description <<
        "." << std::endl;
    }
#ifdef GLIBMM_EXCEPTIONS_ENABLED
  }
  catch(std::runtime_error& e)
  {
    std::cout << "Runtime error while iterating through formats." <<
      std::endl << e.what() << std::endl;
  }
#endif
  return 0;
}

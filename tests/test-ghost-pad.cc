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

  Glib::RefPtr<Gst::Caps> caps = Gst::Caps::create_simple("video/x-raw-yuv");
  caps->set_simple("width", 500);
  caps->set_simple("framerate", Gst::Fraction(25, 1));

  Glib::RefPtr<Gst::PadTemplate> templ =
    Gst::PadTemplate::create("source-template", Gst::PAD_SINK, Gst::PAD_ALWAYS,
      caps);

  if(templ)
    std::cout << "Successfully created pad template '" <<
      templ->get_name_template() << "'; direction = " << 
        templ->get_direction() << "." << std::endl;

  Glib::RefPtr<Gst::Pad> pad1 = Gst::Pad::create(Gst::PAD_SINK);
  if(pad1)
    std::cout << "Successfully created pad '" << pad1->get_name() <<
      "'; direction = " << pad1->get_direction() << "." << std::endl;

  Glib::RefPtr<Gst::Pad> pad2 = Gst::Pad::create(templ);

  if(pad2)
    std::cout << "Successfully created pad '" << pad2->get_name() <<
      "'; direction = " << pad2->get_direction() << "." << std::endl;

// Uncomment the following to get an exception of a failed target pad ghostpad
// construction.
/*
  Glib::RefPtr<Gst::GhostPad> gpad1 = Gst::GhostPad::create(pad1);
  if(gpad1)
    std::cout << "Successfully created pad '" << gpad1->get_name() <<
      "'; direction = " << gpad1->get_direction() << "." << std::endl;
*/

  Glib::RefPtr<Gst::GhostPad> gpad2 =
    Gst::GhostPad::create(Gst::PAD_SRC);
  if(gpad2)
    std::cout << "Successfully created pad '" << gpad2->get_name() <<
      "'; direction = " << gpad2->get_direction() << "." << std::endl;

// Uncomment the following to see a failed target pad/template ghostpad
// construction.
/*
  Glib::RefPtr<Gst::GhostPad> gpad3 =
    Gst::GhostPad::create(pad1, templ);
  if(gpad3)
    std::cout << "Successfully created pad '" << gpad3->get_name() <<
      "'; direction = " << gpad3->get_direction() << "." << std::endl;
*/

  Glib::RefPtr<Gst::GhostPad> gpad4 =
    Gst::GhostPad::create(templ);
  if(gpad4)
    std::cout << "Successfully created pad '" << gpad4->get_name() <<
      "'; direction = " << gpad4->get_direction() << "." << std::endl;

  return 0;
}

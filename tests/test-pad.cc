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

  Glib::RefPtr<Gst::Pad> pad1 = Gst::Pad::create("pad1", Gst::PAD_SINK);

  if(pad1)
    std::cout << "Successfully created pad '" << pad1->get_name() <<
      "'; direction = " << pad1->get_direction() << "." << std::endl;

  Glib::RefPtr<Gst::Pad> pad2 = Gst::Pad::create(Gst::PAD_SINK);

  if(pad2)
    std::cout << "Successfully created pad '" << pad2->get_name() <<
      "'; direction = " << pad2->get_direction() << "." << std::endl;

  Glib::RefPtr<Gst::Pad> pad3 = Gst::Pad::create(templ, "pad3");

  if(pad3)
    std::cout << "Successfully created pad '" << pad3->get_name() <<
      "'; direction = " << pad3->get_direction() << "." << std::endl;

  Glib::RefPtr<Gst::Pad> pad4 = Gst::Pad::create(templ);

  if(pad4)
    std::cout << "Successfully created pad '" << pad4->get_name() <<
      "'; direction = " << pad4->get_direction() << "." << std::endl;

  return 0;
}

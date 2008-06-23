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

  Glib::RefPtr<Gst::Caps> caps = Gst::Caps::create_simple("video/x-raw-yuv");
  caps->set_simple("width", 500);
  caps->set_simple("framerate", Gst::Fraction(25, 1));

  Glib::RefPtr<Gst::PadTemplate> templ =
    Gst::PadTemplate::create("source-template", Gst::PAD_SRC, Gst::PAD_ALWAYS,
      caps);

  if (templ)
    std::cout << "Successfully created pad template '" << templ->get_name() <<
      "'; direction = " <<  templ->get_direction() << "." << std::endl;

  Glib::RefPtr<Gst::Pad> pad1 = Gst::Pad::create("test", Gst::PAD_SRC);

  if (pad1)
    std::cout << "Successfully created pad '" << pad1->get_name() << "'." <<
      std::endl;

  return 0;
}

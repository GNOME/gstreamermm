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
  
  Glib::RefPtr<Gst::Element> vorbisenc = Gst::ElementFactory::create_element("vorbisenc");

  if (!vorbisenc)
  {
    std::cout << "Failed to create vorbisenc element." << std::endl;
    exit(1);
  }

  Glib::RefPtr< Gst::ElementInterfaced<Gst::TagSetter> > setter =
    Gst::Interface::cast<Gst::TagSetter>(vorbisenc);

  if (!setter)
  {
    std::cout << "Failed to cast vorbisenc element to Gst::TagSetter." <<
      std::endl;
    exit(1);
  }

  setter->add_tag("bitrate", 192);

  int bitrate = 0;
  setter->get_tag_list().get("bitrate", bitrate);
  std::cout << "bitrate = " << bitrate << "." << std::endl;

  return 0;
}

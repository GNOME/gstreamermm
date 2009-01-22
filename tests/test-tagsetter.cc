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

  setter->add_tag(Gst::Tag::BITRATE, 192);
  setter->add_tag(Gst::Tag::TITLE, "A Song");

  int bitrate = 0;

  if(setter->get_tag_list().get(Gst::Tag::BITRATE, bitrate))
    std::cout << "bitrate = " << bitrate << "." << std::endl;
  else
    std::cout << "Could not get tag `" << Gst::Tag::BITRATE <<
      "' from tagsetter." << std::endl;

  std::string title;

  if(setter->get_tag_list().get(Gst::Tag::TITLE, title))
    std::cout << "title = `" << title << "'." << std::endl;
  else
    std::cout << "Could not get tag `" << Gst::Tag::TITLE <<
      "' from tagsetter." << std::endl;

  return 0;
}

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
#include <gstreamermm/filesrc.h>
#include <iostream>

int main(int argc, char* argv[])
{
  Gst::init(argc, argv);

  Glib::RefPtr<Gst::Element> element =
          Gst::ElementFactory::create_element("filesrc");

  Glib::RefPtr<Gst::FileSrc> filesrc = Gst::FileSrc::create();

  if(filesrc)
    std::cout << "filesrc is valid." << std::endl;
  else
    std::cout << "filesrc is invalid." << std::endl;

  gulong mmapsize = 0;
  GstFileSrc* obj = filesrc->gobj();
  g_object_get(obj, "mmapsize", &mmapsize, 0);

  std::cout << "mmapsize = "  << mmapsize << std::endl;

  return 0;
}

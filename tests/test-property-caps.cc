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

int
main(int argc, char* argv[])
{
  Gst::init(argc, argv);

  Glib::RefPtr<Gst::Element> source = 
          Gst::ElementFactory::create_element("multifilesrc", "source");

  if (!source)
  {
    std::cout << "Could not create `multifilesrc' element.  Exiting." <<
      std::endl;

    return -1;
  }

  Glib::RefPtr<Gst::Caps> caps;

  source->get_property("caps", caps);

  if (!caps)
    std::cout << "`caps' property is null before setting property." <<
      std::endl;

  source->set_property("caps", Gst::Caps::create_from_string("image/jpeg,framerate=2/1"));

  source->get_property("caps", caps);

  if (caps)
    std::cout << "`caps' property after setting and getting is '" <<
      caps->to_string() << "'." << std::endl;

  return 0;
}

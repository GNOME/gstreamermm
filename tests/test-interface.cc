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

  Glib::RefPtr<Gst::Element> element = Gst::ElementFactory::create_element("filesrc", "source");

  if(element)
    std::cout << "Successfully created gst element '" <<
      element->get_name() << "'." << std::endl;

  Glib::RefPtr< Gst::ElementInterfaced<Gst::URIHandler> > handler =
    Gst::Interface::cast <Gst::URIHandler>(element);

  if(handler)
  {
    std::cout << "element '" << element->get_name() <<
      "' implements URIHandler interface." << std::endl;

    handler->set_uri("file:///tmp/media.file");

    // Test ambiguity of ElementInterfaced<>::gobj() methods
    GstElement* gstElement = handler->gobj();
    const GstElement* constGstElement = handler->gobj();
    Glib::RefPtr<Gst::Element> element_copy = Glib::wrap(handler->gobj_copy());

    if (!gstElement || !constGstElement || !element_copy)
    {
      std::cout << "Underlying gobject methods of cast object didn't work." <<
        std::endl;
    }

    // Use interface methods
    std::cout << handler->get_name() << " uri = '" << handler->get_uri() <<
      "'." << std::endl;
  }

  Glib::RefPtr< Gst::ElementInterfaced<Gst::XOverlay> > xoverlay =
    Gst::Interface::cast <Gst::XOverlay>(element);

  if(xoverlay)
  {
    std::cout << "element '" << element->get_name() <<
      "' implements XOverlay interface." << std::endl;

    // Use interface methods
    xoverlay->handle_events(false);
  }

  return 0;
}

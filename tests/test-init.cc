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
#include <gstreamerbasemm.h>
#include <iostream>

Gst::ClockTime on_get_time(const Glib::RefPtr<Gst::Clock>& clock)
{
  return Gst::CLOCK_TIME_NONE;
}

int main (int argc, char* argv[])
{
  Gst::init(argc, argv);

  Glib::RefPtr<GstBase::AudioClock> clock = GstBase::AudioClock::create("my-clock", sigc::ptr_fun(on_get_time));

  if (clock)
  {
    Gst::ClockTime resolution = clock->get_resolution();
    std::cout << "GstBase::AudioClock resolution = " << resolution << "." <<
       std::endl;
  }

  Glib::RefPtr<Gst::Element> element = Gst::ElementFactory::create_element("ximagesink", "videosink");

  if (element)
    std::cout << "Successfully created gst element '" <<
      element->get_name() << "'." << std::endl;

  Glib::RefPtr< Gst::ElementInterfaced<GstBase::XOverlay> > xoverlay =
    Gst::Interface::cast <GstBase::XOverlay>(element);

  if(xoverlay)
  {
    std::cout << "element '" << element->get_name() <<
      "' implements XOverlay interface." << std::endl;

    xoverlay->handle_events(false);
  }


  return 0;
}

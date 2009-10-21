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

  GstEvent* cevent = gst_event_new_latency(GST_SECOND);
  
  Glib::RefPtr<Gst::Event> event = Gst::Event::wrap(cevent);

  std::cout << "C++ event instance is !null: " << (bool)(event) << std::endl;

  Glib::RefPtr<Gst::EventLatency> event_latency = Glib::RefPtr<Gst::EventLatency>::cast_dynamic(event);
  std::cout << "event is a Gst::EventLatency: " << (bool)event_latency  << std::endl;
  std::cout << "event type name: '" << Gst::Enums::get_name(event->get_event_type()) << "'" << std::endl;

  const Gst::Structure structure = event->get_structure();
  if(structure)
    std::cout << "Event structure name: '" << structure.get_name() << "'" << std::endl;

  return 0;
}

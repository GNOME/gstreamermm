/* gstreamermm - a C++ wrapper for gstreamer
 *
 * Copyright 2015 The gstreamermm Development Team
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

#include "player_window.h"

#include <gtkmm.h>
#include <gstreamermm.h>

#include <iostream>

int main (int argc, char **argv)
{
  Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv, "org.gtkmm.gstreamermm.gtkmm-media-player");
  Gst::init(argc, argv);

  // playbin plays any media type, choosing an appropriate set of elements
  // and linking them together.
#ifndef GSTREAMERMM_DISABLE_DEPRECATED
  Glib::RefPtr<Gst::PlayBin> playbin = Gst::PlayBin::create("playbin");
#else
  Glib::RefPtr<Gst::Element> playbin = Gst::ElementFactory::create_element("playbin");
#endif

  if(!playbin)
  {
    std::cerr << "The playbin could not be created." << std::endl;
    return 1;
  }

  //Create our player window and give it the pipeline and video sink:
  PlayerWindow player(playbin);

  return app->run(player);
}

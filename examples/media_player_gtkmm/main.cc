/* gstreamermm - a C++ wrapper for gstreamer
 *
 * Copyright 2008 The gstreamermm Development Team
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

#include <gtkmm/main.h>
#include <gstreamermm/init.h>
#include <gstreamermm/element.h>

// Plug-ins:
#include <gstreamermm/playbin.h>

#include <iostream>
#include "player_window.h"

int main(int argc, char** argv)
{
  Gtk::Main kit(argc, argv);
  Gst::init(argc, argv);

  // Create the elements:

  // playbin2 plays any media type, choosing an appropriate set of elements
  // and linking them together.
  Glib::RefPtr<Gst::PlayBin> playbin = Gst::PlayBin::create("playbin");

  if(!playbin)
  {
    std::cerr << "The playbin could not be created." << std::endl;
    return 1;
  }

  //Create our player window and give it the pipeline and video sink:
  PlayerWindow mainWindow(playbin);
  kit.run(mainWindow);

  // Clean up nicely:
  playbin->set_state(Gst::STATE_NULL);

  return 0;
}

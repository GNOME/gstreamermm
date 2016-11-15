/* gstreamermm - a C++ wrapper for gstreamer
 *
 * Copyright 2011 The gstreamermm Development Team
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

#include <gstreamermm.h>
#include <glibmm/main.h>
#include <glibmm/convert.h>
#include <iostream>
#include <stdlib.h>
#include <gstreamermm/playbin.h>

namespace
{

Glib::RefPtr<Glib::MainLoop> mainloop;

// This function is used to receive asynchronous messages in the main loop.
bool on_bus_message(const Glib::RefPtr<Gst::Bus>& /* bus */,
  const Glib::RefPtr<Gst::Message>& message)
{
  switch(message->get_message_type()) {
    case Gst::MESSAGE_EOS:
      std::cout << std::endl << "End of stream" << std::endl;
      mainloop->quit();
      return false;
    case Gst::MESSAGE_ERROR:
    {
      Glib::RefPtr<Gst::MessageError> msgError =
        Glib::RefPtr<Gst::MessageError>::cast_static(message);

      if(msgError)
      {
        Glib::Error err;
        err = msgError->parse_error();
        std::cerr << "Error: " << err.what() << std::endl;
      }
      else
        std::cerr << "Error." << std::endl;

      mainloop->quit();
      return false;
    }
    default:
      break;
  }

  return true;
}

} // anonymous namespace

int main(int argc, char** argv)
{
  // Initialize gstreamermm:
  Gst::init(argc, argv);

  // Check input arguments:
  if(argc < 2)
  {
    std::cout << "Usage: " << argv[0] << " <media file or uri>" << std::endl;
    return EXIT_FAILURE;
  }

  // Create a playbin element.
#ifndef GSTREAMERMM_DISABLE_DEPRECATED
  Glib::RefPtr<Gst::PlayBin> playbin = Gst::PlayBin::create();
#else
  Glib::RefPtr<Gst::Element> playbin = Gst::ElementFactory::create_element("playbin");
#endif
  
  if(!playbin)
  {
    std::cerr << "The playbin2 element could not be created." << std::endl;
    return EXIT_FAILURE;
  }

  // Take the commandline argument and ensure that it is a uri:
  Glib::ustring uri;

  if(gst_uri_is_valid(argv[1]))
    uri = argv[1];
  else
    uri = Glib::filename_to_uri(argv[1]);

  // Set the playbyin2's uri property.
  playbin->set_property("uri", uri);

  // Create the main loop.
  mainloop = Glib::MainLoop::create();

  // Get the bus from the playbin, and add a bus watch to the default main
  // context with the default priority:
  Glib::RefPtr<Gst::Bus> bus = playbin->get_bus();
  bus->add_watch(sigc::ptr_fun(&on_bus_message));

  // Now set the playbin to the PLAYING state and start the main loop:
  std::cout << "Setting to PLAYING." << std::endl;
  playbin->set_state(Gst::STATE_PLAYING);
  std::cout << "Running." << std::endl;
  mainloop->run();

  // Clean up nicely:
  std::cout << "Returned. Setting state to NULL." << std::endl;
  playbin->set_state(Gst::STATE_NULL);

  return EXIT_SUCCESS;
}

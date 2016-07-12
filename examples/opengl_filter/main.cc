/* gstreamermm - a C++ wrapper for gstreamer
 *
 * Copyright 2008-2015 The gstreamermm Development Team
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

#include "sample_gl_filter.h"
#include <gstreamermm.h>
#include <glibmm.h>
#include <iostream>

Glib::RefPtr<Glib::MainLoop> mainloop;

bool on_bus_message(const Glib::RefPtr<Gst::Bus>& /* bus */, const Glib::RefPtr<Gst::Message>& message)
{
  switch(message->get_message_type()) {
    case Gst::MESSAGE_EOS:
      std::cout << std::endl << "End of stream" << std::endl;
      mainloop->quit();
      return false;
    case Gst::MESSAGE_ERROR:
    {
      Glib::RefPtr<Gst::MessageError> msgError = Glib::RefPtr<Gst::MessageError>::cast_static(message);
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
    {
      //std::cout << "debug: on_bus_message: unhandled message=" << G_OBJECT_TYPE_NAME(message->gobj()) << std::endl;
    }
    break;
  }

  return true;
}

int main(int argc, char** argv)
{
  // Initialize Gstreamermm:
  Gst::init(argc, argv);

  mainloop = Glib::MainLoop::create();
  Glib::RefPtr<Gst::Pipeline> pipeline = Gst::Pipeline::create("audio-player");

  Glib::RefPtr<Gst::Element> source = Gst::ElementFactory::create_element("gltestsrc");
  if(!source)
    std::cerr << "gltestsrc element could not be created." << std::endl;

  Gst::Plugin::register_static(GST_VERSION_MAJOR, GST_VERSION_MINOR, "sampleglfilter",
    "sampleglfilter is an example of C++ element derived from Gst::GLFilter",
    sigc::ptr_fun(&SampleGLFilter::register_element), "0.123",
    "LGPL", "source?", "package?", "http://example.com");

  Glib::RefPtr<Gst::Element> filter = Gst::ElementFactory::create_element("sampleglfilter");
  if(!filter)
    std::cerr << "sampleglfilter element could not be created." << std::endl;

  Glib::RefPtr<Gst::Element> sink = Gst::ElementFactory::create_element("glimagesink");
  if(!sink)
    std::cerr << "glvideosink element could not be created." << std::endl;

  if(!pipeline || !source || !filter || !sink)
  {
    std::cerr << "One element could not be created" << std::endl;
    return 1;
  }

  Glib::RefPtr<Gst::Bus> bus = pipeline->get_bus();
  bus->add_watch( sigc::ptr_fun(&on_bus_message) );
  try
  {
    pipeline->add(source)->add(filter)->add(sink);
  }
  catch(const Glib::Error& ex)
  {
    std::cerr << "Error while adding elements to the pipeline: " << ex.what() << std::endl;
    return 1;
  }

  // Link the elements together:
  try
  {
    source->link(filter)->link(sink);
  }
  catch(const std::runtime_error& ex)
  {
    std::cout << "Exception while linking elements: " << ex.what() << std::endl;
  }

  // Now set the whole pipeline to playing and start the main loop:
  std::cout << "Setting to PLAYING." << std::endl;
  pipeline->set_state(Gst::STATE_PLAYING);
  std::cout << "Running." << std::endl;
  mainloop->run();

  // Clean up nicely:
  std::cout << "Returned. Stopping playback." << std::endl;
  pipeline->set_state(Gst::STATE_NULL);

  return 0;
}

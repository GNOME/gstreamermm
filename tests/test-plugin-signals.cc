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
#include <gstreamermm/fakesrc.h>
#include <gstreamermm/fakesink.h>
#include <iostream>

Glib::RefPtr<Glib::MainLoop> mainloop;

// This function is used to receive asynchronous messages in the main loop.
bool on_bus_message(const Glib::RefPtr<Gst::Bus>& /* bus */, const Glib::RefPtr<Gst::Message>& message)
{
  switch(message->get_message_type()) {
    case Gst::MESSAGE_EOS:
      std::cout << "End of stream." << std::endl;
      mainloop->quit();
      return false;
    case Gst::MESSAGE_ERROR:
    {

      Glib::RefPtr<Gst::MessageError> msgError =
              Glib::RefPtr<Gst::MessageError>::cast_dynamic(message);

      if(msgError)
      {
        Glib::Error err;
        err = msgError->parse();
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

void on_handoff(const Glib::RefPtr<Gst::Buffer>& buffer,
                const Glib::RefPtr<Gst::Pad>& pad)
{
  std::cout << "Gst::FakeSrc's handoff signal triggered." << std::endl;
}

int main(int argc, char* argv[])
{
  Gst::init(argc, argv);

  mainloop = Glib::MainLoop::create();

  // Create elements:
  Glib::RefPtr<Gst::Pipeline> pipeline = Gst::Pipeline::create("pipeline");
  Glib::RefPtr<Gst::FakeSrc> source = Gst::FakeSrc::create();
  Glib::RefPtr<Gst::FakeSink> sink = Gst::FakeSink::create();

  if(!pipeline || !source || !sink) {
    std::cerr << "One element could not be created" << std::endl;
    return -1;
  }

  // Put all elements in a bin:
  try
  {
    pipeline->add(source)->add(sink);
  }
  catch(const Glib::Error& ex)
  {
    std::cerr << "Error while adding elements to the pipeline: " <<
      ex.what() << std::endl;

    return -1;
  }

  // Link together:
  source->link(sink);

  // Add bus watch to pipeline bus to receive messages:
  pipeline->get_bus()->add_watch(sigc::ptr_fun(&on_bus_message));

  // Set number of buffers fakesink creates to low number:
  source->property_num_buffers() = 5;

  // Enable the fakesink handoff signal emition and connect slot:
  sink->property_signal_handoffs() = true;
  sink->signal_handoff().connect(sigc::ptr_fun(on_handoff));

  // Now set to playing and iterate:
  std::cout << "Setting to PLAYING." << std::endl;
  pipeline->set_state(Gst::STATE_PLAYING);
  std::cout << "Running." << std::endl;
  mainloop->run();

  // Clean up nicely:
  std::cout << "Returned. Stopping playback." << std::endl;
  pipeline->set_state(Gst::STATE_NULL);

  return 0;
}

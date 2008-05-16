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
#include <iostream>
#include <iomanip>

Glib::RefPtr<Glib::MainLoop> mainloop;
Glib::RefPtr<Gst::Pipeline> pipeline;
Glib::RefPtr<Gst::Element> decoder;
gulong data_probe_id = 0;

bool on_timeout()
{
  Gst::Format fmt = Gst::FORMAT_TIME;
  gint64 pos = 0;
  gint64 len = 0;

  Glib::RefPtr<Gst::Query> query = Gst::QueryPosition::create(fmt);

  if (pipeline->query(query)
    && pipeline->query_duration(fmt, len))
  {
    //TODO: Document why we do this cast:
    Glib::RefPtr<Gst::QueryPosition> query_pos =
      Glib::RefPtr<Gst::QueryPosition>::cast_dynamic(query);
    if(query_pos)
      query_pos->parse(fmt, pos);

    std::cout << std::right << "Time: " << std::setfill('0') <<
      std::setw(3) << Gst::get_hours(pos) << ":" <<
      std::setw(2) << Gst::get_minutes(pos) << ":" <<
      std::setw(2) << Gst::get_seconds(pos) << "." <<
      std::setw(9) << std::left << Gst::get_fractional_seconds(pos);

    std::cout << std::right << "/" <<
      std::setw(3) << Gst::get_hours(len) << ":" <<
      std::setw(2) << Gst::get_minutes(len) << ":" <<
      std::setw(2) << Gst::get_seconds(len) << "." <<
      std::setw(9) << std::left << Gst::get_fractional_seconds(len) <<
      std::endl << std::flush;
  }

  return true;
}

// This function is used to receive asynchronous messages in the main loop.
bool on_bus_message(const Glib::RefPtr<Gst::Bus>& /* bus_not_used */, const Glib::RefPtr<Gst::Message>& message)
{
  switch (message->get_message_type()) {
    case Gst::MESSAGE_EOS:
      std::cout << std::endl << "End of stream" << std::endl;
      mainloop->quit();
      return false;
    case Gst::MESSAGE_ERROR:
    {
      Glib::RefPtr<Gst::MessageError> msgError = Glib::RefPtr<Gst::MessageError>::cast_dynamic(message);
      if(msgError)
      {
        Glib::Error err;
        std::string debug; //TODO: Maybe this should be an optional parameter.
        msgError->parse(err, debug);
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

void on_parser_pad_added(const Glib::RefPtr<Gst::Pad>& newPad)
{
  // We can now link this pad with the audio decoder
  std::cout << "Dynamic pad created. Linking parser/decoder." << std::endl;
  Glib::RefPtr<Gst::Pad> sinkPad = decoder->get_pad("sink");
  newPad->link(sinkPad);
}

bool on_sink_pad_have_data(const Glib::RefPtr<Gst::Pad>& pad,
        const Glib::RefPtr<Gst::MiniObject>& data)
{
  std::cout << "Sink pad '" << pad->get_name() << "' has received data;";
  std::cout << " will now remove sink data probe id: " << data_probe_id << std::endl;
  pad->remove_data_probe(data_probe_id);
  return true;
}

int main(int argc, char* argv[])
{
  // check input arguments
  if (argc < 2)
  {
    std::cout << "Usage: " << argv[0] << " <Ogg/Vorbis filename>" << std::endl;
    return -1;
  }

  // Initialize Gstreamermm:
  Gst::init(argc, argv);

  mainloop = Glib::MainLoop::create();

  // Create the pipeline:
  pipeline = Gst::Pipeline::create("audio-player");
  std::cout << "pipeline=" << pipeline << std::endl;

  // Create the elements:

  // filsrc reads the file from disk:
  Glib::RefPtr<Gst::Element> source = Gst::ElementFactory::create_element("filesrc");
  std::cout << "source=" << source << std::endl;

  // oggdemux parses the ogg streams into elementary streams (audio and video):
  Glib::RefPtr<Gst::Element> parser = Gst::ElementFactory::create_element("oggdemux");
  std::cout << "parser=" << parser << std::endl;

  // vorbisdec decodes a vorbis (audio) stream:
  decoder = Gst::ElementFactory::create_element("vorbisdec", "vorbis-decoder");
  std::cout << "decoder=" << decoder << std::endl;

  // audioconvert converts raw audio to a format which can be used by the next element
  Glib::RefPtr<Gst::Element> conv = Gst::ElementFactory::create_element("audioconvert");
  std::cout << "conv=" << conv << std::endl;

  // Outputs sound to an ALSA audio device
  Glib::RefPtr<Gst::Element> sink = Gst::ElementFactory::create_element("alsasink");
  std::cout << "sink=" << sink << std::endl;

  if (!pipeline || !source || !parser || !decoder || !conv || !sink)
  {
    std::cerr << "One element could not be created" << std::endl;
    return -1;
  }

  data_probe_id = sink->get_pad("sink")->add_data_probe(
    sigc::ptr_fun(&on_sink_pad_have_data));
  std::cout << "sink data probe id = " << data_probe_id << std::endl;


  // Set filename property on the file source. Also add a message handler:
  source->set_property("location", std::string(argv[1]));

  // get the bus from the pipeline
  Glib::RefPtr<Gst::Bus> bus = pipeline->get_bus();

  // Add a bus watch to the default main context with the default priority.
  bus->add_watch( sigc::ptr_fun(&on_bus_message) );

  // Put all elements in a pipeline:
  try
  {
    pipeline->add(source)->add(parser)->add(decoder)->add(conv)->add(sink);
  }
  catch(const Glib::Error& ex)
  {
    std::cerr << "Error while adding elements to the pipeline: " << ex.what() << std::endl;
    return -1;
  }

  // Link together:
  source->link(parser);

  // We cannot link the parser and decoder yet, 
  // because the parser uses dynamic pads. For that,
  // we set a pad-added signal handler:
  parser->signal_pad_added().connect( sigc::ptr_fun(&on_parser_pad_added) );

  decoder->link(conv)->link(sink);

  // Call on_timeout function at a 200ms
  // interval to regularly print the position of the stream
  Glib::signal_timeout().connect(sigc::ptr_fun(&on_timeout), 200);

  // Now set to playing and iterate: TODO: What is iterated? Is the comment wrong?
  std::cout << "Setting to PLAYING." << std::endl;
  pipeline->set_state(Gst::STATE_PLAYING);
  std::cout << "Running." << std::endl;
  mainloop->run();

  // Clean up nicely:
  std::cout << "Returned. Stopping playback." << std::endl;
  pipeline->set_state(Gst::STATE_NULL);

  return 0;
}

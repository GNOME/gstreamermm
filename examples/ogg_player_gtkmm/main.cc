/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */

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

#include <gtkmm/main.h>
#include <gstreamermm/init.h>
#include <gstreamermm/element.h>
#include <gstreamermm/elementfactory.h>
#include <gstreamermm/pad.h>
#include <gstreamermm/pipeline.h>
#include <iostream>
#include "player_window.h"

Glib::RefPtr<Gst::Pipeline> pipeline;
Glib::RefPtr<Gst::Element> decoder;

void on_parser_pad_added(const Glib::RefPtr<Gst::Pad>& newPad)
{
  // We can now link this pad with the audio decoder.
  Glib::RefPtr<Gst::Pad> sinkPad = decoder->get_pad("sink");

  try
  {
    newPad->link(sinkPad);
  }
  catch(const std::runtime_error& ex)
  {
    std::cerr << "Exception caught while linking: " << ex.what() << std::endl;
  }
}

int
main (int argc, char *argv[])
{
  Gtk::Main kit(argc, argv);
  Gst::init(argc, argv);

  // Create the pipeline
  pipeline = Gst::Pipeline::create("audio-player");

  // Create the elements
  // Reads file from disk
  Glib::RefPtr<Gst::Element> source = Gst::ElementFactory::create_element("filesrc");
  if(!source)
  {
    std::cerr << "filesrc element could not be created" << std::endl;
    return -1;
  }

  // Parses the ogg streams into elementary streams (note that an ogg file may contain a video stream too)
  Glib::RefPtr<Gst::Element> parser = Gst::ElementFactory::create_element("oggdemux");
  if(!parser)
  {
    std::cerr << "oggdemux element could not be created" << std::endl;
    return -1;
  }

  // Decodes a vorbis stream
  decoder = Gst::ElementFactory::create_element("vorbisdec");
  if(!decoder)
  {
    std::cerr << "vorbisdec element could not be created" << std::endl;
    return -1;
  }

  // Converts audio to a format which can be used by the next element
  Glib::RefPtr<Gst::Element> conv = Gst::ElementFactory::create_element("audioconvert");
  if(!conv)
  {
    std::cerr << "audioconvert element could not be created" << std::endl;
    return -1;
  }

  // Outputs sound to an ALSA audio device
  Glib::RefPtr<Gst::Element> sink = Gst::ElementFactory::create_element("alsasink");
  if(!sink)
  {
    std::cerr << "sink element could not be created" << std::endl;
    return -1;
  }


  // Put all elements in a pipeline:
  try
  {
    pipeline->add(source)->add(parser)->add(decoder)->add(conv)->add(sink);
  }
  catch(const std::runtime_error& ex)
  {
    std::cerr << "Error while adding elements to the pipeline: " << ex.what() << std::endl;
    return -1;
  }


  // Link the elements together:
  try
  {
    source->link(parser);

    // We cannot link the parser and decoder yet, 
    // because the parser uses dynamic pads.
    // So we do it later in a pad-added signal handler:
    parser->signal_pad_added().connect( sigc::ptr_fun(&on_parser_pad_added) );

    decoder->link(conv)->link(sink);
  }
  catch(const std::runtime_error& ex)
  {
    std::cout << "Exception while linking elements: " << ex.what() << std::endl;
  }

  // Create our window and show it:
  PlayerWindow mainWindow(source, pipeline);
  kit.run(mainWindow);

  // Clean up nicely:
  pipeline->set_state(Gst::STATE_NULL);

  return 0;
}

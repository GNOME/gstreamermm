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
  // We can now link this pad with the audio decoder
  Glib::RefPtr<Gst::Pad> sinkPad = decoder->get_pad("sink");
  newPad->link(sinkPad);
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

  // Parses the ogg streams into elementary streams (note that an ogg file may contain a video stream too)
  Glib::RefPtr<Gst::Element> parser = Gst::ElementFactory::create_element("oggdemux");

  // Decodes a vorbis stream
  decoder = Gst::ElementFactory::create_element("vorbisdec", "vorbis-decoder");

  // Converts audio() to a format which can be used by the next element
  Glib::RefPtr<Gst::Element> conv = Gst::ElementFactory::create_element("audioconvert");

  // Outputs sound to an ALSA audio device
  Glib::RefPtr<Gst::Element> sink = Gst::ElementFactory::create_element("alsasink");

  if (!pipeline || !source || !parser || !decoder || !conv || !sink)
  {
    std::cerr << "One element could not be created" << std::endl;
    return -1;
  }

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

  PlayerWindow mainWindow(source, pipeline);

  kit.run(mainWindow);

  // Clean up nicely:
  pipeline->set_state(Gst::STATE_NULL);

  return 0;
}

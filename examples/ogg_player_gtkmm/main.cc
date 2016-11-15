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
#include <gstreamermm/elementfactory.h>
#include <gstreamermm/pad.h>
#include <gstreamermm/pipeline.h>

// Plug-ins
#include <gstreamermm/alsasink.h>
#include <gstreamermm/audioconvert.h>
#include <gstreamermm/filesrc.h>
#include <gstreamermm/oggdemux.h>
#include <gstreamermm/vorbisdec.h>

#include <iostream>
#include "player_window.h"

Glib::RefPtr<Gst::Pipeline> pipeline;

#ifndef GSTREAMERMM_DISABLE_DEPRECATED
Glib::RefPtr<Gst::VorbisDec> decoder;
#else
Glib::RefPtr<Gst::Element> decoder;
#endif

void on_parser_pad_added(const Glib::RefPtr<Gst::Pad>& newPad)
{
  // We can now link this pad with the audio decoder.
  Glib::RefPtr<Gst::Pad> sinkPad = decoder->get_static_pad("sink");
  Gst::PadLinkReturn ret = newPad->link(sinkPad);

  if (ret != Gst::PAD_LINK_OK && ret != Gst::PAD_LINK_WAS_LINKED)
  {
    std::cerr << "Linking of pads " << newPad->get_name() << " and " <<
      sinkPad->get_name() << " failed." << std::endl;
  }
}

int main(int argc, char** argv)
{
  Gtk::Main kit(argc, argv);
  Gst::init(argc, argv);

  // Create the pipeline
  pipeline = Gst::Pipeline::create("audio-player");

  // Create the elements
  // Reads file from disk
#ifndef GSTREAMERMM_DISABLE_DEPRECATED
  Glib::RefPtr<Gst::FileSrc> source = Gst::FileSrc::create();
#else
  Glib::RefPtr<Gst::Element> source = Gst::ElementFactory::create_element("filesrc");
#endif
  if(!source)
  {
    std::cerr << "filesrc element could not be created" << std::endl;
    return 1;
  }

  // Parses the ogg streams into elementary streams (note that an ogg file may
  // contain a video stream too)
#ifndef GSTREAMERMM_DISABLE_DEPRECATED
  Glib::RefPtr<Gst::OggDemux> parser = Gst::OggDemux::create();
#else
  Glib::RefPtr<Gst::Element> parser = Gst::ElementFactory::create_element("oggdemux");
#endif
  if(!parser)
  {
    std::cerr << "oggdemux element could not be created" << std::endl;
    return 1;
  }

  // Decodes a vorbis stream
#ifndef GSTREAMERMM_DISABLE_DEPRECATED
  decoder = Gst::VorbisDec::create();
#else
  decoder = Gst::ElementFactory::create_element("vorbisdec");
#endif
  
  if(!decoder)
  {
    std::cerr << "vorbisdec element could not be created" << std::endl;
    return 1;
  }

  // Converts audio to a format which can be used by the next element
#ifndef GSTREAMERMM_DISABLE_DEPRECATED
  Glib::RefPtr<Gst::AudioConvert> conv = Gst::AudioConvert::create();
#else
  Glib::RefPtr<Gst::Element> conv = Gst::ElementFactory::create_element("audioconvert");
#endif

  if(!conv)
  {
    std::cerr << "audioconvert element could not be created" << std::endl;
    return 1;
  }

  // Outputs sound to an ALSA audio device
#ifndef GSTREAMERMM_DISABLE_DEPRECATED
  Glib::RefPtr<Gst::AlsaSink> sink = Gst::AlsaSink::create();
#else
  Glib::RefPtr<Gst::Element> sink = Gst::ElementFactory::create_element("alsasink");
#endif
  if(!sink)
  {
    std::cerr << "sink element could not be created" << std::endl;
    return 1;
  }


  // Put all elements in a pipeline:
  try
  {
    pipeline->add(source)->add(parser)->add(decoder)->add(conv)->add(sink);
  }
  catch(const std::runtime_error& ex)
  {
    std::cerr << "Error while adding elements to the pipeline: " << ex.what() << std::endl;
    return 1;
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

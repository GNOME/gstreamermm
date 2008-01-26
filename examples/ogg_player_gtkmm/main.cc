/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * main.cc
 * Copyright (C) The gstmm development team 2007 <gtkmm-list@gnome.org>
 * 
 * main.cc is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * main.cc is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <gtkmm/main.h>
#include <gstreamermm/init.h>
#include <gstreamermm/element.h>
#include <gstreamermm/pad.h>
#include <gstreamermm/pipeline.h>
#include <iostream>
#include "PlayerWindow.h"

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
    Glib::RefPtr<Gst::Element> source = Gst::Element::create("filesrc", "file-source");

    // Parses the ogg streams into elementary streams (note that an ogg file may contain a video stream too)
    Glib::RefPtr<Gst::Element> parser = Gst::Element::create("oggdemux", "ogg-parser");

    // Decodes a vorbis stream
    decoder = Gst::Element::create("vorbisdec", "vorbis-decoder");

    // Converts audio() to a format which can be used by the next element
    Glib::RefPtr<Gst::Element> conv = Gst::Element::create("audioconvert", "converter");

    // Outputs sound to an ALSA audio device
    Glib::RefPtr<Gst::Element> sink = Gst::Element::create("alsasink", "alsa-output");

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

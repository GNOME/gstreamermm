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
#include "PlayerWindow.h"

int
main (int argc, char *argv[])
{
    Gtk::Main kit(argc, argv);
    Gst::init(argc, argv);

    // Create the pipeline
    Glib::RefPtr<Gst::Pipeline> pipeline = Gst::Pipeline::create("media-player");

    // Create the elements

    // Autoplays any media type.  Implements GstBase::XOverlay so accepts
    // a window id in which to draw video
    Glib::RefPtr<Gst::Element> playbin = Gst::ElementFactory::create("playbin", "media-playbin");

    if (!pipeline || !playbin)
    {
        std::cerr << "One element could not be created" << std::endl;
        return -1;
    }

    // Put elements in a pipeline:
    try
    {
        pipeline->add(playbin);
    }
    catch(const Glib::Error& ex)
    {
        std::cerr << "Error while adding elements to the pipeline: " << ex.what() << std::endl;
        return -1;
    }

    PlayerWindow mainWindow(playbin, pipeline);

    kit.run(mainWindow);

    // Clean up nicely:
    pipeline->set_state(Gst::STATE_NULL);

    return 0;
}

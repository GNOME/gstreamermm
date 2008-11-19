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
#include <gstreamerbasemm/init.h>
#include <gstreamermm/element.h>
#include <gstreamermm/elementfactory.h>
#include <gstreamermm/pad.h>
#include <gstreamermm/pipeline.h>
#include <iostream>
#include "player_window.h"

int
main (int argc, char *argv[])
{
  Gtk::Main kit(argc, argv);

  // Use GstBase::init() instead of Gst::init() because some of its API
  // (i.e. GstBase::XOverlay in player_window.cc) is used:
  GstBase::init(argc, argv);

  // Create the elements:

  // playbin plays any media type, choosing an appropriate set of elements
  // and linking them together.
  // playbin implements GstBase::XOverlay so it accepts a window id in which 
  // to draw video.
  Glib::RefPtr<Gst::Element> playbin = Gst::ElementFactory::create_element("playbin");

  //The playbin element is actually a pipeline:
  Glib::RefPtr<Gst::Pipeline> pipeline = Glib::RefPtr<Gst::Pipeline>::cast_dynamic(playbin);
  if(!pipeline)
  {
    std::cerr << "The playbin could not be created." << std::endl;
    return -1;
  }

  // Create a video sink where video (if any) will be drawn:
  Glib::RefPtr<Gst::Element> video_sink = Gst::ElementFactory::create_element("ximagesink");
  if (!video_sink)
  {
    std::cerr << "The ximagesink could not be created." << std::endl;
    return -1;
  }

  // Set the playbin's video-sink property so that our video sink is used for video display:
  // TODO: Create a PlayBin class that we can dynamic_cast<> to, so we can use property_video_sink()?
  pipeline->set_property("video-sink", video_sink);

  //Create our player window and give it the pipeline and video sink:
  PlayerWindow mainWindow(pipeline, video_sink);
  kit.run(mainWindow);

  // Clean up nicely:
  pipeline->set_state(Gst::STATE_NULL);

  return 0;
}

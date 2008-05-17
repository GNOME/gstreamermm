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

#ifndef _PLAYERWINDOW_H
#define _PLAYERWINDOW_H

#include <gtkmm/window.h>
#include <gtkmm/drawingarea.h>
#include <gtkmm/buttonbox.h>
#include <gtkmm/label.h>
#include <gtkmm/button.h>
#include <gtkmm/scale.h>
#include <gstreamermm/element.h>
#include <gstreamermm/pipeline.h>
#include <gstreamermm/bus.h>

class PlayerWindow : public Gtk::Window
{
public:
  /**
   * @param playbin The pipeline that can play media files.
   * @param video_sink
   */
  PlayerWindow(const Glib::RefPtr<Gst::Pipeline>& playbin, const Glib::RefPtr<Gst::Element>& video_sink);
  virtual ~PlayerWindow();

protected:

  //Signal handlers:
  Gst::BusSyncReply on_bus_message_sync(const Glib::RefPtr<Gst::Bus>& bus, const Glib::RefPtr<Gst::Message>& message);
  bool on_bus_message(const Glib::RefPtr<Gst::Bus>& bus, const Glib::RefPtr<Gst::Message>& message);
  bool on_video_pad_got_buffer(const Glib::RefPtr<Gst::Pad>& pad, const Glib::RefPtr<Gst::MiniObject>& buffer);

  void on_button_play();
  void on_button_pause();
  void on_button_stop();
  void on_button_rewind();
  void on_button_forward();
  void on_button_open();
  bool on_scale_value_changed(Gtk::ScrollType type, double value);
  bool on_timeout();

  void display_label_progress(gint64 pos, gint64 len);

protected:
  Gtk::VBox m_vbox;
  Gtk::HButtonBox m_button_box;
  Gtk::DrawingArea m_video_area;
  Gtk::Label m_progress_label;
  Gtk::HScale m_progress_scale;
  Gtk::Button m_play_button;
  Gtk::Button m_pause_button;
  Gtk::Button m_stop_button;
  Gtk::Button m_rewind_button;
  Gtk::Button m_forward_button;
  Gtk::Button m_open_button;

  Glib::RefPtr<Gst::Pipeline> m_play_bin;
  Glib::RefPtr<Gst::Element> m_video_sink;
  sigc::connection m_timeout_connection;
  guint m_watch_id;
  gint64 m_duration;
  gulong m_pad_probe_id;
};

#endif /* _PLAYERWINDOW_H */

 

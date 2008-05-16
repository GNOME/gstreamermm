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
    PlayerWindow(const Glib::RefPtr<Gst::Pipeline>& playbin,
            const Glib::RefPtr<Gst::Element>& videoSink);

    ~PlayerWindow();
protected:
    Gtk::VBox vBox;
    Gtk::HButtonBox buttonBox;
    Gtk::DrawingArea videoArea;
    Gtk::Label progressLabel;
    Gtk::HScale progressScale;
    Gtk::Button playButton;
    Gtk::Button pauseButton;
    Gtk::Button stopButton;
    Gtk::Button rewindButton;
    Gtk::Button forwardButton;
    Gtk::Button openButton;
protected:
    virtual Gst::BusSyncReply on_bus_message_sync(
        const Glib::RefPtr<Gst::Bus>& bus,
        const Glib::RefPtr<Gst::Message>& message);

    virtual bool on_bus_message(const Glib::RefPtr<Gst::Bus>& bus,
                            const Glib::RefPtr<Gst::Message>& message);

    virtual bool on_video_pad_got_buffer(const Glib::RefPtr<Gst::Pad>& pad,
                            const Glib::RefPtr<Gst::MiniObject>& buffer);

    virtual void on_play();
    virtual void on_pause();
    virtual void on_stop();
    virtual bool on_scale_value_changed(Gtk::ScrollType type, double value);
    virtual void on_rewind();
    virtual void on_forward();
    virtual void on_open();
protected:
    bool update_stream_progress();
    void display_label_progress(gint64 pos, gint64 len);
private:
    Glib::RefPtr<Gst::Pipeline> playbin;
    Glib::RefPtr<Gst::Element> videoSink;
    sigc::connection progressConnection;
    guint watch_id;
    gint64 duration;
    gulong pad_probe_id;
};

#endif /* _PLAYERWINDOW_H */

 

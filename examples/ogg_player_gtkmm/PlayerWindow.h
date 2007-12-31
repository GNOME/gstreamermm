/***************************************************************************
 *            PlayerWindow.h
 *
 *  Tue Dec 18 18:48:33 2007
 *  Copyright  2007  The gstmm development team
 *  <gtkmm-list@gnome.org>
 ****************************************************************************/

/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Library General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor Boston, MA 02110-1301,  USA
 */
 
#ifndef _PLAYERWINDOW_H
#define _PLAYERWINDOW_H

#include <gtkmm/window.h>
#include <gtkmm/box.h>
#include <gtkmm/buttonbox.h>
#include <gtkmm/label.h>
#include <gtkmm/button.h>
#include <gtkmm/scale.h>
#include <gstmm/element.h>
#include <gstmm/pipeline.h>

class PlayerWindow : public Gtk::Window
{
public:
    PlayerWindow(Glib::RefPtr<Gst::Element> sourceElement,
                 Glib::RefPtr<Gst::Pipeline> mainPipeline);
protected:
    Gtk::VBox vBox;
    Gtk::HButtonBox buttonBox;
    Gtk::Label progressLabel;
    Gtk::HScale progressScale;
    Gtk::Button playButton;
    Gtk::Button pauseButton;
    Gtk::Button stopButton;
    Gtk::Button rewindButton;
    Gtk::Button forwardButton;
    Gtk::Button openButton;
protected:
    virtual bool on_bus_message(const Glib::RefPtr<Gst::Bus>& bus,
                            const Glib::RefPtr<Gst::Message>& message);
    virtual void on_play(void);
    virtual void on_pause(void);
    virtual void on_stop(void);
    virtual bool on_scale_value_changed(Gtk::ScrollType type, double value);
    virtual void on_rewind(void);
    virtual void on_forward(void);
    virtual void on_open(void);
protected:
    bool update_stream_progress(void);
    void display_label_progress(gint64 pos, gint64 len);
private:
    Glib::RefPtr<Gst::Element> sourceElement;
    Glib::RefPtr<Gst::Pipeline> mainPipeline;
    gint64 duration;
    sigc::connection progressConnection;
};

#endif /* _PLAYERWINDOW_H */

 

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

#include <gtkmm/stock.h>
#include <gtkmm/filechooserdialog.h>
#include <gstreamermm/bus.h>
#include <gstreamermm/clock.h>
#include <gstreamermm/event.h>
#include <gstreamermm/message.h>
#include <gstreamermm/query.h>
#include <iostream>
#include <sstream>
#include <iomanip>
#include "PlayerWindow.h"

PlayerWindow::PlayerWindow(Glib::RefPtr<Gst::Element> sourceElement,
                                Glib::RefPtr<Gst::Pipeline> mainPipeline) :
vBox(false, 5),
progressLabel("000:00:00.000000000 / 000:00:00.000000000"),
playButton(Gtk::Stock::MEDIA_PLAY),
pauseButton(Gtk::Stock::MEDIA_PAUSE),
stopButton(Gtk::Stock::MEDIA_STOP),
rewindButton(Gtk::Stock::MEDIA_REWIND),
forwardButton(Gtk::Stock::MEDIA_FORWARD),
openButton(Gtk::Stock::OPEN)
{
    set_title("gstreamermm Ogg Player Example");

    add(vBox);
    vBox.pack_start(progressLabel);
    vBox.pack_start(progressScale);
    vBox.pack_start(buttonBox);

    progressLabel.set_alignment(Gtk::ALIGN_CENTER);

    progressScale.set_range(0, 1);
    progressScale.set_draw_value(false);
    progressScale.signal_change_value().connect(
                sigc::mem_fun(*this, &PlayerWindow::on_scale_value_changed));

    buttonBox.pack_start(playButton);
    buttonBox.pack_start(pauseButton);
    buttonBox.pack_start(stopButton);
    buttonBox.pack_start(rewindButton);
    buttonBox.pack_start(forwardButton);
    buttonBox.pack_start(openButton);

    playButton.signal_clicked().connect(sigc::mem_fun(*this,
                                          &PlayerWindow::on_play));
    pauseButton.signal_clicked().connect(sigc::mem_fun(*this,
                                          &PlayerWindow::on_pause));
    stopButton.signal_clicked().connect(sigc::mem_fun(*this,
                                          &PlayerWindow::on_stop));
    rewindButton.signal_clicked().connect(sigc::mem_fun(*this,
                                          &PlayerWindow::on_rewind));
    forwardButton.signal_clicked().connect(sigc::mem_fun(*this,
                                          &PlayerWindow::on_forward));
    openButton.signal_clicked().connect(sigc::mem_fun(*this,
                                          &PlayerWindow::on_open));

    // get the bus from the pipeline
    Glib::RefPtr<Gst::Bus> bus = mainPipeline->get_bus();

    // Add a bus watch to receive messages from pipeline's bus
    watch_id = bus->add_watch(
        sigc::mem_fun( *this, &PlayerWindow::on_bus_message) );

    progressScale.set_sensitive(false);
    playButton.set_sensitive(false);
    pauseButton.set_sensitive(false);
    stopButton.set_sensitive(false);
    rewindButton.set_sensitive(false);
    forwardButton.set_sensitive(false);

    this->sourceElement = sourceElement;
    this->mainPipeline = mainPipeline;

    show_all_children();
    pauseButton.hide();
}

// This function is used to receive asynchronous messages from mainPipeline's bus
bool PlayerWindow::on_bus_message(const Glib::RefPtr<Gst::Bus>& /* bus_not_used */,
					const Glib::RefPtr<Gst::Message>& message)
{
    switch (message->get_message_type())
    {
        case Gst::MESSAGE_EOS:
            on_stop();
            break;
        case Gst::MESSAGE_ERROR:
        {
            Glib::RefPtr<Gst::MessageError> msgError =
                Glib::RefPtr<Gst::MessageError>::cast_dynamic(message);
            if(msgError)
            {
                Glib::Error err;
                std::string debug; //TODO: Maybe this should be an optional parameter.
                msgError->parse(err, debug);
                std::cerr << "Error: " << err.what() << std::endl;
            }
            else
                std::cerr << "Error." << std::endl;

            on_stop();
            break;
        }
        default:
        {
        //std::cout << "debug: on_bus_message: unhandled message=" << G_OBJECT_TYPE_NAME(message->gobj()) << std::endl;
        }
        break;
    }

    return true;
}

void PlayerWindow::on_play()
{
    progressScale.set_sensitive(true);
    playButton.set_sensitive(false);
    pauseButton.set_sensitive(true);
    stopButton.set_sensitive(true);
    rewindButton.set_sensitive(true);
    forwardButton.set_sensitive(true);
    openButton.set_sensitive(false);

    playButton.hide();
    pauseButton.show();

	// Call update_stream_progress function at a 200ms
	// interval to regularly update the position of the stream
	progressConnection = Glib::signal_timeout().connect(sigc::mem_fun(*this,
                             &PlayerWindow::update_stream_progress), 200);

    // set Gstmm pipeline to play mode
	mainPipeline->set_state(Gst::STATE_PLAYING);
}
 
void PlayerWindow::on_pause()
{
    playButton.set_sensitive(true);
    pauseButton.set_sensitive(false);

    pauseButton.hide();
    playButton.show();

    // disconnect progress callback
    progressConnection.disconnect();
    
    // set Gstmm pipeline to pause mode
	mainPipeline->set_state(Gst::STATE_PAUSED);
}
 
void PlayerWindow::on_stop()
{
    progressScale.set_sensitive(false);
    playButton.set_sensitive(true);
    pauseButton.set_sensitive(false);
    stopButton.set_sensitive(false);
    rewindButton.set_sensitive(false);
    forwardButton.set_sensitive(false);
    openButton.set_sensitive(true);

    pauseButton.hide();
    playButton.show();

    // disconnect progress callback
    progressConnection.disconnect();

    // set Gstmm pipeline to inactive mode
	mainPipeline->set_state(Gst::STATE_NULL);
    display_label_progress(0, duration);
    progressScale.set_value(0);
}

bool PlayerWindow::on_scale_value_changed(Gtk::ScrollType /* type_not_used */, double value)
{
    gint64 newPos = gint64(value * duration);

    if (mainPipeline->seek(Gst::FORMAT_TIME, Gst::SEEK_FLAG_FLUSH, newPos))
    {
        display_label_progress(newPos, duration);
        return true;
    }
    else
    {
        std::cerr << "Could not seek!" << std::endl;
        return false;
    }
}

void PlayerWindow::on_rewind()
{
    static const gint64 skipAmount = GST_SECOND * 2;

    gint64 pos;
    Gst::Format fmt = Gst::FORMAT_TIME;

    if (mainPipeline->query_position(fmt, pos))
    {
        gint64 newPos = (pos > skipAmount) ? (pos - skipAmount) : 0;

        if (mainPipeline->seek(Gst::FORMAT_TIME, Gst::SEEK_FLAG_FLUSH, newPos)) {
            display_label_progress(newPos, duration);
            progressScale.set_value(double(newPos) / duration);
        }
        else
            std::cerr << "Could not seek!" << std::endl;
    }
}

void PlayerWindow::on_forward()
{
    static const gint64 skipAmount = GST_SECOND * 3;

    gint64 pos;
    Gst::Format fmt = Gst::FORMAT_TIME;

    Glib::RefPtr<Gst::Query> query = Gst::QueryPosition::create(fmt);

    if (mainPipeline->query(query))
    {
        Glib::RefPtr<Gst::QueryPosition> posQuery =
            Glib::RefPtr<Gst::QueryPosition>::cast_dynamic(query);

        posQuery->parse(fmt, pos);

        gint64 newPos = ((pos + skipAmount) < duration) ? (pos + skipAmount) :
            duration;

        Glib::RefPtr<Gst::Event> event = Gst::EventSeek::create(1.0, fmt,
                Gst::SEEK_FLAG_FLUSH, Gst::SEEK_TYPE_SET, newPos,
                Gst::SEEK_TYPE_NONE, -1);

        Glib::RefPtr<Gst::EventSeek> seekEvent =
            Glib::RefPtr<Gst::EventSeek>::cast_dynamic(event);

        if (mainPipeline->send_event(seekEvent))
        {
            progressScale.set_value(double(newPos) / duration);
            display_label_progress(newPos, duration);
        }
        else
            std::cerr << "Could not seek!" << std::endl;
    }
}

void PlayerWindow::on_open()
{
    static Glib::ustring workingDir = Glib::get_home_dir();
    
    Gtk::FileChooserDialog chooser(*this,
                        "Select ogg file", Gtk::FILE_CHOOSER_ACTION_OPEN);

    Gtk::FileFilter filter;
    filter.add_mime_type("application/ogg");
    filter.set_name("Ogg files");

    chooser.set_filter(filter);

    chooser.add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
    chooser.add_button(Gtk::Stock::OK, Gtk::RESPONSE_OK);
    
    chooser.set_current_folder(workingDir);
    
    int response = chooser.run();
    
    if (response == Gtk::RESPONSE_OK) {
        workingDir = chooser.get_current_folder();

        // Set filename property on the file source. Also add a message handler:
        sourceElement->set_property("location", chooser.get_filename());
        set_title(Glib::filename_display_basename(chooser.get_filename()));

        playButton.set_sensitive(true);
        display_label_progress(0, 0);
    }
}

bool PlayerWindow::update_stream_progress()
{
    Gst::Format fmt = Gst::FORMAT_TIME;
    gint64 pos = 0;

    if (mainPipeline->query_position(fmt, pos)
    && mainPipeline->query_duration(fmt, duration)) {
        progressScale.set_value(double(pos) / duration);
        display_label_progress(pos, duration);
    }

   return true;
}

void PlayerWindow::display_label_progress(gint64 pos, gint64 len)
{
    std::ostringstream locationStream (std::ostringstream::out);
    std::ostringstream durationStream (std::ostringstream::out);

    locationStream << std::right << std::setfill('0') << 
        std::setw(3) << Gst::get_hours(pos) << ":" <<
        std::setw(2) << Gst::get_minutes(pos) << ":" <<
        std::setw(2) << Gst::get_seconds(pos) << "." <<
        std::setw(9) << std::left << Gst::get_fractional_seconds(pos);

    durationStream << std::right << std::setfill('0') <<
        std::setw(3) << Gst::get_hours(len) << ":" <<
        std::setw(2) << Gst::get_minutes(len) << ":" <<
        std::setw(2) << Gst::get_seconds(len) << "." <<
        std::setw(9) << std::left << Gst::get_fractional_seconds(len);

    progressLabel.set_text(locationStream.str() + " / " + durationStream.str());
}

PlayerWindow::~PlayerWindow()
{
  mainPipeline->get_bus()->remove_watch(watch_id);
}

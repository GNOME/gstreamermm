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
#include <gdk/gdkx.h>
#include <gstreamermm/bus.h>
#include <gstreamermm/caps.h>
#include <gstreamermm/clock.h>
#include <gstreamermm/buffer.h>
#include <gstreamermm/event.h>
#include <gstreamermm/message.h>
#include <gstreamermm/query.h>
#include <gstreamermm/interface.h>
#include <gstreamerbasemm/xoverlay.h>
#include <iostream>
#include <sstream>
#include <iomanip>
#include "PlayerWindow.h"

PlayerWindow::PlayerWindow(const Glib::RefPtr<Gst::Pipeline>& playbin,
        const Glib::RefPtr<Gst::Element>& videoSink) :
vBox(false, 5),
progressLabel("000:00:00.000000000 / 000:00:00.000000000"),
playButton(Gtk::Stock::MEDIA_PLAY),
pauseButton(Gtk::Stock::MEDIA_PAUSE),
stopButton(Gtk::Stock::MEDIA_STOP),
rewindButton(Gtk::Stock::MEDIA_REWIND),
forwardButton(Gtk::Stock::MEDIA_FORWARD),
openButton(Gtk::Stock::OPEN)
{
    set_title("gstreamermm Media Player Example");

    add(vBox);
    vBox.pack_start(videoArea, Gtk::PACK_EXPAND_WIDGET);
    vBox.pack_start(progressLabel, Gtk::PACK_SHRINK);
    vBox.pack_start(progressScale, Gtk::PACK_SHRINK);
    vBox.pack_start(buttonBox, Gtk::PACK_SHRINK);

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
    Glib::RefPtr<Gst::Bus> bus = playbin->get_bus();

    // Add a sync handler to receive synchronous messages from pipeline's
    // bus (this is done so that videoArea can be set up for drawing at an
    // exact appropriate time
    bus->set_sync_handler(
        sigc::mem_fun(*this, &PlayerWindow::on_bus_message_sync));

    // Add a bus watch to receive messages from pipeline's bus
    watch_id = bus->add_watch(
        sigc::mem_fun(*this, &PlayerWindow::on_bus_message) );

    progressScale.set_sensitive(false);
    playButton.set_sensitive(false);
    pauseButton.set_sensitive(false);
    stopButton.set_sensitive(false);
    rewindButton.set_sensitive(false);
    forwardButton.set_sensitive(false);

    this->playbin = playbin;
    this->videoSink = videoSink;

    show_all_children();
    pauseButton.hide();
}

// This function is used to receive asynchronous messages from mainPipeline's bus
Gst::BusSyncReply PlayerWindow::on_bus_message_sync(
        const Glib::RefPtr<Gst::Bus>& /* bus_not_used */,
        const Glib::RefPtr<Gst::Message>& message)
{
    // ignore anything but 'prepare-xwindow-id' element messages
    if (message->get_message_type() != Gst::MESSAGE_ELEMENT)
        return Gst::BUS_PASS;

    if (!message->get_structure()->has_name("prepare-xwindow-id"))
       return Gst::BUS_PASS;

    Glib::RefPtr<Gst::Element> element =
            Glib::RefPtr<Gst::Element>::cast_dynamic(message->get_source());

    Glib::RefPtr< Gst::ElementInterfaced<GstBase::XOverlay> > xoverlay =
            Gst::Interface::cast <GstBase::XOverlay>(element);

    if (xoverlay)
    {
        gulong xWindowId = GDK_WINDOW_XID(videoArea.get_window()->gobj());
        xoverlay->set_xwindow_id(xWindowId);
    }

    return Gst::BUS_DROP;
}

// This function is used to receive asynchronous messages from playbin's bus
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

bool PlayerWindow::on_video_pad_got_buffer(const Glib::RefPtr<Gst::Pad>& pad,
        const Glib::RefPtr<Gst::MiniObject>& data)
{
    Glib::RefPtr<Gst::Buffer> buffer = Glib::RefPtr<Gst::Buffer>::cast_dynamic(data);

    if (buffer) {
        Glib::Value<int> widthValue;
        Glib::Value<int> heightValue;

        Glib::RefPtr<Gst::Caps> caps = buffer->get_caps();
        caps->get_structure(0)->get_field("width", widthValue);
        caps->get_structure(0)->get_field("height", heightValue);

        videoArea.set_size_request(widthValue.get(), heightValue.get());
        resize(1, 1);       // Resize to minimum when first playing by making size
        check_resize();     // smallest then resizing according to video new size
    }

    pad->remove_buffer_probe(pad_probe_id);
    pad_probe_id = 0; // Clear probe id to indicate that it has been removed

    return true; // Keep buffer in pipeline (do not throw away)
}

void PlayerWindow::on_play(void)
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
	playbin->set_state(Gst::STATE_PLAYING);
}
 
void PlayerWindow::on_pause(void)
{
    playButton.set_sensitive(true);
    pauseButton.set_sensitive(false);

    pauseButton.hide();
    playButton.show();

    // disconnect progress callback
    progressConnection.disconnect();
    
    // set Gstmm pipeline to pause mode
	playbin->set_state(Gst::STATE_PAUSED);
}
 
void PlayerWindow::on_stop(void)
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
	playbin->set_state(Gst::STATE_NULL);

    // reset display
    display_label_progress(0, duration);
    progressScale.set_value(0);

    // Remove video sink pad buffer probe if after playing, probe id is
    // not zero (means probe was not removed because media had no video and
    // video_pad_got_buffer method never got a chance to remove probe)
    if (pad_probe_id != 0)
    {
        videoSink->get_pad("sink")->remove_buffer_probe(pad_probe_id);
        pad_probe_id  = 0;
    }
}

bool PlayerWindow::on_scale_value_changed(Gtk::ScrollType /* type_not_used */, double value)
{
    gint64 newPos = gint64(value * duration);

    if (playbin->seek(Gst::FORMAT_TIME, Gst::SEEK_FLAG_FLUSH, newPos))
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

void PlayerWindow::on_rewind(void)
{
    static const gint64 skipAmount = GST_SECOND * 2;

    gint64 pos;
    Gst::Format fmt = Gst::FORMAT_TIME;

    if (playbin->query_position(fmt, pos))
    {
        gint64 newPos = (pos > skipAmount) ? (pos - skipAmount) : 0;

        if (playbin->seek(Gst::FORMAT_TIME, Gst::SEEK_FLAG_FLUSH, newPos)) {
            progressScale.set_value(double(newPos) / duration);
            display_label_progress(newPos, duration);
        }
        else
            std::cerr << "Could not seek!" << std::endl;
    }
}

void PlayerWindow::on_forward(void)
{
    static const gint64 skipAmount = GST_SECOND * 3;

    gint64 pos;
    Gst::Format fmt = Gst::FORMAT_TIME;

    Glib::RefPtr<Gst::Query> query = Gst::QueryPosition::create(fmt);

    if (playbin->query(query))
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

        if (playbin->send_event(seekEvent))
        {
            progressScale.set_value(double(newPos) / duration);
            display_label_progress(newPos, duration);
        }
        else
            std::cerr << "Could not seek!" << std::endl;
    }
}

void PlayerWindow::on_open(void)
{
    static Glib::ustring workingDir = Glib::get_home_dir();
    
    Gtk::FileChooserDialog chooser(*this,
                        "Select a media file", Gtk::FILE_CHOOSER_ACTION_OPEN);

    chooser.add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
    chooser.add_button(Gtk::Stock::OK, Gtk::RESPONSE_OK);
    
    chooser.set_current_folder(workingDir);
    
    int response = chooser.run();
    
    if (response == Gtk::RESPONSE_OK) {
        workingDir = chooser.get_current_folder();

        // Set uri property on the playbin.
        Glib::RefPtr<Gst::Element>::cast_dynamic(playbin)->
                set_property("uri", chooser.get_uri());

        // Resize videoArea and window to minimum when opening a file
        videoArea.set_size_request(0, 0);
        resize(1, 1);

        // Add buffer probe to video sink pad when file is opened which will
        // be removed after first buffer is received in on_video_pad_got_buffer
        // method (if there's video).  When first buffer arrives, video
        // size can be extracted.  If there's no video, probe will be
        // removed when media stops in on_stop method
        pad_probe_id = videoSink->get_pad("sink")->add_buffer_probe(
            sigc::mem_fun(*this, &PlayerWindow::on_video_pad_got_buffer));

        set_title(Glib::filename_display_basename(chooser.get_filename()));

        playButton.set_sensitive(true);
        display_label_progress(0, 0);
    }
}

bool PlayerWindow::update_stream_progress(void)
{
    Gst::Format fmt = Gst::FORMAT_TIME;
    gint64 pos = 0;

    if (playbin->query_position(fmt, pos)
    && playbin->query_duration(fmt, duration)) {
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
  playbin->get_bus()->remove_watch(watch_id);
}

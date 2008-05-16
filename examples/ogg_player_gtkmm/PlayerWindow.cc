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

PlayerWindow::PlayerWindow(const Glib::RefPtr<Gst::Element>& source_element, const Glib::RefPtr<Gst::Pipeline>& main_pipeline)
: m_vbox(false, 5),
  m_progress_label("000:00:00.000000000 / 000:00:00.000000000"),
  m_play_button(Gtk::Stock::MEDIA_PLAY),
  m_pause_button(Gtk::Stock::MEDIA_PAUSE),
  m_stop_button(Gtk::Stock::MEDIA_STOP),
  m_rewind_button(Gtk::Stock::MEDIA_REWIND),
  m_forward_button(Gtk::Stock::MEDIA_FORWARD),
  m_open_button(Gtk::Stock::OPEN)
{
  set_title("gstreamermm Ogg Player Example");

  add(m_vbox);
  m_vbox.pack_start(m_progress_label);
  m_vbox.pack_start(m_progress_scale);
  m_vbox.pack_start(m_button_box);

  m_progress_label.set_alignment(Gtk::ALIGN_CENTER);

  m_progress_scale.set_range(0, 1);
  m_progress_scale.set_draw_value(false);
  m_progress_scale.signal_change_value().connect(
    sigc::mem_fun(*this, &PlayerWindow::on_scale_value_changed));

  m_button_box.pack_start(m_play_button);
  m_button_box.pack_start(m_pause_button);
  m_button_box.pack_start(m_stop_button);
  m_button_box.pack_start(m_rewind_button);
  m_button_box.pack_start(m_forward_button);
  m_button_box.pack_start(m_open_button);

  m_play_button.signal_clicked().connect(
    sigc::mem_fun(*this, &PlayerWindow::on_play ));
  m_pause_button.signal_clicked().connect(
    sigc::mem_fun(*this, &PlayerWindow::on_pause) );
  m_stop_button.signal_clicked().connect(
    sigc::mem_fun(*this, &PlayerWindow::on_stop) );
  m_rewind_button.signal_clicked().connect(
    sigc::mem_fun(*this, &PlayerWindow::on_rewind) );
  m_forward_button.signal_clicked().connect(
    sigc::mem_fun(*this,  &PlayerWindow::on_forward) );
  m_open_button.signal_clicked().connect(
    sigc::mem_fun(*this, &PlayerWindow::on_open) );

  // get the bus from the pipeline
  Glib::RefPtr<Gst::Bus> bus = main_pipeline->get_bus();

  // Add a bus watch to receive messages from pipeline's bus
  m_watch_id = bus->add_watch(
    sigc::mem_fun( *this, &PlayerWindow::on_bus_message) );

  m_progress_scale.set_sensitive(false);
  m_play_button.set_sensitive(false);
  m_pause_button.set_sensitive(false);
  m_stop_button.set_sensitive(false);
  m_rewind_button.set_sensitive(false);
  m_forward_button.set_sensitive(false);

  m_source_element = source_element;
  m_main_pipeline = main_pipeline;

  show_all_children();
  m_pause_button.hide();
}

// This function is used to receive asynchronous messages from main_pipeline's bus
bool PlayerWindow::on_bus_message(const Glib::RefPtr<Gst::Bus>& /* bus */, const Glib::RefPtr<Gst::Message>& message)
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
  m_progress_scale.set_sensitive(true);
  m_play_button.set_sensitive(false);
  m_pause_button.set_sensitive(true);
  m_stop_button.set_sensitive(true);
  m_rewind_button.set_sensitive(true);
  m_forward_button.set_sensitive(true);
  m_open_button.set_sensitive(false);

  m_play_button.hide();
  m_pause_button.show();

  // Call update_stream_progress function at a 200ms
  // interval to regularly update the position of the stream
  m_progress_connection = Glib::signal_timeout().connect(
    sigc::mem_fun(*this, &PlayerWindow::update_stream_progress), 200);

  // set Gstmm pipeline to play mode
  m_main_pipeline->set_state(Gst::STATE_PLAYING);
}
 
void PlayerWindow::on_pause()
{
  m_play_button.set_sensitive(true);
  m_pause_button.set_sensitive(false);

  m_pause_button.hide();
  m_play_button.show();

  // disconnect progress callback
  m_progress_connection.disconnect();
  
  // set Gstmm pipeline to pause mode
  m_main_pipeline->set_state(Gst::STATE_PAUSED);
}
 
void PlayerWindow::on_stop()
{
  m_progress_scale.set_sensitive(false);
  m_play_button.set_sensitive(true);
  m_pause_button.set_sensitive(false);
  m_stop_button.set_sensitive(false);
  m_rewind_button.set_sensitive(false);
  m_forward_button.set_sensitive(false);
  m_open_button.set_sensitive(true);

  m_pause_button.hide();
  m_play_button.show();

  // disconnect progress callback
  m_progress_connection.disconnect();

  // set Gstmm pipeline to inactive mode
  m_main_pipeline->set_state(Gst::STATE_NULL);
  display_label_progress(0, m_duration);
  m_progress_scale.set_value(0);
}

bool PlayerWindow::on_scale_value_changed(Gtk::ScrollType /* type_not_used */, double value)
{
  gint64 newPos = gint64(value * m_duration);

  if(m_main_pipeline->seek(Gst::FORMAT_TIME, Gst::SEEK_FLAG_FLUSH, newPos))
  {
    display_label_progress(newPos, m_duration);
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

  gint64 pos = 0;
  Gst::Format fmt = Gst::FORMAT_TIME;

  if(m_main_pipeline->query_position(fmt, pos))
  {
    gint64 newPos = (pos > skipAmount) ? (pos - skipAmount) : 0;

    if(m_main_pipeline->seek(Gst::FORMAT_TIME, Gst::SEEK_FLAG_FLUSH, newPos))
    {
      display_label_progress(newPos, m_duration);
      m_progress_scale.set_value(double(newPos) / m_duration);
    }
    else
      std::cerr << "Could not seek!" << std::endl;
  }
}

void PlayerWindow::on_forward()
{
  static const gint64 skipAmount = GST_SECOND * 3;

  gint64 pos = 0;
  Gst::Format fmt = Gst::FORMAT_TIME;

  Glib::RefPtr<Gst::Query> query = Gst::QueryPosition::create(fmt);

  if(m_main_pipeline->query(query))
  {
    Glib::RefPtr<Gst::QueryPosition> posQuery =
      Glib::RefPtr<Gst::QueryPosition>::cast_dynamic(query);

    posQuery->parse(fmt, pos);

    gint64 newPos = ((pos + skipAmount) < m_duration) ? (pos + skipAmount) :
      m_duration;

    Glib::RefPtr<Gst::Event> event = Gst::EventSeek::create(1.0, fmt,
      Gst::SEEK_FLAG_FLUSH, Gst::SEEK_TYPE_SET, newPos,
      Gst::SEEK_TYPE_NONE, -1);

    Glib::RefPtr<Gst::EventSeek> seekEvent =
      Glib::RefPtr<Gst::EventSeek>::cast_dynamic(event);

    if(m_main_pipeline->send_event(seekEvent))
    {
      m_progress_scale.set_value(double(newPos) / m_duration);
      display_label_progress(newPos, m_duration);
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
  
  const int response = chooser.run();
  if(response == Gtk::RESPONSE_OK)
  {
    workingDir = chooser.get_current_folder();

    // Set filename property on the file source. Also add a message handler:
    m_source_element->set_property("location", chooser.get_filename());
    set_title(Glib::filename_display_basename(chooser.get_filename()));

    m_play_button.set_sensitive(true);
    display_label_progress(0, 0);
  }
}

bool PlayerWindow::update_stream_progress()
{
  Gst::Format fmt = Gst::FORMAT_TIME;
  gint64 pos = 0;

  if(m_main_pipeline->query_position(fmt, pos)
    && m_main_pipeline->query_duration(fmt, m_duration))
  {
    m_progress_scale.set_value(double(pos) / m_duration);
    display_label_progress(pos, m_duration);
  }

   return true;
}

void PlayerWindow::display_label_progress(gint64 pos, gint64 len)
{
  std::ostringstream locationStream(std::ostringstream::out);
  std::ostringstream durationStream(std::ostringstream::out);

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

  m_progress_label.set_text(locationStream.str() + " / " + durationStream.str());
}

PlayerWindow::~PlayerWindow()
{
  m_main_pipeline->get_bus()->remove_watch(m_watch_id);
}


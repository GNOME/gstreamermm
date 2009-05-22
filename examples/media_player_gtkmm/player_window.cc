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
#include <gstreamermm/xoverlay.h>
#include <iostream>
#include <sstream>
#include <iomanip>
#include "player_window.h"

PlayerWindow::PlayerWindow(const Glib::RefPtr<Gst::PlayBin2>& playbin,
  const Glib::RefPtr<Gst::XImageSink>& video_sink)
: m_vbox(false, 6),
  m_progress_label("000:00:00.000000000 / 000:00:00.000000000"),
  m_play_button(Gtk::Stock::MEDIA_PLAY),
  m_pause_button(Gtk::Stock::MEDIA_PAUSE),
  m_stop_button(Gtk::Stock::MEDIA_STOP),
  m_rewind_button(Gtk::Stock::MEDIA_REWIND),
  m_forward_button(Gtk::Stock::MEDIA_FORWARD),
  m_open_button(Gtk::Stock::OPEN)
{
  set_title("gstreamermm Media Player Example");

  add(m_vbox);
  m_vbox.pack_start(m_video_area, Gtk::PACK_EXPAND_WIDGET);
  m_vbox.pack_start(m_progress_label, Gtk::PACK_SHRINK);
  m_vbox.pack_start(m_progress_scale, Gtk::PACK_SHRINK);
  m_vbox.pack_start(m_button_box, Gtk::PACK_SHRINK);

  m_progress_label.set_alignment(Gtk::ALIGN_CENTER);

  m_progress_scale.set_range(0, 1);
  m_progress_scale.set_draw_value(false);
  m_progress_scale.signal_change_value().connect(
    sigc::mem_fun(*this, &PlayerWindow::on_scale_value_changed) );

  m_button_box.pack_start(m_play_button);
  m_button_box.pack_start(m_pause_button);
  m_button_box.pack_start(m_stop_button);
  m_button_box.pack_start(m_rewind_button);
  m_button_box.pack_start(m_forward_button);
  m_button_box.pack_start(m_open_button);

  m_play_button.signal_clicked().connect(sigc::mem_fun(*this,
                      &PlayerWindow::on_button_play));
  m_pause_button.signal_clicked().connect(sigc::mem_fun(*this,
                      &PlayerWindow::on_button_pause));
  m_stop_button.signal_clicked().connect(sigc::mem_fun(*this,
                      &PlayerWindow::on_button_stop));
  m_rewind_button.signal_clicked().connect(sigc::mem_fun(*this,
                      &PlayerWindow::on_button_rewind));
  m_forward_button.signal_clicked().connect(sigc::mem_fun(*this,
                      &PlayerWindow::on_button_forward));
  m_open_button.signal_clicked().connect(sigc::mem_fun(*this,
                      &PlayerWindow::on_button_open));

  // Get the bus from the pipeline:
  Glib::RefPtr<Gst::Bus> bus = playbin->get_bus();

  // Enable synchronous message emission to set up video (if any) at the
  // exact appropriate time
  bus->enable_sync_message_emission();

  // Connect to bus's synchronous message signal (this is done so that
  // m_video_area can be set up for drawing at the exact appropriate time):
  bus->signal_sync_message().connect(
    sigc::mem_fun(*this, &PlayerWindow::on_bus_message_sync));

  // Add a bus watch to receive messages from the pipeline's bus:
  m_watch_id = bus->add_watch(
    sigc::mem_fun(*this, &PlayerWindow::on_bus_message) );

  m_progress_scale.set_sensitive(false);
  m_play_button.set_sensitive(false);
  m_pause_button.set_sensitive(false);
  m_stop_button.set_sensitive(false);
  m_rewind_button.set_sensitive(false);
  m_forward_button.set_sensitive(false);

  m_play_bin = playbin;
  m_video_sink = video_sink;

  show_all_children();
  m_pause_button.hide();
}

// This function is used to receive asynchronous messages from mainPipeline's bus
void PlayerWindow::on_bus_message_sync(
    const Glib::RefPtr<Gst::Message>& message)
{
  // ignore anything but 'prepare-xwindow-id' element messages
  if(message->get_message_type() != Gst::MESSAGE_ELEMENT)
    return;

  if(!message->get_structure().has_name("prepare-xwindow-id"))
     return;

  Glib::RefPtr<Gst::Element> element =
      Glib::RefPtr<Gst::Element>::cast_dynamic(message->get_source());

  Glib::RefPtr< Gst::ElementInterfaced<Gst::XOverlay> > xoverlay =
      Gst::Interface::cast <Gst::XOverlay>(element);

  if(xoverlay)
  {
    const gulong xWindowId = GDK_WINDOW_XID(m_video_area.get_window()->gobj());
    xoverlay->set_xwindow_id(xWindowId);
  }
}

// This function is used to receive asynchronous messages from play_bin's bus
bool PlayerWindow::on_bus_message(const Glib::RefPtr<Gst::Bus>& /* bus */,
          const Glib::RefPtr<Gst::Message>& message)
{
  switch(message->get_message_type())
  {
    case Gst::MESSAGE_EOS:
    {
      on_button_stop();
      break;
    }
    case Gst::MESSAGE_ERROR:
    {
      Glib::RefPtr<Gst::MessageError> msgError = Glib::RefPtr<Gst::MessageError>::cast_dynamic(message);
      if(msgError)
      {
        Glib::Error err;
        err = msgError->parse();
        std::cerr << "Error: " << err.what() << std::endl;
      }
      else
        std::cerr << "Error." << std::endl;

      on_button_stop();
      break;
    }
    default:
    {
      //std::cout << "debug: on_bus_message: unhandled message=" << G_OBJECT_TYPE_NAME(message->gobj()) << std::endl;
    }
  }

  return true;
}

bool PlayerWindow::on_video_pad_got_buffer(const Glib::RefPtr<Gst::Pad>& pad,
    const Glib::RefPtr<Gst::MiniObject>& data)
{
  Glib::RefPtr<Gst::Buffer> buffer = Glib::RefPtr<Gst::Buffer>::cast_dynamic(data);

  if(buffer) {
    int width_value;
    int height_value;

    Glib::RefPtr<Gst::Caps> caps = buffer->get_caps();

    const Gst::Structure structure = caps->get_structure(0);
    if(structure)
    {
      structure.get_field("width", width_value);
      structure.get_field("height", height_value);
    }

    m_video_area.set_size_request(width_value, height_value);

    // Resize to minimum when first playing by making size 
    // smallest then resizing according to video new size:
    resize(1, 1);
    check_resize();
  }

  pad->remove_buffer_probe(m_pad_probe_id);
  m_pad_probe_id = 0; // Clear probe id to indicate that it has been removed

  return true; // Keep buffer in pipeline (do not throw away)
}

void PlayerWindow::on_button_play()
{
  //Change the UI appropriately:
  m_progress_scale.set_sensitive();
  m_play_button.set_sensitive(false);
  m_pause_button.set_sensitive();
  m_stop_button.set_sensitive();
  m_rewind_button.set_sensitive();
  m_forward_button.set_sensitive();
  m_open_button.set_sensitive(false);

  m_play_button.hide();
  m_pause_button.show();

  // Call on_timeout function at a 200ms
  // interval to regularly update the position of the stream
  m_timeout_connection = Glib::signal_timeout().connect(
    sigc::mem_fun(*this, &PlayerWindow::on_timeout), 200);

  // set the pipeline to play mode:
  m_play_bin->set_state(Gst::STATE_PLAYING);
}
 
void PlayerWindow::on_button_pause()
{
  m_play_button.set_sensitive();
  m_pause_button.set_sensitive(false);

  m_pause_button.hide();
  m_play_button.show();

  // Disconnect the progress callback:
  m_timeout_connection.disconnect();
  
  // Set the pipeline to pause mode:
  m_play_bin->set_state(Gst::STATE_PAUSED);
}
 
void PlayerWindow::on_button_stop()
{
  //Change the UI appropriately:
  m_progress_scale.set_sensitive(false);
  m_play_button.set_sensitive();
  m_pause_button.set_sensitive(false);
  m_stop_button.set_sensitive(false);
  m_rewind_button.set_sensitive(false);
  m_forward_button.set_sensitive(false);
  m_open_button.set_sensitive();
  m_pause_button.hide();
  m_play_button.show();

  // Disconnect the progress signal handler:
  m_timeout_connection.disconnect();

  // Set the pipeline to inactive mode:
  m_play_bin->set_state(Gst::STATE_NULL);

  // Reset the display:
  display_label_progress(0, m_duration);
  m_progress_scale.set_value(0);

  // Remove video sink pad buffer probe if after playing, probe id is
  // not zero (means probe was not removed because media had no video and
  // video_pad_got_buffer method never got a chance to remove probe)
  if(m_pad_probe_id != 0)
  {
    m_video_sink->get_static_pad("sink")->remove_buffer_probe(m_pad_probe_id);
    m_pad_probe_id  = 0;
  }
}

bool PlayerWindow::on_scale_value_changed(Gtk::ScrollType /* type_not_used */, double value)
{
  const gint64 newPos = gint64(value * m_duration);

  if(m_play_bin->seek(Gst::FORMAT_TIME, Gst::SEEK_FLAG_FLUSH, newPos))
  {
    display_label_progress(newPos, m_duration);
    return true;
  }
  else
  {
    std::cerr << "Could not seek." << std::endl;
    return false;
  }
}

void PlayerWindow::on_button_rewind()
{
  static const gint64 skipAmount = Gst::SECOND * 2;

  gint64 pos = 0;
  Gst::Format fmt = Gst::FORMAT_TIME;

  if(m_play_bin->query_position(fmt, pos))
  {
    gint64 newPos = (pos > skipAmount) ? (pos - skipAmount) : 0;

    if(m_play_bin->seek(Gst::FORMAT_TIME, Gst::SEEK_FLAG_FLUSH, newPos)) {
      m_progress_scale.set_value(double(newPos) / m_duration);
      display_label_progress(newPos, m_duration);
    }
    else
      std::cerr << "Could not seek." << std::endl;
  }
}

void PlayerWindow::on_button_forward()
{
  static const gint64 skipAmount = Gst::SECOND * 3;

  Gst::Format fmt = Gst::FORMAT_TIME;

  Glib::RefPtr<Gst::Query> query = Gst::QueryPosition::create(fmt);

  if(m_play_bin->query(query))
  {
    Glib::RefPtr<Gst::QueryPosition> posQuery =
      Glib::RefPtr<Gst::QueryPosition>::cast_dynamic(query);

    gint64 pos = posQuery->parse();

    gint64 newPos = ((pos + skipAmount) < m_duration) ? (pos + skipAmount) :
      m_duration;

    Glib::RefPtr<Gst::Event> event = Gst::EventSeek::create(1.0, fmt,
        Gst::SEEK_FLAG_FLUSH, Gst::SEEK_TYPE_SET, newPos,
        Gst::SEEK_TYPE_NONE, -1);

    Glib::RefPtr<Gst::EventSeek> seekEvent =
      Glib::RefPtr<Gst::EventSeek>::cast_dynamic(event);

    if(m_play_bin->send_event(seekEvent))
    {
      m_progress_scale.set_value(double(newPos) / m_duration);
      display_label_progress(newPos, m_duration);
    }
    else
      std::cerr << "Could not seek." << std::endl;
  }
}

void PlayerWindow::on_button_open()
{
  static Glib::ustring working_dir = Glib::get_home_dir();
  
  Gtk::FileChooserDialog chooser(*this,
    "Select a media file", Gtk::FILE_CHOOSER_ACTION_OPEN);
  chooser.add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
  chooser.add_button(Gtk::Stock::OK, Gtk::RESPONSE_OK);
  
  chooser.set_current_folder(working_dir);
  
  const int response = chooser.run();
  if(response == Gtk::RESPONSE_OK)
  {
    working_dir = chooser.get_current_folder();

    // Set uri property on the playbin.
#ifdef GLIBMM_PROPERTIES_ENABLED
    m_play_bin->property_uri() = chooser.get_uri();
#else
    m_play_bin->set_property("property_uri", chooser.get_uri());
#endif

    // Resize m_video_area and window to minimum when opening a file
    m_video_area.set_size_request(0, 0);
    resize(1, 1);

    // Add buffer probe to video sink pad when file is opened which will
    // be removed after first buffer is received in on_video_pad_got_buffer
    // method (if there's video).  When first buffer arrives, video
    // size can be extracted.  If there's no video, probe will be
    // removed when media stops in on_button_stop method
    m_pad_probe_id = m_video_sink->get_static_pad("sink")->add_buffer_probe(
      sigc::mem_fun(*this, &PlayerWindow::on_video_pad_got_buffer));

    set_title( Glib::filename_display_basename(chooser.get_filename()) );

    m_play_button.set_sensitive();
    display_label_progress(0, 0);
  }
}

bool PlayerWindow::on_timeout()
{
  Gst::Format fmt = Gst::FORMAT_TIME;
  gint64 pos = 0;

  if(m_play_bin->query_position(fmt, pos)
    && m_play_bin->query_duration(fmt, m_duration))
  {
    m_progress_scale.set_value(double(pos) / m_duration);
    display_label_progress(pos, m_duration);
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

  m_progress_label.set_text(locationStream.str() + " / " + durationStream.str());
}

PlayerWindow::~PlayerWindow()
{
  m_play_bin->get_bus()->remove_watch(m_watch_id);
}

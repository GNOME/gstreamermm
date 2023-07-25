/* gstreamermm - a C++ wrapper for gstreamer
 *
 * Copyright 2015 The gstreamermm Development Team
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

#include "player_window.h"

#include <gstreamermm/xvimagesink.h>

#if defined (GDK_WINDOWING_X11)
#include <gdk/gdkx.h>
#elif defined (GDK_WINDOWING_WIN32)
#include <gdk/gdkwin32.h>
#endif

#include <iostream>
#include <iomanip>

#ifdef GSTREAMERMM_DISABLE_DEPRECATED

static const Glib::SignalProxyInfo PlayBin_signal_video_changed_info =
{
  "video-changed",
  (GCallback) &Glib::SignalProxyNormal::slot0_void_callback,
  (GCallback) &Glib::SignalProxyNormal::slot0_void_callback
};

#endif


PlayerWindow::PlayerWindow(const Glib::RefPtr<PlayBinT>& playbin)
: m_vbox(false, 6),
  m_progress_label("000:00:00.000000000 / 000:00:00.000000000"),
  m_play_button("Play"),
  m_pause_button("Pause"),
  m_stop_button("Stop"),
  m_rewind_button("Rewind"),
  m_forward_button("Forward"),
  m_open_button("Open")
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

  m_video_area.signal_realize().connect(sigc::mem_fun(*this,
                      &PlayerWindow::on_video_area_realize));

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

  m_playbin = playbin;

#ifndef GSTREAMERMM_DISABLE_DEPRECATED
  m_playbin->property_video_sink() = Gst::XvImageSink::create();
  m_playbin->signal_video_changed().connect(
    sigc::mem_fun(*this, &PlayerWindow::on_video_changed) );
#else
  m_playbin->set_property("video-sink", Gst::ElementFactory::create_element("xvimagesink"));
  Glib::SignalProxy< void >(m_playbin.operator->(), &PlayBin_signal_video_changed_info).connect(
     sigc::mem_fun(*this, &PlayerWindow::on_video_changed) );
#endif
  
  show_all_children();
  m_pause_button.hide();
}


void PlayerWindow::on_video_area_realize()
{
  // When the video area (the drawing area) is realized, Get its X Window
  // ID and save it for when the Gst::VideoOverlay is ready to accept an ID in
  // which to draw the video.
#ifdef GDK_WINDOWING_X11
  window_handler = GDK_WINDOW_XID (m_video_area.get_window()->gobj());
#endif
#ifdef GDK_WINDOWING_WIN32
  window_handler = (guintptr) GDK_WINDOW_HWND (m_video_area.get_window()->gobj());
#endif
}

static Glib::RefPtr<Gst::VideoOverlay> find_overlay(Glib::RefPtr<Gst::Element> element)
{
  auto overlay = Glib::RefPtr<Gst::VideoOverlay>::cast_dynamic(element);

  if (overlay)
    return overlay;

  auto bin = Glib::RefPtr<Gst::Bin>::cast_dynamic(element);

  if (!bin)
    return overlay;

  for (auto e : bin->get_children())
  {
    overlay = find_overlay(e);
    if (overlay)
      break;
  }

  return overlay;
}

// This function is used to receive asynchronous messages from mainPipeline's
// bus, specifically to prepare the Gst::VideoOverlay to draw inside the window
// in which we want it to draw to.
void PlayerWindow::on_bus_message_sync(const Glib::RefPtr<Gst::Message>& message)
{
  if (!gst_is_video_overlay_prepare_window_handle_message (message->gobj()))
   return;

  if (window_handler != 0)
  {
    Glib::RefPtr< Gst::VideoOverlay > videooverlay =
        find_overlay(Glib::RefPtr<Gst::Element>::cast_dynamic(message->get_source()));

    if(videooverlay)
    {
      videooverlay->set_window_handle(window_handler);
    }
  }
  else
  {
    std::cerr << "Should have obtained video_window_handle by now!";
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
      Glib::RefPtr<Gst::MessageError> msg_error = Glib::RefPtr<Gst::MessageError>::cast_static(message);
      if(msg_error)
      {
        Glib::Error err = msg_error->parse_error();
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

void PlayerWindow::on_video_changed()
{
#ifndef GSTREAMERMM_DISABLE_DEPRECATED
  Glib::RefPtr<Gst::Pad> pad = m_playbin->get_video_pad(0);
#else
  GstPad* result;
  g_signal_emit_by_name(m_playbin->gobj(), "get-video-pad", 0, &result, static_cast<void*>(0));
  Glib::RefPtr<Gst::Pad> pad = Glib::wrap(result);
#endif
  
  if(pad)
  {
    // Add a buffer probe to the video sink pad which will be removed after
    // the first buffer is received in the on_video_pad_got_buffer method.
    // When the first buffer arrives, the video size can be extracted.
    m_pad_probe_id = pad->add_probe(Gst::PAD_PROBE_TYPE_BUFFER,
      sigc::mem_fun(*this, &PlayerWindow::on_video_pad_got_buffer));
  }
}

Gst::PadProbeReturn PlayerWindow::on_video_pad_got_buffer(const Glib::RefPtr<Gst::Pad>& pad, const Gst::PadProbeInfo& /* data */)
{
  int width_value;
  int height_value;

  Glib::RefPtr<Gst::Caps> caps = pad->get_current_caps();
  caps = caps->create_writable();

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

  pad->remove_probe(m_pad_probe_id);
  m_pad_probe_id = 0; // Clear probe id to indicate that it has been removed

  return Gst::PAD_PROBE_OK;
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
  m_playbin->set_state(Gst::STATE_PLAYING);
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
  m_playbin->set_state(Gst::STATE_PAUSED);
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
  m_playbin->set_state(Gst::STATE_NULL);

  // Reset the display:
  display_label_progress(0, m_duration);
  m_progress_scale.set_value(0);
}

bool PlayerWindow::on_scale_value_changed(Gtk::ScrollType /* type_not_used */, double value)
{
  const gint64 new_pos = gint64(value * m_duration);

  if(m_playbin->seek(Gst::FORMAT_TIME, Gst::SEEK_FLAG_FLUSH, new_pos))
  {
    display_label_progress(new_pos, m_duration);
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
  gint64 pos = 0;
  Gst::Format fmt = Gst::FORMAT_TIME;

  if(m_playbin->query_position(fmt, pos))
  {
    gint64 new_pos = (pos > rewind_skip_amount) ? (pos - rewind_skip_amount) : 0;

    if(m_playbin->seek(Gst::FORMAT_TIME, Gst::SEEK_FLAG_FLUSH, new_pos))
    {
      m_progress_scale.set_value(double(new_pos) / m_duration);
      display_label_progress(new_pos, m_duration);
    }
    else
      std::cerr << "Could not seek." << std::endl;
  }
}

void PlayerWindow::on_button_forward()
{
  Gst::Format fmt = Gst::FORMAT_TIME;
  Glib::RefPtr<Gst::QueryPosition> query = Gst::QueryPosition::create(fmt);

  if(m_playbin->query(query))
  {
    gint64 pos = query->parse();
    gint64 new_pos = ((pos + forward_skip_amount) < m_duration) ? (pos + forward_skip_amount) :
      m_duration;

    Glib::RefPtr<Gst::Event> event = Gst::EventSeek::create(1.0, fmt,
        Gst::SEEK_FLAG_FLUSH, Gst::SEEK_TYPE_SET, new_pos,
        Gst::SEEK_TYPE_NONE, -1);

    if(Glib::RefPtr<Gst::Element>::cast_static(m_playbin)->send_event(std::move(event)))
    {
      m_progress_scale.set_value(double(new_pos) / m_duration);
      display_label_progress(new_pos, m_duration);
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
  chooser.add_button("Cancel", Gtk::RESPONSE_CANCEL);
  chooser.add_button("OK", Gtk::RESPONSE_OK);

  chooser.set_current_folder(working_dir);

  const int response = chooser.run();
  if(response == Gtk::RESPONSE_OK)
  {
    working_dir = chooser.get_current_folder();

    // Set uri property on the playbin.
    m_playbin->set_property("uri", chooser.get_uri());

    // Resize m_video_area and window to minimum when opening a file
    m_video_area.set_size_request(0, 0);
    resize(1, 1);

    set_title( Glib::filename_display_basename(chooser.get_filename()) );

    m_play_button.set_sensitive();
    display_label_progress(0, 0);
  }
}

bool PlayerWindow::on_timeout()
{
  Gst::Format fmt = Gst::FORMAT_TIME;
  gint64 pos = 0;

  if(m_playbin->query_position(fmt, pos)
    && m_playbin->query_duration(fmt, m_duration))
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
  m_playbin->get_bus()->remove_watch(m_watch_id);
  m_playbin->set_state(Gst::STATE_NULL);
}

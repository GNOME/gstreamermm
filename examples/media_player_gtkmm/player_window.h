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

#ifndef PLAYER_WINDOW_H_
#define PLAYER_WINDOW_H_

#include <gtkmm.h>
#include <gstreamermm.h>

class PlayerWindow : public Gtk::Window
{
public:
#ifndef GSTREAMERMM_DISABLE_DEPRECATED
  using PlayBinT = Gst::PlayBin;
#else
  using PlayBinT = Gst::Element;
#endif
  PlayerWindow(const Glib::RefPtr<PlayBinT>& playbin);
  virtual ~PlayerWindow();

protected:

  //Signal handlers:
  void on_video_area_realize();
  void on_bus_message_sync(const Glib::RefPtr<Gst::Message>& message);
  bool on_bus_message(const Glib::RefPtr<Gst::Bus>& bus, const Glib::RefPtr<Gst::Message>& message);
  void on_video_changed();
  Gst::PadProbeReturn on_video_pad_got_buffer(const Glib::RefPtr<Gst::Pad>& pad, const Gst::PadProbeInfo& data);

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

#ifndef GSTREAMERMM_DISABLE_DEPRECATED
  Glib::RefPtr<Gst::PlayBin> m_playbin;
#else
  Glib::RefPtr<Gst::Element> m_playbin;
#endif
  
  sigc::connection m_timeout_connection;
  guint m_watch_id;
  gint64 m_duration;
  guintptr window_handler;
  gulong m_pad_probe_id;

  const gint64 rewind_skip_amount = Gst::SECOND * 2;
  const gint64 forward_skip_amount = Gst::SECOND * 3;
};

#endif /* PLAYER_WINDOW_H_ */

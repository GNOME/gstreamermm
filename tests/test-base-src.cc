/* gstreamermm - a C++ wrapper for gstreamer
 *
 * Copyright 2011 The gstreamermm Development Team
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free
 * Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#include <gstreamermm.h>
#include <iostream>

void print_info(const Glib::RefPtr<Gst::Mixer>& mixer)
{
  typedef std::vector< Glib::RefPtr<Gst::MixerTrack> > tracks_type;

  tracks_type tracks = mixer->list_tracks();

  for(tracks_type::iterator iter = tracks.begin(); iter != tracks.end();
    ++iter)
  {
    Glib::RefPtr<const Gst::MixerTrack> track = *iter;

    Glib::ustring label = track->get_label();

    bool const is_microphone = !label.compare("Mic") ||
      !label.compare(0, 4, "Mic ") || !label.compare(0, 10, "Microphone");

    bool const has_channels = track->get_num_channels() > 0;

    std::cout << label;

    if (is_microphone)
      std::cout << " [MICROPHONE]";

    if (has_channels)
    {
      std::vector<int> volumes = mixer->get_volume(track);

      for (std::vector<int>::iterator volume_iter = volumes.begin();
        volume_iter != volumes.end(); ++volume_iter)
      {
        std::cout << ' ' << *volume_iter;
      }
    }

    guint flags = track->property_flags();

    if ((flags & Gst::MIXER_TRACK_INPUT))
      std::cout << " [input]";

    if ((flags & Gst::MIXER_TRACK_OUTPUT))
      std::cout << " [output]";

    if ((flags & Gst::MIXER_TRACK_MUTE))
      std::cout << " [muted]";

    if ((flags & Gst::MIXER_TRACK_RECORD))
      std::cout << " [CAPTURE]";

    std::cout << std::endl;
  }
}

int main(int argc, char** argv)
{
  Gst::init(argc, argv);

  Glib::RefPtr<Gst::AlsaSrc> alsasrc = Gst::AlsaSrc::create("alsasrc");

  if(!alsasrc)
  {
    std::cout << "Could not create the alsarc element." << std::endl;
    return 1;
  }

  // Must set the state of the alsasrc to ready before using it.
  alsasrc->set_state(Gst::STATE_READY);

  print_info(alsasrc);

  // Also go back to the NULL state before it is freed.
  alsasrc->set_state(Gst::STATE_NULL);

  return 0;
}

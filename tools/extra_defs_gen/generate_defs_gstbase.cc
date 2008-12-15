/* generate_defs_gst.cc
 *
 * Copyright (C) 2001 The Free Software Foundation
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public
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

#include "glibmm_generate_extra_defs/generate_extra_defs.h"
#include "get_plugin_defs.h"

#include <gst/gst.h>
#include <gst/audio/gstaudioclock.h>
#include <gst/audio/gstaudiofilter.h>
#include <gst/audio/gstbaseaudiosink.h>
#include <gst/audio/gstbaseaudiosrc.h>
#include <gst/audio/gstaudiosink.h>
#include <gst/audio/gstaudiosrc.h>
#include <gst/audio/gstringbuffer.h>
#include <gst/interfaces/colorbalance.h>
#include <gst/interfaces/colorbalancechannel.h>
#include <gst/interfaces/xoverlay.h>

int main (int argc, char *argv[])
{
  gst_init (&argc, &argv);

  // gst-plugins-base (GStreamer base) types:
  std::cout << get_defs(GST_TYPE_AUDIO_CLOCK)
            << get_defs(GST_TYPE_AUDIO_FILTER)
            << get_defs(GST_TYPE_BASE_AUDIO_SINK)
            << get_defs(GST_TYPE_BASE_AUDIO_SRC)
            << get_defs(GST_TYPE_AUDIO_SINK)
            << get_defs(GST_TYPE_AUDIO_SRC)
            << get_defs(GST_TYPE_RING_BUFFER)

  // gst-plugins-base (GStreamer base) interfaces:
            << get_defs(GST_TYPE_COLOR_BALANCE)
            << get_defs(GST_TYPE_COLOR_BALANCE_CHANNEL)
            << get_defs(GST_TYPE_X_OVERLAY)

   // Base class of playbin plugin:
            << get_defs(g_type_from_name("GstPlayBaseBin"))

  // gst-plugins-base (GStreamer base) plugin types:
            << get_plugin_defs("adder")
            << get_plugin_defs("alsamixer")
            << get_plugin_defs("alsasink")
            << get_plugin_defs("alsasrc")
            << get_plugin_defs("audioconvert")
            << get_plugin_defs("audioresample")
            << get_plugin_defs("audiotestsrc")
            << get_plugin_defs("cdparanoiasrc")
            << get_plugin_defs("clockoverlay")
            << get_plugin_defs("decodebin")
            << get_plugin_defs("decodebin2")
            << get_plugin_defs("ffmpegcolorspace")
            << get_plugin_defs("gdpdepay")
            << get_plugin_defs("gdppay")
            << get_plugin_defs("giosink")
            << get_plugin_defs("giosrc")
            << get_plugin_defs("giostreamsink")
            << get_plugin_defs("giostreamsrc")
            << get_plugin_defs("gnomevfssink")
            << get_plugin_defs("gnomevfssrc")
            << get_plugin_defs("multifdsink")
            << get_plugin_defs("oggdemux")
            << get_plugin_defs("oggmux")
            << get_plugin_defs("playbin")
            << get_plugin_defs("playbin2")
            << get_plugin_defs("tcpserversink")
            << get_plugin_defs("textoverlay")
            << get_plugin_defs("textrender")
            << get_plugin_defs("theoradec")
            << get_plugin_defs("theoraenc")
            << get_plugin_defs("theoraparse")
            << get_plugin_defs("timeoverlay")
            << get_plugin_defs("uridecodebin")
            << get_plugin_defs("videorate")
            << get_plugin_defs("videoscale")
            << get_plugin_defs("videotestsrc")
            << get_plugin_defs("volume")
            << get_plugin_defs("vorbisdec")
            << get_plugin_defs("vorbisenc")
            << get_plugin_defs("vorbisparse")
            << get_plugin_defs("vorbistag")
            << get_plugin_defs("ximagesink")
            << get_plugin_defs("xvimagesink")
            ;

  return 0;
}

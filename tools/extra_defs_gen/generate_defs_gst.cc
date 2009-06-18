/* generate_defs_gst.cc
 *
 * Copyright 2008 The gstreamermm Development Team
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with this library; if not, write to the Free
 * Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#include <glibmm_generate_extra_defs/generate_extra_defs.h>
#include "get_plugin_defs.h"

// Core includes
#include <gst/gst.h>

// Core library includes
#include <gst/base/gstbasesrc.h>
#include <gst/base/gstbasesink.h>
#include <gst/base/gstbasetransform.h>
#include <gst/base/gstpushsrc.h>
#include <gst/base/gstadapter.h>
#include <gst/base/gstcollectpads.h>
#include <gst/base/gstdataqueue.h>
#include <gst/controller/gstcontroller.h>
#include <gst/controller/gstcontrolsource.h>
#include <gst/controller/gstinterpolationcontrolsource.h>
#include <gst/controller/gstlfocontrolsource.h>
#include <gst/net/gstnet.h>

// Base library includes
#include <gst/audio/gstaudioclock.h>
#include <gst/audio/gstaudiofilter.h>
#include <gst/audio/gstbaseaudiosink.h>
#include <gst/audio/gstbaseaudiosrc.h>
#include <gst/audio/gstaudiosink.h>
#include <gst/audio/gstaudiosrc.h>
#include <gst/audio/gstringbuffer.h>
#include <gst/cdda/gstcddabasesrc.h>
#include <gst/netbuffer/gstnetbuffer.h>
#include <gst/rtp/gstbasertpaudiopayload.h>
#include <gst/rtp/gstbasertpdepayload.h>
#include <gst/rtp/gstbasertppayload.h>
#include <gst/tag/gsttagdemux.h>
#include <gst/video/gstvideosink.h>
#include <gst/video/gstvideofilter.h>

// Base interface includes
#include <gst/interfaces/colorbalance.h>
#include <gst/interfaces/colorbalancechannel.h>
#include <gst/interfaces/mixer.h>
#include <gst/interfaces/navigation.h>
#include <gst/interfaces/propertyprobe.h>
#include <gst/interfaces/tuner.h>
#include <gst/interfaces/videoorientation.h>
#include <gst/interfaces/xoverlay.h>

bool gst_type_is_a_pointer(GType gtype)
{
  return (gtype_is_a_pointer(gtype) || g_type_is_a(gtype,
GST_TYPE_MINI_OBJECT));
}

int main (int argc, char *argv[])
{
  gst_init (&argc, &argv);

  // GStreamer core types:
  std::cout << get_defs(GST_TYPE_BUS, gst_type_is_a_pointer)
            << get_defs(GST_TYPE_BIN, gst_type_is_a_pointer)
            << get_defs(GST_TYPE_BUFFER, gst_type_is_a_pointer)
            << get_defs(GST_TYPE_CAPS, gst_type_is_a_pointer)
            << get_defs(GST_TYPE_CHILD_PROXY, gst_type_is_a_pointer)
            << get_defs(GST_TYPE_CLOCK, gst_type_is_a_pointer)
            << get_defs(GST_TYPE_ELEMENT, gst_type_is_a_pointer)
            << get_defs(GST_TYPE_ELEMENT_FACTORY, gst_type_is_a_pointer)
            << get_defs(GST_TYPE_EVENT, gst_type_is_a_pointer)
            << get_defs(GST_TYPE_FORMAT, gst_type_is_a_pointer)
            << get_defs(GST_TYPE_G_ERROR, gst_type_is_a_pointer)
            << get_defs(GST_TYPE_GHOST_PAD, gst_type_is_a_pointer)
            << get_defs(GST_TYPE_IMPLEMENTS_INTERFACE, gst_type_is_a_pointer)
            << get_defs(GST_TYPE_INDEX, gst_type_is_a_pointer)
            << get_defs(GST_TYPE_INDEX_FACTORY, gst_type_is_a_pointer)
            << get_defs(GST_TYPE_MESSAGE, gst_type_is_a_pointer)
            << get_defs(GST_TYPE_MINI_OBJECT, gst_type_is_a_pointer)
            << get_defs(GST_TYPE_OBJECT, gst_type_is_a_pointer)
            << get_defs(GST_TYPE_PAD, gst_type_is_a_pointer)
            << get_defs(GST_TYPE_PAD_TEMPLATE, gst_type_is_a_pointer)
            << get_defs(GST_TYPE_PIPELINE, gst_type_is_a_pointer)
            << get_defs(GST_TYPE_PLUGIN, gst_type_is_a_pointer)
            << get_defs(GST_TYPE_PLUGIN_FEATURE, gst_type_is_a_pointer)
            << get_defs(GST_TYPE_QUERY, gst_type_is_a_pointer)
            << get_defs(GST_TYPE_REGISTRY, gst_type_is_a_pointer)
            << get_defs(GST_TYPE_SEGMENT, gst_type_is_a_pointer)
            << get_defs(GST_TYPE_STRUCTURE, gst_type_is_a_pointer)
            << get_defs(GST_TYPE_SYSTEM_CLOCK, gst_type_is_a_pointer)
            << get_defs(GST_TYPE_TAG_LIST, gst_type_is_a_pointer)
            << get_defs(GST_TYPE_TAG_SETTER, gst_type_is_a_pointer)
            << get_defs(GST_TYPE_TASK, gst_type_is_a_pointer)
            << get_defs(GST_TYPE_TYPE_FIND, gst_type_is_a_pointer)
            << get_defs(GST_TYPE_TYPE_FIND_FACTORY, gst_type_is_a_pointer)
            << get_defs(GST_TYPE_URI_HANDLER, gst_type_is_a_pointer)
            << get_defs(GST_TYPE_XML, gst_type_is_a_pointer)

  // GStreamer core library types:
            << get_defs(GST_TYPE_BASE_SRC, gst_type_is_a_pointer)
            << get_defs(GST_TYPE_BASE_SINK, gst_type_is_a_pointer)
            << get_defs(GST_TYPE_BASE_TRANSFORM, gst_type_is_a_pointer)
            << get_defs(GST_TYPE_PUSH_SRC, gst_type_is_a_pointer)
            << get_defs(GST_TYPE_ADAPTER, gst_type_is_a_pointer)
            << get_defs(GST_TYPE_COLLECT_PADS, gst_type_is_a_pointer)
            << get_defs(GST_TYPE_DATA_QUEUE, gst_type_is_a_pointer)
            << get_defs(GST_TYPE_CONTROLLER, gst_type_is_a_pointer)
            << get_defs(GST_TYPE_CONTROL_SOURCE, gst_type_is_a_pointer)
            << get_defs(GST_TYPE_INTERPOLATION_CONTROL_SOURCE, gst_type_is_a_pointer)
            << get_defs(GST_TYPE_LFO_CONTROL_SOURCE, gst_type_is_a_pointer)
            << get_defs(GST_TYPE_NET_CLIENT_CLOCK, gst_type_is_a_pointer)
            << get_defs(GST_TYPE_NET_TIME_PROVIDER, gst_type_is_a_pointer)
            << get_defs(GST_TYPE_NET_TIME_PROVIDER, gst_type_is_a_pointer)

  // GStreamer core plugin types:
            << get_plugin_defs("capsfilter", gst_type_is_a_pointer)
            << get_plugin_defs("fakesrc", gst_type_is_a_pointer)
            << get_plugin_defs("fakesink", gst_type_is_a_pointer)
            << get_plugin_defs("fdsink", gst_type_is_a_pointer)
            << get_plugin_defs("fdsrc", gst_type_is_a_pointer)
            << get_plugin_defs("filesrc", gst_type_is_a_pointer)
            << get_plugin_defs("filesink", gst_type_is_a_pointer)
            << get_plugin_defs("identity", gst_type_is_a_pointer)
            << get_plugin_defs("multiqueue", gst_type_is_a_pointer)
            << get_plugin_defs("queue", gst_type_is_a_pointer)
            << get_plugin_defs("tee", gst_type_is_a_pointer)
            << get_plugin_defs("typefind", gst_type_is_a_pointer)

  // gst-plugins-base (GStreamer base) types:
            << get_defs(GST_TYPE_AUDIO_CLOCK, gst_type_is_a_pointer)
            << get_defs(GST_TYPE_AUDIO_FILTER, gst_type_is_a_pointer)
            << get_defs(GST_TYPE_BASE_AUDIO_SINK, gst_type_is_a_pointer)
            << get_defs(GST_TYPE_BASE_AUDIO_SRC, gst_type_is_a_pointer)
            << get_defs(GST_TYPE_AUDIO_SINK, gst_type_is_a_pointer)
            << get_defs(GST_TYPE_AUDIO_SRC, gst_type_is_a_pointer)
            << get_defs(GST_TYPE_RING_BUFFER, gst_type_is_a_pointer)
            << get_defs(GST_TYPE_CDDA_BASE_SRC, gst_type_is_a_pointer)
            << get_defs(GST_TYPE_NETBUFFER, gst_type_is_a_pointer)
            << get_defs(GST_TYPE_BASE_RTP_AUDIO_PAYLOAD, gst_type_is_a_pointer)
            << get_defs(GST_TYPE_BASE_RTP_DEPAYLOAD, gst_type_is_a_pointer)
            << get_defs(GST_TYPE_BASE_RTP_PAYLOAD, gst_type_is_a_pointer)
            << get_defs(GST_TYPE_TAG_DEMUX, gst_type_is_a_pointer)
            << get_defs(GST_TYPE_VIDEO_SINK, gst_type_is_a_pointer)
            << get_defs(GST_TYPE_VIDEO_FILTER, gst_type_is_a_pointer)

  // gst-plugins-base (GStreamer base) interfaces:
            << get_defs(GST_TYPE_COLOR_BALANCE, gst_type_is_a_pointer)
            << get_defs(GST_TYPE_COLOR_BALANCE_CHANNEL, gst_type_is_a_pointer)
            << get_defs(GST_TYPE_MIXER, gst_type_is_a_pointer)
            << get_defs(GST_TYPE_MIXER_TRACK, gst_type_is_a_pointer)
            << get_defs(GST_TYPE_MIXER_OPTIONS, gst_type_is_a_pointer)
            << get_defs(GST_TYPE_NAVIGATION, gst_type_is_a_pointer)
            << get_defs(GST_TYPE_PROPERTY_PROBE, gst_type_is_a_pointer)
            << get_defs(GST_TYPE_TUNER, gst_type_is_a_pointer)
            << get_defs(GST_TYPE_TUNER_CHANNEL, gst_type_is_a_pointer)
            << get_defs(GST_TYPE_TUNER_NORM, gst_type_is_a_pointer)
            << get_defs(GST_TYPE_VIDEO_ORIENTATION, gst_type_is_a_pointer)
            << get_defs(GST_TYPE_X_OVERLAY, gst_type_is_a_pointer)

  // gst-plugins-base (GStreamer base) plugin types:
            << get_plugin_defs("adder", gst_type_is_a_pointer)
            << get_plugin_defs("alsamixer", gst_type_is_a_pointer)
            << get_plugin_defs("alsasink", gst_type_is_a_pointer)
            << get_plugin_defs("alsasrc", gst_type_is_a_pointer)
            << get_plugin_defs("appsrc", gst_type_is_a_pointer)
            << get_plugin_defs("appsink", gst_type_is_a_pointer)
            << get_plugin_defs("audioconvert", gst_type_is_a_pointer)
            << get_plugin_defs("audioresample", gst_type_is_a_pointer)
            << get_plugin_defs("audiotestsrc", gst_type_is_a_pointer)
            << get_plugin_defs("cdparanoiasrc", gst_type_is_a_pointer)
            << get_plugin_defs("clockoverlay", gst_type_is_a_pointer)
            << get_plugin_defs("decodebin", gst_type_is_a_pointer)
            << get_plugin_defs("decodebin2", gst_type_is_a_pointer)
            << get_plugin_defs("ffmpegcolorspace", gst_type_is_a_pointer)
            << get_plugin_defs("gdpdepay", gst_type_is_a_pointer)
            << get_plugin_defs("gdppay", gst_type_is_a_pointer)
            << get_plugin_defs("giosink", gst_type_is_a_pointer)
            << get_plugin_defs("giosrc", gst_type_is_a_pointer)
            << get_plugin_defs("giostreamsink", gst_type_is_a_pointer)
            << get_plugin_defs("giostreamsrc", gst_type_is_a_pointer)
            << get_plugin_defs("gnomevfssink", gst_type_is_a_pointer)
            << get_plugin_defs("gnomevfssrc", gst_type_is_a_pointer)
            << get_plugin_defs("multifdsink", gst_type_is_a_pointer)
            << get_plugin_defs("oggdemux", gst_type_is_a_pointer)
            << get_plugin_defs("oggmux", gst_type_is_a_pointer)
            << get_plugin_defs("playbin", gst_type_is_a_pointer)
            << get_plugin_defs("playbin2", gst_type_is_a_pointer)
            << get_plugin_defs("tcpclientsrc", gst_type_is_a_pointer)
            << get_plugin_defs("tcpclientsink", gst_type_is_a_pointer)
            << get_plugin_defs("tcpserversrc", gst_type_is_a_pointer)
            << get_plugin_defs("tcpserversink", gst_type_is_a_pointer)
            << get_plugin_defs("textoverlay", gst_type_is_a_pointer)
            << get_plugin_defs("textrender", gst_type_is_a_pointer)
            << get_plugin_defs("theoradec", gst_type_is_a_pointer)
            << get_plugin_defs("theoraenc", gst_type_is_a_pointer)
            << get_plugin_defs("theoraparse", gst_type_is_a_pointer)
            << get_plugin_defs("timeoverlay", gst_type_is_a_pointer)
            << get_plugin_defs("uridecodebin", gst_type_is_a_pointer)
            << get_plugin_defs("videorate", gst_type_is_a_pointer)
            << get_plugin_defs("videoscale", gst_type_is_a_pointer)
            << get_plugin_defs("videotestsrc", gst_type_is_a_pointer)
            << get_plugin_defs("volume", gst_type_is_a_pointer)
            << get_plugin_defs("vorbisdec", gst_type_is_a_pointer)
            << get_plugin_defs("vorbisenc", gst_type_is_a_pointer)
            << get_plugin_defs("vorbisparse", gst_type_is_a_pointer)
            << get_plugin_defs("vorbistag", gst_type_is_a_pointer)
            << get_plugin_defs("ximagesink", gst_type_is_a_pointer)
            << get_plugin_defs("xvimagesink", gst_type_is_a_pointer)
            ;
  return 0;
}

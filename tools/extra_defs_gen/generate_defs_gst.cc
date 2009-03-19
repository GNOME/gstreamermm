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

#include "glibmm_generate_extra_defs/generate_extra_defs.h"
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

int main (int argc, char *argv[])
{
  gst_init (&argc, &argv);

  // GStreamer core types:
  std::cout << get_defs(GST_TYPE_BUS)
            << get_defs(GST_TYPE_BIN)
            << get_defs(GST_TYPE_BUFFER)
            << get_defs(GST_TYPE_CAPS)
            << get_defs(GST_TYPE_CHILD_PROXY)
            << get_defs(GST_TYPE_CLOCK)
            << get_defs(GST_TYPE_ELEMENT)
            << get_defs(GST_TYPE_ELEMENT_FACTORY)
            << get_defs(GST_TYPE_EVENT)
            << get_defs(GST_TYPE_FORMAT)
            << get_defs(GST_TYPE_G_ERROR)
            << get_defs(GST_TYPE_GHOST_PAD)
            << get_defs(GST_TYPE_IMPLEMENTS_INTERFACE)
            << get_defs(GST_TYPE_INDEX)
            << get_defs(GST_TYPE_INDEX_FACTORY)
            << get_defs(GST_TYPE_MESSAGE)
            << get_defs(GST_TYPE_MINI_OBJECT)
            << get_defs(GST_TYPE_OBJECT)
            << get_defs(GST_TYPE_PAD)
            << get_defs(GST_TYPE_PAD_TEMPLATE)
            << get_defs(GST_TYPE_PIPELINE)
            << get_defs(GST_TYPE_PLUGIN)
            << get_defs(GST_TYPE_PLUGIN_FEATURE)
            << get_defs(GST_TYPE_QUERY)
            << get_defs(GST_TYPE_REGISTRY)
            << get_defs(GST_TYPE_SEGMENT)
            << get_defs(GST_TYPE_STRUCTURE)
            << get_defs(GST_TYPE_SYSTEM_CLOCK)
            << get_defs(GST_TYPE_TAG_LIST)
            << get_defs(GST_TYPE_TAG_SETTER)
            << get_defs(GST_TYPE_TASK)
            << get_defs(GST_TYPE_TYPE_FIND)
            << get_defs(GST_TYPE_TYPE_FIND_FACTORY)
            << get_defs(GST_TYPE_URI_HANDLER)
            << get_defs(GST_TYPE_XML)

  // GStreamer core library types:
            << get_defs(GST_TYPE_BASE_SRC)
            << get_defs(GST_TYPE_BASE_SINK)
            << get_defs(GST_TYPE_BASE_TRANSFORM)
            << get_defs(GST_TYPE_PUSH_SRC)
            << get_defs(GST_TYPE_ADAPTER)
            << get_defs(GST_TYPE_COLLECT_PADS)
            << get_defs(GST_TYPE_DATA_QUEUE)
            << get_defs(GST_TYPE_CONTROLLER)
            << get_defs(GST_TYPE_CONTROL_SOURCE)
            << get_defs(GST_TYPE_INTERPOLATION_CONTROL_SOURCE)
            << get_defs(GST_TYPE_LFO_CONTROL_SOURCE)
            << get_defs(GST_TYPE_NET_CLIENT_CLOCK)
            << get_defs(GST_TYPE_NET_TIME_PROVIDER)
            << get_defs(GST_TYPE_NET_TIME_PROVIDER)

  // GStreamer core plugin types:
            << get_plugin_defs("capsfilter")
            << get_plugin_defs("fakesrc")
            << get_plugin_defs("fakesink")
            << get_plugin_defs("fdsink")
            << get_plugin_defs("fdsrc")
            << get_plugin_defs("filesrc")
            << get_plugin_defs("filesink")
            << get_plugin_defs("identity")
            << get_plugin_defs("multiqueue")
            << get_plugin_defs("queue")
            << get_plugin_defs("tee")
            << get_plugin_defs("typefind")

  // gst-plugins-base (GStreamer base) types:
            << get_defs(GST_TYPE_AUDIO_CLOCK)
            << get_defs(GST_TYPE_AUDIO_FILTER)
            << get_defs(GST_TYPE_BASE_AUDIO_SINK)
            << get_defs(GST_TYPE_BASE_AUDIO_SRC)
            << get_defs(GST_TYPE_AUDIO_SINK)
            << get_defs(GST_TYPE_AUDIO_SRC)
            << get_defs(GST_TYPE_RING_BUFFER)
            << get_defs(GST_TYPE_CDDA_BASE_SRC)
            << get_defs(GST_TYPE_NETBUFFER)
            << get_defs(GST_TYPE_BASE_RTP_AUDIO_PAYLOAD)
            << get_defs(GST_TYPE_BASE_RTP_DEPAYLOAD)
            << get_defs(GST_TYPE_BASE_RTP_PAYLOAD)
            << get_defs(GST_TYPE_TAG_DEMUX)
            << get_defs(GST_TYPE_VIDEO_SINK)
            << get_defs(GST_TYPE_VIDEO_FILTER)

  // gst-plugins-base (GStreamer base) interfaces:
            << get_defs(GST_TYPE_COLOR_BALANCE)
            << get_defs(GST_TYPE_COLOR_BALANCE_CHANNEL)
            << get_defs(GST_TYPE_MIXER)
            << get_defs(GST_TYPE_MIXER_TRACK)
            << get_defs(GST_TYPE_MIXER_OPTIONS)
            << get_defs(GST_TYPE_NAVIGATION)
            << get_defs(GST_TYPE_PROPERTY_PROBE)
            << get_defs(GST_TYPE_TUNER)
            << get_defs(GST_TYPE_TUNER_CHANNEL)
            << get_defs(GST_TYPE_TUNER_NORM)
            << get_defs(GST_TYPE_VIDEO_ORIENTATION)
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
            << get_plugin_defs("tcpclientsrc")
            << get_plugin_defs("tcpclientsink")
            << get_plugin_defs("tcpserversrc")
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

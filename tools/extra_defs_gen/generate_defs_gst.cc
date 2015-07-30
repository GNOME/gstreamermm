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

// Core includes
#include <gst/gst.h>

// Core library includes
#include <gst/base/gstadapter.h>
#include <gst/base/gstbaseparse.h>
#include <gst/base/gstbasesink.h>
#include <gst/base/gstbasesrc.h>
#include <gst/base/gstbasetransform.h>

#include <gst/base/gstcollectpads.h>
#include <gst/base/gstpushsrc.h>

#include <gst/gstcontrolsource.h>
#include <gst/gstcontrolbinding.h>

#include <gst/controller/gstinterpolationcontrolsource.h>
#include <gst/controller/gstlfocontrolsource.h>

#include <gst/net/gstnetclientclock.h>
#include <gst/net/gstnettimeprovider.h>


// Base library includes
#include <gst/audio/audio.h>
#include <gst/audio/audio-enumtypes.h>
#include <gst/audio/gstaudiobasesink.h>
#include <gst/audio/gstaudiobasesrc.h>
#include <gst/audio/gstaudiocdsrc.h>
#include <gst/audio/gstaudioclock.h>
#include <gst/audio/gstaudiodecoder.h>
#include <gst/audio/gstaudioencoder.h>
#include <gst/audio/gstaudiofilter.h>
#include <gst/audio/gstaudioringbuffer.h>
#include <gst/audio/gstaudiosink.h>
#include <gst/audio/gstaudiosrc.h>
#include <gst/audio/streamvolume.h>

#include <gst/rtp/gstrtpbaseaudiopayload.h>
#include <gst/rtp/gstrtpbasedepayload.h>
#include <gst/rtp/gstrtpbasepayload.h>

#include <gst/tag/gsttagdemux.h>

#include <gst/video/video.h>
#include <gst/video/gstvideodecoder.h>
#include <gst/video/gstvideoencoder.h>
#include <gst/video/gstvideofilter.h>
#include <gst/video/gstvideopool.h>
#include <gst/video/gstvideosink.h>
#include <gst/video/gstvideoutils.h>
#include <gst/video/videoorientation.h>
#include <gst/video/video-overlay-composition.h>
#include <gst/video/videooverlay.h>

#include <gst/video/colorbalancechannel.h>
#include <gst/video/colorbalance.h>

#include <gst/video/navigation.h>


#include <gst/pbutils/pbutils.h>
#include <gst/tag/tag.h>


bool gst_type_is_a_pointer(GType gtype)
{
  return (gtype_is_a_pointer(gtype));
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
            << get_defs(GST_TYPE_GHOST_PAD, gst_type_is_a_pointer)
            << get_defs(GST_TYPE_MESSAGE, gst_type_is_a_pointer)
            << get_defs(GST_TYPE_OBJECT, gst_type_is_a_pointer)
            << get_defs(GST_TYPE_PAD, gst_type_is_a_pointer)
            << get_defs(GST_TYPE_PAD_TEMPLATE, gst_type_is_a_pointer)
            << get_defs(GST_TYPE_STATIC_PAD_TEMPLATE, gst_type_is_a_pointer)
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

  // GStreamer core library types:
            << get_defs(GST_TYPE_BASE_SRC, gst_type_is_a_pointer)
            << get_defs(GST_TYPE_BASE_SINK, gst_type_is_a_pointer)
            << get_defs(GST_TYPE_BASE_TRANSFORM, gst_type_is_a_pointer)
            << get_defs(GST_TYPE_BASE_PARSE, gst_type_is_a_pointer)
            << get_defs(GST_TYPE_PUSH_SRC, gst_type_is_a_pointer)
            << get_defs(GST_TYPE_ADAPTER, gst_type_is_a_pointer)
            << get_defs(GST_TYPE_COLLECT_PADS, gst_type_is_a_pointer)
            << get_defs(GST_TYPE_CONTROL_SOURCE, gst_type_is_a_pointer)
            << get_defs(GST_TYPE_CONTROL_BINDING, gst_type_is_a_pointer)
            << get_defs(GST_TYPE_INTERPOLATION_CONTROL_SOURCE, gst_type_is_a_pointer)
            << get_defs(GST_TYPE_LFO_CONTROL_SOURCE, gst_type_is_a_pointer)
            << get_defs(GST_TYPE_NET_CLIENT_CLOCK, gst_type_is_a_pointer)
            << get_defs(GST_TYPE_NET_TIME_PROVIDER, gst_type_is_a_pointer)

  // gst-plugins-base (GStreamer base) types:
            << get_defs(GST_TYPE_AUDIO_BASE_SINK, gst_type_is_a_pointer)
            << get_defs(GST_TYPE_AUDIO_BASE_SRC, gst_type_is_a_pointer)
            << get_defs(GST_TYPE_AUDIO_CD_SRC, gst_type_is_a_pointer)
            << get_defs(GST_TYPE_AUDIO_CLOCK, gst_type_is_a_pointer)
            << get_defs(GST_TYPE_AUDIO_FILTER, gst_type_is_a_pointer)
            << get_defs(GST_TYPE_AUDIO_RING_BUFFER, gst_type_is_a_pointer)
            << get_defs(GST_TYPE_AUDIO_SINK, gst_type_is_a_pointer)
            << get_defs(GST_TYPE_AUDIO_SRC, gst_type_is_a_pointer)
            << get_defs(GST_TYPE_DISCOVERER, gst_type_is_a_pointer)
            << get_defs(GST_TYPE_RTP_BASE_AUDIO_PAYLOAD, gst_type_is_a_pointer)
            << get_defs(GST_TYPE_RTP_BASE_DEPAYLOAD, gst_type_is_a_pointer)
            << get_defs(GST_TYPE_RTP_BASE_PAYLOAD, gst_type_is_a_pointer)
            << get_defs(GST_TYPE_TAG_DEMUX, gst_type_is_a_pointer)
            << get_defs(GST_TYPE_VIDEO_FILTER, gst_type_is_a_pointer)
            << get_defs(GST_TYPE_VIDEO_SINK, gst_type_is_a_pointer)

  // gst-plugins-base (GStreamer base) interfaces:
            << get_defs(GST_TYPE_COLOR_BALANCE, gst_type_is_a_pointer)
            << get_defs(GST_TYPE_COLOR_BALANCE_CHANNEL, gst_type_is_a_pointer)
            << get_defs(GST_TYPE_NAVIGATION, gst_type_is_a_pointer)
            << get_defs(GST_TYPE_STREAM_VOLUME, gst_type_is_a_pointer)
            << get_defs(GST_TYPE_VIDEO_ORIENTATION, gst_type_is_a_pointer)
            << get_defs(GST_TYPE_VIDEO_OVERLAY, gst_type_is_a_pointer)
            ;
  return 0;
}

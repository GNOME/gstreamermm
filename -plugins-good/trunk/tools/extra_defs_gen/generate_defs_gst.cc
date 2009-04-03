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
#include <gstreamermm_get_plugin_defs/get_plugin_defs.h>
#include <gst/gst.h>

int main (int argc, char *argv[])
{
  gst_init (&argc, &argv);

  std::cout << get_plugin_defs("aasink")
            << get_plugin_defs("alphacolor")
            << get_plugin_defs("apedemux")
            << get_plugin_defs("apev2mux")
            << get_plugin_defs("audioamplify")
            << get_plugin_defs("audiochebband")
            << get_plugin_defs("audiocheblimit")
            << get_plugin_defs("audiowsincband")
            << get_plugin_defs("audiowsinclimit")
            << get_plugin_defs("audiodynamic")
            << get_plugin_defs("audioinvert")
            << get_plugin_defs("audiopanorama")
            << get_plugin_defs("audiokaraoke")
            << get_plugin_defs("autoaudiosink")
            << get_plugin_defs("autovideosink")
            << get_plugin_defs("avidemux")
            << get_plugin_defs("avimux")
            << get_plugin_defs("avisubtitle")
            << get_plugin_defs("cacasink")
            << get_plugin_defs("cairotimeoverlay")
            << get_plugin_defs("cmmldec")
            << get_plugin_defs("cmmlenc")
            << get_plugin_defs("deinterleave")
            << get_plugin_defs("directdrawsink")
            << get_plugin_defs("directsoundsink")
            << get_plugin_defs("dv1394src")
            << get_plugin_defs("hdv1394src")
            << get_plugin_defs("dvdec")
            << get_plugin_defs("dvdemux")
            << get_plugin_defs("equalizer-10bands")
            << get_plugin_defs("equalizer-3bands")
            << get_plugin_defs("equalizer-nbands")
            << get_plugin_defs("esdsink")
            << get_plugin_defs("flacdec")
            << get_plugin_defs("flacenc")
            << get_plugin_defs("flactag")
            << get_plugin_defs("gamma")
            << get_plugin_defs("gdkpixbufsink")
            << get_plugin_defs("goom")
            << get_plugin_defs("goom2k1")
            << get_plugin_defs("halaudiosink")
            << get_plugin_defs("halaudiosrc")
            << get_plugin_defs("icydemux")
            << get_plugin_defs("id3demux")
            << get_plugin_defs("id3v2mux")
            << get_plugin_defs("interleave")
            << get_plugin_defs("jpegdec")
            << get_plugin_defs("jpegenc")
            << get_plugin_defs("level")
            << get_plugin_defs("monoscope")
            << get_plugin_defs("multifilesink")
            << get_plugin_defs("multifilesrc")
            << get_plugin_defs("multipartdemux")
            << get_plugin_defs("multipartmux")
            << get_plugin_defs("multiudpsink")
            << get_plugin_defs("ossmixer")
            << get_plugin_defs("osssink")
            << get_plugin_defs("osssrc")
            << get_plugin_defs("osxaudiosink")
            << get_plugin_defs("osxaudiosrc")
            << get_plugin_defs("osxvideosink")
            << get_plugin_defs("pngdec")
            << get_plugin_defs("pngenc")
            << get_plugin_defs("progressreport")
            << get_plugin_defs("pulsesink")
            << get_plugin_defs("pulsesrc")
            << get_plugin_defs("pulsemixer")
            << get_plugin_defs("qtdemux")
            << get_plugin_defs("rganalysis")
            << get_plugin_defs("rglimiter")
            << get_plugin_defs("rgvolume")
            << get_plugin_defs("rtpdec")
            << get_plugin_defs("rtspsrc")
            << get_plugin_defs("smokedec")
            << get_plugin_defs("smokeenc")
            << get_plugin_defs("smpte")
            << get_plugin_defs("smptealpha")
            << get_plugin_defs("souphttpsrc")
            << get_plugin_defs("spectrum")
            << get_plugin_defs("taginject")
            << get_plugin_defs("udpsrc")
            << get_plugin_defs("v4l2src")
            << get_plugin_defs("videobalance")
            << get_plugin_defs("videocrop")
            << get_plugin_defs("videoflip")
            << get_plugin_defs("videomixer")
            << get_plugin_defs("waveformsink")
            << get_plugin_defs("wavpackdec")
            << get_plugin_defs("wavpackenc")
            << get_plugin_defs("wavpackparse")
            << get_plugin_defs("wavparse")
            << get_plugin_defs("ximagesrc")
            ;
  return 0;
}

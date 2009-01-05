#!/bin/sh

# Note that h2def.py should be in PATH for this script to work and
# JHBUILD_SOURCES should be defined to contain the path to the root of the
# jhbuild sources.  Also this script should reside in
# gstreamermm/gstrearmer/src.

if [ -z "$JHBUILD_SOURCES" -o ! -x "`which h2def.py`" ]; then
  echo -e "JHBUILD_SOURCES must contain the path to the jhbuild sources and \
h2def.py\nneeds to be executable and in PATH."
  exit 1;
fi

DIR=`dirname "$0"`

PREFIX="$JHBUILD_SOURCES/gstreamer"
h2def.py "$PREFIX"/gst/*.h "$PREFIX"/libs/gst/{base,controller,dataprotocol,\
net,check}/*.h > "$DIR/gst_methods.defs"

PREFIX="$JHBUILD_SOURCES/gst-plugins-base"
h2def.py "$PREFIX"/gst-libs/gst/{audio,cdda,fft,floatcast,interfaces,netbuffer,\
riff,rtp,rtsp,sdp,tag,pbutils,video}/*.h >> "$DIR/gst_methods.defs"

#Patch generated file.
patch  $DIR/gst_methods.defs $DIR/gst_methods.defs.patch

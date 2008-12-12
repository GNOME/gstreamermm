#!/bin/sh

# Note that h2def.py should be in PATH for this script to work and
# JHBUILD_SOURCES should be defined to contain the path to the root of the
# jhbuild sources.  Also this script should reside in
# gstreamermm/gstrearmerbase/src.

if [ -z "$JHBUILD_SOURCES" -o ! -x "`which h2def.py`" ]; then
  echo -e "JHBUILD_SOURCES must contain the path to the jhbuild sources and \
  h2def.py\nneeds to be executable and in PATH."
  exit 1;
fi

PREFIX="$JHBUILD_SOURCES/gst-plugins-base"
DIR=`dirname "$0"`

h2def.py "$PREFIX"/gst-libs/gst/{audio,cdda,fft,floatcast,interfaces,netbuffer,\
riff,rtp,rtsp,sdp,tag,pbutils,video}/*.h "$PREFIX"/gst/*/*.h \
"$PREFIX"/ext/*/*.h > "$DIR/gstbase_methods.defs"

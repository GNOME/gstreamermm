#!/bin/bash

# Note that docextract_to_xml.py should be in PATH for this script to work and
# JHBUILD_SOURCES should be defined to contain the path to the root of the
# jhbuild sources.  Also this script should reside in
# gstreamermm/gstrearmer/src.

if [ -z "$JHBUILD_SOURCES" -o ! -x "`which docextract_to_xml.py`" ]; then
  echo -e "JHBUILD_SOURCES must contain path to jhbuild sources and \
docextract_to_xml.py\nneeds to be executable and in PATH."
  exit 1;
fi

PREFIX="$JHBUILD_SOURCES"
DIR=`dirname "$0"`

PARAMS="-s $PREFIX/gstreamer/gst/"

for dir in "$PREFIX"/gstreamer/libs/gst/{base,controller,dataprotocol,net,\
check} "$PREFIX"/gst-plugins-base/gst-libs/gst/{app,audio,cdda,fft,floatcast,\
interfaces,netbuffer,riff,rtp,rtsp,sdp,tag,pbutils,video}; do
  PARAMS="$PARAMS -s $dir"
done

docextract_to_xml.py --no-since $PARAMS > "$DIR/gst_docs.xml"

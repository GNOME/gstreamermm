#!/bin/sh

# Note that docextract_to_xml.py should be in PATH for this script to work and
# JHBUILD_SOURCES should be defined to contain the path to the root of the
# jhbuild sources.  Also this script should reside in
# gstreamermm/gstrearmerbase/src.

if [ -z "$JHBUILD_SOURCES" -o ! -x "`which docextract_to_xml.py`" ]; then
  echo -e "JHBUILD_SOURCES must contain path to jhbuild sources and \
  docextract_to_xml.py needs to be executable and in PATH."
  exit 1;
fi

PREFIX="$JHBUILD_SOURCES"
DIR=`dirname "$0"`

PARAMS="-s $PREFIX/gst-plugins-base/docs/libs/tmpl"

for dir in "$PREFIX"/gst-plugins-base/gst-libs/gst/{audio,cdda,fft,floatcast,\
interfaces,netbuffer,riff,rtp,rtsp,sdp,tag,pbutils,video}/; do
  PARAMS="$PARAMS -s $dir"
done

docextract_to_xml.py $PARAMS > "$DIR/gstbase_docs.xml"

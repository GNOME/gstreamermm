#!/bin/bash

# Note that JHBUILD_SOURCES should be defined to contain the path to the root
# of the jhbuild sources.  Also this script assumes that it resides in the
# tools/gen_scripts directory and the XML file will be placed in
# gstreamer/src.

if [ -z "$JHBUILD_SOURCES" ]; then
  echo -e "JHBUILD_SOURCES must contain path to jhbuild sources."
  exit 1;
fi

PREFIX="$JHBUILD_SOURCES"
ROOT_DIR="$(dirname "$0")/../.."
OUT_DIR="$ROOT_DIR/gstreamer/src"

PARAMS="-s $PREFIX/gstreamer/gst/"

for dir in "$PREFIX"/gstreamer/libs/gst/{base,check,controller,helpers,\
net} "$PREFIX"/gst-plugins-base/gst-libs/gst/{allocators,app,audio,fft,\
pbutils,riff,rtp,rtsp,sdp,tag,video}; do
  PARAMS="$PARAMS -s $dir"
done

DOCEXTRACT_TO_XML_PY="$JHBUILD_SOURCES/glibmm/tools/defs_gen/docextract_to_xml.py"
$DOCEXTRACT_TO_XML_PY --no-since $PARAMS > "$OUT_DIR/gst_docs.xml"

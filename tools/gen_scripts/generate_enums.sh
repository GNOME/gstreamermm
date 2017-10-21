#!/bin/bash

# Note that JHBUILD_SOURCES should be defined to contain the path to the root
# of the jhbuild sources.  Also this script assumes that it resides in the
# tools/gen_scripts directory and the defs file will be placed in
# gstreamer/src.

if [ -z "$JHBUILD_SOURCES" ]; then
  echo -e "JHBUILD_SOURCES must contain the path to the jhbuild sources."
  exit 1;
fi

ROOT_DIR="$(dirname "$0")/../.."
OUT_DIR="$ROOT_DIR/gstreamer/src"

PREFIX="$JHBUILD_SOURCES/gstreamer"
ENUM_PL="$JHBUILD_SOURCES/glibmm/tools/enum.pl"
$ENUM_PL "$PREFIX"/gst/*.h "$PREFIX"/libs/gst/{base,check,controller,\
dataprotocol,net}/*.h "$PREFIX"/plugins/elements/*.h > \
"$OUT_DIR/gst_enums.defs"

PREFIX="$JHBUILD_SOURCES/gst-plugins-base"
$ENUM_PL "$PREFIX"/gst-libs/gst/{allocators,app,audio,cdda,fft,floatcast,\
interfaces,netbuffer,pbutils,riff,rtp,rtsp,sdp,tag,video}/*.h \
"$PREFIX"/gst/*/*.h "$PREFIX"/ext/*/*.h >> "$OUT_DIR/gst_enums.defs"

#Patch generated file.
patch $OUT_DIR/gst_enums.defs $OUT_DIR/gst_enums.defs.patch



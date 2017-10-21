#!/bin/bash

# Note that JHBUILD_SOURCES should be defined to contain the path to the root
# of the jhbuild sources.  Also this script assumes that it resides in the
# tools/gen_script directory and the defs file will be placed in
# gstreamer/src.

if [ -z "$JHBUILD_SOURCES" -a ! -x "`which h2def.py`" ]; then
  echo -e "JHBUILD_SOURCES must contain the path to the jhbuild sources."
  exit 1;
fi

ROOT_DIR="$(dirname "$0")/../.."
OUT_DIR="$ROOT_DIR/gstreamer/src"

# Make bash remove empty pattern matches from the argument list because
# h2def.py breaks if no *.h files are found in a directory.
shopt -s nullglob

H2DEF_PY="$JHBUILD_SOURCES/glibmm/tools/defs_gen/h2def.py"

PREFIX="$JHBUILD_SOURCES/gstreamer"
$H2DEF_PY "$PREFIX"/gst/*.h "$PREFIX"/libs/gst/{base,check,controller,\
dataprotocol,net}/*.h > "$OUT_DIR/gst_methods.defs"

PREFIX="$JHBUILD_SOURCES/gst-plugins-base"
$H2DEF_PY  "$PREFIX"/gst-libs/gst/{allocators,app,audio,cdda,fft,floatcast,\
interfaces,netbuffer,pbutils,riff,rtp,rtsp,sdp,tag,video}/*.h >> \
"$OUT_DIR/gst_methods.defs"



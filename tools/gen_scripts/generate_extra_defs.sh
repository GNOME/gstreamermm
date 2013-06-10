#!/bin/bash

# Note that script assumes it resides in the tools/gen_scripts directory and
# the defs file will be placed in gstreamer/src.

ROOT_DIR="$(dirname "$0")/../.."
GEN_DIR="$ROOT_DIR/tools/extra_defs_gen"
OUT_DIR="$ROOT_DIR/gstreamer/src"

"$GEN_DIR"/generate_defs_gst > "$OUT_DIR"/gst_signals.defs

#Patch generated file.
patch $OUT_DIR/gst_signals.defs $OUT_DIR/gst_signals.defs.patch

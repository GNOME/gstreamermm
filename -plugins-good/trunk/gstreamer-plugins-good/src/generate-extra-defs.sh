#!/bin/sh

# Note that script assumes it resides in the
# gstreamermm-plugins-good/gstreamer-plugins-good/src directory.

DIR=`dirname "$0"`

"$DIR"/../../tools/extra_defs_gen/generate_defs_gst > "$DIR/gst_signals.defs"

#!/bin/sh

# Note that script assumes it resides in the gstreamermm/gstreamer/src
# directory.

DIR=`dirname "$0"`

"$DIR"/../../tools/extra_defs_gen/generate_defs_gst > "$DIR/gst_signals.defs"

#Patch generated file.
(cd "$DIR" && patch -p0 < gst_signals.defs.patch)

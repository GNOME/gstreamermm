#!/bin/sh

# Note that script assumes it resides in the gstreamermm/gstreamer/src
# directory.

DIR=`dirname "$0"`

$DIR/../../tools/extra_defs_gen/generate_extra_defs > gst_signals.defs


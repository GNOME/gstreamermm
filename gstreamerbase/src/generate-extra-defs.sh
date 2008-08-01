#!/bin/sh

# Note that script assumes it resides in gstreamermm/gstreamerbase/src
# directory.

DIR=`dirname "$0"`

$DIR/../../tools/extra_defs_gen/generate_defs_gstbase > gstbase_signals.defs


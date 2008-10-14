#!/bin/sh

# Note that h2def.py should be in PATH for this script to work and
# JHBUILD_PREFIX should be defined to contain the path to the prefix (install)
# directory of jhbuild.  Also this script should reside in
# gstreamermm/gstrearmer/src.

if [ -z "$JHBUILD_PREFIX" -o ! -x "`which h2def.py`" ]; then
  echo "JHBUILD_PREFIX must contain path to jhbuild prefix and h2def.py needs to be executable and in PATH."
  exit 1;
fi

PREFIX="$JHBUILD_PREFIX"
DIR=`dirname "$0"`

h2def.py "$PREFIX"/include/gstreamer-0.10/gst/*.h "$PREFIX"/include/gstreamer-0.10/gst/{base,controller,dataprotocol,net,check}/*.h > "$DIR/gst_methods.defs"

#Patch generated file.
(cd "$DIR" && patch -p0 < gst_methods.defs.patch)

#!/bin/sh

# Note that h2def.py should be in PATH for this script to work and
# JHBUILD_PREFIX should be defined to contain the path to the prefix (install)
# directory of jhbuild.

PREFIX=$JHBUILD_PREFIX

h2def.py $PREFIX/include/gstreamer-0.10/gst/*.h $PREFIX/include/gstreamer-0.10/gst/{base,controller,dataprotocol,net,check}/*.h > gst_methods.defs


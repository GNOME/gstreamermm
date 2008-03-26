#!/bin/sh

# Note that h2def.py should be in $PATH for this script to work

PREFIX=/opt/usr-jhbuild

h2def.py $PREFIX/include/gstreamer-0.10/gst/*.h /opt/usr-jhbuild/include/gstreamer-0.10/gst/{base,controller,dataprotocol,net,check}/*.h > gst_methods.defs

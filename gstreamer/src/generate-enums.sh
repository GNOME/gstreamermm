#!/bin/sh

# Note that enum.pl should be in $PATH for this script to work

PREFIX=/opt/usr-jhbuild

enum.pl $PREFIX/include/gstreamer-0.10/gst/*.h /opt/usr-jhbuild/include/gstreamer-0.10/gst/{base,controller,dataprotocol,net,check}/*.h > gst_enums.defs

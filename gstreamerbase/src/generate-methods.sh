#!/bin/sh

# Note that h2def.py should be in $PATH for this script to work

PREFIX=/opt/usr-jhbuild

h2def.py $PREFIX/include/gstreamer-0.10/gst/{audio,cdda,fft,floatcast,interfaces,netbuffer,riff,rtp,rtsp,sdp,tag,pbutils,video}/*.h > gstbase_methods.defs

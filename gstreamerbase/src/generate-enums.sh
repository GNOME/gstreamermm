#!/bin/sh

# Note that enum.pl should be in $PATH for this script to work

PREFIX=/opt/usr-jhbuild

enum.pl $PREFIX/include/gstreamer-0.10/gst/{audio,cdda,fft,floatcast,interfaces,netbuffer,riff,rtp,rtsp,sdp,tag,pbutils,video}/*.h > gstbase_enums.defs

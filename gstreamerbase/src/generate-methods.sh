#!/bin/sh

# Note that h2def.py should be in PATH for this script to work and
# JHBUILD_PREFIX should be defined to contain the path to the prefix (install)
# directory of jhbuild.

PREFIX=$JHBUILD_PREFIX

h2def.py $PREFIX/include/gstreamer-0.10/gst/{audio,cdda,fft,floatcast,interfaces,netbuffer,riff,rtp,rtsp,sdp,tag,pbutils,video}/*.h > gstbase_methods.defs


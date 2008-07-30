#!/bin/sh

# Note that docextract_to_xml.py should be in PATH for this script to work and
# JHBUILD_SOURCES should be defined to contain the path to the root of the
# jhbuild sources.

PREFIX=$JHBUILD_SOURCES 

PARAMS="-s $PREFIX/gstreamer/gst/ -s $PREFIX/gstreamer/docs/gst/tmpl -s $PREFIX/gstreamer/docs/libs/tmpl"

for dir in $PREFIX/gstreamer/libs/gst/{base,controller,dataprotocol,net,check}/ ; do
  PARAMS="$PARAMS -s $dir"
done

docextract_to_xml.py $PARAMS > gst_docs.xml

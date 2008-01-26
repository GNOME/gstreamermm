doxyfile=Doxyfile
doxygenprog=@DOXYGEN@

html/index.html:
	rm -rf html
	$(doxygenprog) $(doxyfile)

htmlfiles=$(shell ls -1 html/*.html)
pngfiles=$(shell ls -1 html/*.png)
giffiles=$(shell ls -1 html/*.gif)
cssfiles=$(shell ls -1 html/*.css)
websitefiles=reference-index.txt

docdir = $(datadir)/doc/gstreamermm-0.10/docs
htmldocumentationdir=$(docdir)/reference/html
htmldocumentation_DATA=$(htmlfiles) $(pngfiles) $(giffiles) $(cssfiles)

all: html/index.html

clean-local:
	-rm -rf html
	-rm doxygen-warnings.txt

EXTRA_DIST=$(doxyfile) $(htmlfiles) \
$(pngfiles) $(giffiles) $(cssfiles) \
$(websitefiles)


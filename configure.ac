## Copyright 2009 The gstreamermm Development Team
##
## This library is free software: you can redistribute it and/or modify it
## under the terms of the GNU Lesser General Public License as published
## by the Free Software Foundation, either version 2.1 of the License,
## or (at your option) any later version.
##
## This library is distributed in the hope that it will be useful,
## but WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
## Lesser General Public License for more details.
##
## You should have received a copy of the GNU Lesser General Public License
## along with this program.  If not, see <http://www.gnu.org/licenses/>.

AC_INIT([gstreamermm], [0.10.5],
        [http://bugzilla.gnome.org/enter_bug.cgi?product=gstreamermm],
        [gstreamermm], [http://www.gtkmm.org/])
AC_PREREQ([2.59])

AC_CONFIG_SRCDIR([gstreamer/gstreamermm.h])
AC_CONFIG_AUX_DIR([build])
AC_CONFIG_MACRO_DIR([build])
AC_CONFIG_HEADERS([config.h gstreamer/gstreamermmconfig.h])

MM_PREREQ([0.7.2])
MM_INIT_MODULE([gstreamermm-0.10])

# http://www.gnu.org/software/libtool/manual/html_node/Updating-version-info.html
AC_SUBST([GSTREAMERMM_SO_VERSION], [2:1:0])

AM_INIT_AUTOMAKE([1.9 -Wno-portability check-news dist-bzip2 no-define nostdinc tar-pax])
AM_MAINTAINER_MODE
AC_ARG_VAR([ACLOCAL_FLAGS], [aclocal flags, e.g. -I <macro dir>])

AC_PROG_CXX
AC_DISABLE_STATIC
AC_LIBTOOL_WIN32_DLL
AC_PROG_LIBTOOL

min_glibmm_version='2.21.1'
min_gtkmm_version='2.12.0'
min_gstreamer_version='0.10.24'
min_libxmlpp_version='2.14.0'

## The format below is used so that the requirements appear nicely in the .pc
## file.
AC_SUBST([GSTREAMERMM_MODULES],
         ["\
glibmm-2.4 >= $min_glibmm_version \
giomm-2.4 >= $min_glibmm_version \
libxml++-2.6 >= $min_libxmlpp_version \
gstreamer-0.10 >= $min_gstreamer_version \
gstreamer-base-0.10 >= $min_gstreamer_version \
gstreamer-controller-0.10 >= $min_gstreamer_version \
gstreamer-dataprotocol-0.10 >= $min_gstreamer_version \
gstreamer-net-0.10 >= $min_gstreamer_version \
gstreamer-plugins-base-0.10 >= $min_gstreamer_version \
gstreamer-audio-0.10 >= $min_gstreamer_version \
gstreamer-cdda-0.10 >= $min_gstreamer_version \
gstreamer-interfaces-0.10 >= $min_gstreamer_version \
gstreamer-netbuffer-0.10 >= $min_gstreamer_version \
gstreamer-rtp-0.10 >= $min_gstreamer_version \
gstreamer-video-0.10 >= $min_gstreamer_version"
])

PKG_CHECK_MODULES([GSTREAMERMM], [$GSTREAMERMM_MODULES])

MM_PKG_CONFIG_SUBST([GTHREAD_CFLAGS], [--cflags-only-other gthread-2.0])
MM_PKG_CONFIG_SUBST([GMMPROC_DIR], [--variable=gmmprocdir glibmm-2.4])

MM_ARG_ENABLE_DOCUMENTATION
MM_ARG_WITH_TAGFILE_DOC([libstdc++.tag], [mm-common-libstdc++])
MM_ARG_WITH_TAGFILE_DOC([libsigc++-2.0.tag], [sigc++-2.0])
MM_ARG_WITH_TAGFILE_DOC([glibmm-2.4.tag], [glibmm-2.4])
MM_ARG_WITH_TAGFILE_DOC([giomm-2.4.tag], [giomm-2.4])

AC_LANG([C++])
MM_ARG_ENABLE_WARNINGS([GSTREAMERMM_WXXFLAGS],
                       [-Wall],
                       [-pedantic -Wall -Wextra],
                       [G GSTREAMER])

#########################################################################
#  Examples
#########################################################################

AC_ARG_ENABLE(examples,
  [AC_HELP_STRING([--enable-examples],
    [enable compilation of example programs [default=yes]])],
  [enable_examples=$enableval], [enable_examples=yes])

if test "x$enable_examples" = "xyes"; then

# Extra dependencies needed for the examples. Use --enable-examples=no to build
# the library without this.
PKG_CHECK_MODULES(GSTREAMERMM_EXAMPLES, gtkmm-2.4 >= ${min_gtkmm_version})
AC_SUBST(GSTREAMERMM_EXAMPLES_CFLAGS)
AC_SUBST(GSTREAMERMM_EXAMPLES_LIBS)

MM_ARG_WITH_TAGFILE_DOC([gtkmm-2.4.tag], [gtkmm-2.4])

EXAMPLE_SUBDIR="examples"
AC_CONFIG_FILES([
    examples/Makefile
    ])
AC_SUBST(EXAMPLE_SUBDIR)
else
EXAMPLE_SUBDIR=""
fi

#########################################################################
#  Plug-in definitions
#########################################################################

# To add a plugin, add the plugin definition, in the form of
# "plugin=CppClassName" to the space-separated list of definitions below.
# (Where "plugin" is the plugin name as recognized by gst-inspect and
# "CppClassName" is the desired name of the C++ class.)
#
# Also add the target .hg file name to the plugins_hg variable in the
# gstreamer/src/fileslist.am.  (That must be the same as "CppClassName" - all
# in lowercase with a .hg extension).  Make sure that the order of both lists
# correspond.

# TODO: Include appsink and appsrc plug-ins in list below if they indeed are
# plug-ins (see gst-plugins-base docs for details) and when they don't cause
# gstreamermm initialization errors.
GSTREAMERMM_PLUGIN_DEFS="\
adder=Adder \
alsamixer=AlsaMixer \
alsasink=AlsaSink \
alsasrc=AlsaSrc \
audioconvert=AudioConvert \
audioresample=AudioResample \
audiotestsrc=AudioTestSrc \
capsfilter=CapsFilter \
cdparanoiasrc=CdParanoiaSrc \
clockoverlay=ClockOverlay \
decodebin2=DecodeBin2 \
decodebin=DecodeBin \
fakesink=FakeSink \
fakesrc=FakeSrc \
fdsink=FdSink \
fdsrc=FdSrc \
ffmpegcolorspace=FfmpegColorSpace \
filesink=FileSink \
filesrc=FileSrc \
gdpdepay=GDPDepay \
gdppay=GDPPay \
giosink=GioSink \
giosrc=GioSrc \
giostreamsink=GioStreamSink \
giostreamsrc=GioStreamSrc \
identity=Identity \
multifdsink=MultiFdSink \
multiqueue=MultiQueue \
oggdemux=OggDemux \
oggmux=OggMux \
playbin2=PlayBin2 \
playbin=PlayBin \
queue=Queue \
tcpclientsink=TCPClientSink \
tcpclientsrc=TCPClientSrc \
tcpserversink=TcpServerSink \
tcpserversrc=TCPServerSrc \
tee=Tee \
textoverlay=TextOverlay \
textrender=TextRender \
theoradec=TheoraDec \
theoraenc=TheoraEnc \
theoraparse=TheoraParse \
timeoverlay=TimeOverlay \
typefind=TypeFindElement \
uridecodebin=UriDecodeBin \
videorate=VideoRate \
videoscale=VideoScale \
videotestsrc=VideoTestSrc \
volume=Volume \
vorbisdec=VorbisDec \
vorbisenc=VorbisEnc \
vorbisparse=VorbisParse \
vorbistag=VorbisTag \
ximagesink=XImageSink \
xvimagesink=XvImageSink \
"

AC_SUBST(GSTREAMERMM_PLUGIN_DEFS)

#########################################################################

AC_CONFIG_FILES([Makefile
                 tools/Makefile
                 tools/generate_gst_wrap_init.pl
                 gstreamer/${GSTREAMERMM_MODULE_NAME}.pc:gstreamer/gstreamermm.pc.in
                 gstreamer/${GSTREAMERMM_MODULE_NAME}-uninstalled.pc:gstreamer/gstreamermm-uninstalled.pc.in
                 gstreamer/src/Makefile
                 gstreamer/gstreamermm/Makefile
                 tests/Makefile
                 docs/Makefile
                 docs/reference/Doxyfile])
AC_OUTPUT

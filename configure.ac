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

m4_define([GSTMM_VERSION], [1.10.0])

AC_INIT([gstreamermm], [1.10.0],
        [http://bugzilla.gnome.org/enter_bug.cgi?product=gstreamermm],
        [gstreamermm], [http://www.gtkmm.org/])
AC_PREREQ([2.59])

AC_CONFIG_SRCDIR([gstreamer/gstreamermm.h])
AC_CONFIG_AUX_DIR([build])
AC_CONFIG_MACRO_DIR([build])
AC_CONFIG_HEADERS([config.h gstreamer/gstreamermmconfig.h])

MM_PREREQ([0.9.8])
MM_INIT_MODULE([gstreamermm-1.0])

# Copy the mm-common .pl scripts into docs/,
# and use them from there,
# so we can dist them to avoid a tarball-build dependency.
MM_CONFIG_DOCTOOL_DIR([docs])

# http://www.gnu.org/software/libtool/manual/html_node/Updating-version-info.html
AC_SUBST([GSTREAMERMM_SO_VERSION], [1:0:0])

AM_INIT_AUTOMAKE([1.9 subdir-objects -Wno-portability check-news dist-bzip2 no-define nostdinc tar-ustar])
m4_ifdef([AM_SILENT_RULES], [AM_SILENT_RULES([yes])])
AM_MAINTAINER_MODE
AC_ARG_VAR([ACLOCAL_FLAGS], [aclocal flags, e.g. -I <macro dir>])

AC_PROG_CXX
MM_AX_CXX_COMPILE_STDCXX_11([noext],[mandatory])

AC_DISABLE_STATIC
AC_LIBTOOL_WIN32_DLL
AC_PROG_LIBTOOL

# Check for m4 and sed which are used for plug-in .hg and .ccg file generation.
AC_CHECK_PROGS([M4], [gm4 m4], [m4])
AC_PROG_SED

# TODO: This makes no sense. --danielk
AS_IF([test "x$enable_static" = xyes],
[
  AC_DEFINE([GSTREAMERMM_STATIC_LIB], [1], [Define if gstreamermm is built as a static library])
])

# The format below is used so that the requirements appear nicely in the .pc
# file.

AC_SUBST([GSTREAMERMM_MODULES],
         ['giomm-2.4 >= 2.47.6[]m4_foreach([gstmm_mod],
         [[], [-base], [-check], [-controller], [-net],
          [-allocators], [-app], [-audio], [-fft], [-pbutils],
          [-plugins-base], [-riff], [-rtp], [-rtsp], [-sdp],
          [-tag], [-video]],
         [ gstreamer[]m4_defn([gstmm_mod])[]-1.0 >= GSTMM_VERSION])'])

PKG_CHECK_MODULES([GSTREAMERMM], [$GSTREAMERMM_MODULES])

PKG_CHECK_MODULES([GUI_EXAMPLES], [$GSTREAMERMM_MODULES gtkmm-3.0 >= 3.0],
                  [gstmm_enable_gui_examples=yes], [gstmm_enable_gui_examples=no])

AS_IF([test "x$gstmm_enable_gui_examples" != xyes],
      [AC_MSG_WARN([gtkmm not available: GUI examples will not be built.])])
AM_CONDITIONAL([ENABLE_GUI_EXAMPLES], [test "x$gstmm_enable_gui_examples" = xyes])

MM_PKG_CONFIG_SUBST([GMMPROC_DIR], [--variable=gmmprocdir glibmm-2.4])

MM_ARG_ENABLE_DOCUMENTATION
MM_ARG_WITH_TAGFILE_DOC([libstdc++.tag], [mm-common-libstdc++])
MM_ARG_WITH_TAGFILE_DOC([libsigc++-2.0.tag], [sigc++-2.0])
MM_ARG_WITH_TAGFILE_DOC([glibmm-2.4.tag], [glibmm-2.4])
MM_ARG_WITH_TAGFILE_DOC([cairomm-1.0.tag], [cairomm-1.0])
MM_ARG_WITH_TAGFILE_DOC([pangomm-1.4.tag], [pangomm-1.4])

AC_ARG_ENABLE(unittests,
       AS_HELP_STRING([--enable-unittests=@<:@yes/no/auto@:>@], 
       [Enable unit tests]),
       [enable_unittests=$enableval],
       [enable_unittests=auto])

AS_IF([test "$enable_unittests" != no],[
       AC_CHECK_LIB([gtest_main], [main], [have_gtest=yes],[have_gtest=no])
       AS_IF([test "$enable_unittests" = "yes" && test "$have_gtest" = "no"],
               AC_MSG_FAILURE([Unit tests are enabled so gtest library is required for building unit tests.])], [enable_unittests=$have_gtest)
])

AC_SUBST([ENABLE_UNITTESTS], ["$enable_unittests"])


#########################################################################
#  Plug-in processing
#########################################################################

# To add a plugin, add the plugin definition, in the form of
# "hgfilebasename|plugin|CppClassName" to the space-separated list of
# definitions below.  (Where "hgfilebasename" is the basename of the .hg file,
# "plugin" is the plugin name as recognized by gst-inspect and "CppClassName"
# is the desired name of the C++ class.)
#
# Also add the target .hg file name to the plugins_hg variable in the
# gstreamer/src/fileslist.am.  (That must be the same as "CppClassName" - all
# in lowercase with a .hg extension).
AC_SUBST([GSTREAMERMM_CORE_PLUGIN_DEFS], ["\
capsfilter|capsfilter|CapsFilter \
concat|concat|Concat \
downloadbuffer|downloadbuffer|DownloadBuffer \
fakesink|fakesink|FakeSink \
fakesrc|fakesrc|FakeSrc \
fdsink|fdsink|FdSink \
fdsrc|fdsrc|FdSrc \
filesink|filesink|FileSink \
filesrc|filesrc|FileSrc \
funnel|funnel|Funnel \
identity|identity|Identity \
inputselector|input-selector|InputSelector \
multiqueue|multiqueue|MultiQueue \
outputselector|output-selector|OutputSelector \
streamiddemux|streamiddemux|StreamidDemux \
queue|queue|Queue \
queue2|queue2|Queue2 \
tee|tee|Tee \
typefindelement|typefind|TypeFindElement \
valve|valve|Valve
"])
#audioresample|audioresample|AudioResample 
AC_SUBST([GSTREAMERMM_BASE_PLUGIN_DEFS], ["\
adder|adder|Adder \
alsasink|alsasink|AlsaSink \
alsasrc|alsasrc|AlsaSrc \
appsink|appsink|AppSink \
appsrc|appsrc|AppSrc \
audioconvert|audioconvert|AudioConvert \
audiorate|audiorate|AudioRate \
audiotestsrc|audiotestsrc|AudioTestSrc \
cdparanoiasrc|cdparanoiasrc|CdParanoiaSrc \
clockoverlay|clockoverlay|ClockOverlay \
decodebin|decodebin|DecodeBin \
encodebin|encodebin|EncodeBin \
giosink|giosink|GioSink \
giosrc|giosrc|GioSrc \
giostreamsink|giostreamsink|GioStreamSink \
giostreamsrc|giostreamsrc|GioStreamSrc \
multifdsink|multifdsink|MultiFdSink \
multisocketsink|multisocketsink|MultiSocketSink \
oggdemux|oggdemux|OggDemux \
oggmux|oggmux|OggMux \
playbin|playbin|PlayBin \
playsink|playsink|PlaySink \
socketsrc|socketsrc|SocketSrc \
streamsynchronizer|streamsynchronizer|StreamSynchronizer \
subtitleoverlay|subtitleoverlay|SubtitleOverlay \
tcpclientsink|tcpclientsink|TCPClientSink \
tcpclientsrc|tcpclientsrc|TCPClientSrc \
tcpserversink|tcpserversink|TCPServerSink \
tcpserversrc|tcpserversrc|TCPServerSrc \
textoverlay|textoverlay|TextOverlay \
textrender|textrender|TextRender \
theoradec|theoradec|TheoraDec \
theoraenc|theoraenc|TheoraEnc \
theoraparse|theoraparse|TheoraParse \
timeoverlay|timeoverlay|TimeOverlay \
uridecodebin|uridecodebin|UriDecodeBin \
videoconvert|videoconvert|VideoConvert \
videorate|videorate|VideoRate \
videoscale|videoscale|VideoScale \
videotestsrc|videotestsrc|VideoTestSrc \
volume|volume|Volume \
vorbisdec|vorbisdec|VorbisDec \
vorbisenc|vorbisenc|VorbisEnc \
vorbisparse|vorbisparse|VorbisParse \
vorbistag|vorbistag|VorbisTag \
ximagesink|ximagesink|XImageSink \
xvimagesink|xvimagesink|XvImageSink
"])

GENERATE_PLUGINS_LIST_FILE([gstreamer/src/plugin_filelist.am], $GSTREAMERMM_CORE_PLUGIN_DEFS)
GENERATE_PLUGINS_LIST_FILE([gstreamer/src/plugin_filelist.am], $GSTREAMERMM_BASE_PLUGIN_DEFS)

#########################################################################

AC_LANG([C++])
MM_ARG_ENABLE_WARNINGS([GSTREAMERMM_WXXFLAGS],
                       [-Wall], [-Wall -Wextra],
                       [G GSTREAMER])

# Offer the ability to omit some API from the library,
# to reduce the code size:
MM_ARG_DISABLE_DEPRECATED_API([GSTREAMERMM])

AC_CONFIG_FILES([Makefile
                 tools/Makefile
                 gstreamer/${GSTREAMERMM_MODULE_NAME}.pc:gstreamer/gstreamermm.pc.in
                 gstreamer/${GSTREAMERMM_MODULE_NAME}-uninstalled.pc:gstreamer/gstreamermm-uninstalled.pc.in
                 gstreamer/src/Makefile
                 gstreamer/gstreamermm/Makefile
                 examples/Makefile
                 tests/Makefile
                 docs/Makefile
                 docs/reference/Doxyfile])
AC_OUTPUT

cat <<EOF

${PACKAGE}-${VERSION}

  Build Environment
    Install Prefix:              ${prefix}

  Libraries
    GStreamer Version:           $(pkg-config --modversion gstreamer-1.0)

  Extra features
    Use deprecated API:          ${mm_enable_deprecated_api}
    GUI Examples:                ${gstmm_enable_gui_examples}
    Unit Tests:                  ${enable_unittests}

EOF

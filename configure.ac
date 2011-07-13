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

AC_INIT([gstreamermm], [0.10.9.1],
        [http://bugzilla.gnome.org/enter_bug.cgi?product=gstreamermm],
        [gstreamermm], [http://www.gtkmm.org/])
AC_PREREQ([2.59])

AC_CONFIG_SRCDIR([gstreamer/gstreamermm.h])
AC_CONFIG_AUX_DIR([build])
AC_CONFIG_MACRO_DIR([build])
AC_CONFIG_HEADERS([config.h gstreamer/gstreamermmconfig.h])

MM_PREREQ([0.9.5])
MM_INIT_MODULE([gstreamermm-0.10])

# Copy the mm-common .pl scripts into docs/,
# and use them from there,
# so we can dist them to avoid a tarball-build dependency.
MM_CONFIG_DOCTOOL_DIR([docs])

# http://www.gnu.org/software/libtool/manual/html_node/Updating-version-info.html
AC_SUBST([GSTREAMERMM_SO_VERSION], [2:1:0])

AM_INIT_AUTOMAKE([1.9 -Wno-portability check-news dist-bzip2 no-define nostdinc tar-ustar])
m4_ifdef([AM_SILENT_RULES], [AM_SILENT_RULES])
AM_MAINTAINER_MODE
AC_ARG_VAR([ACLOCAL_FLAGS], [aclocal flags, e.g. -I <macro dir>])

AC_PROG_CXX
AC_DISABLE_STATIC
AC_LIBTOOL_WIN32_DLL
AC_PROG_LIBTOOL

# Check for m4 and sed which are used for plug-in .hg and .ccg file generation.
AC_CHECK_PROGS([M4], [gm4 m4], [m4])
AC_PROG_SED

# The format below is used so that the requirements appear nicely in the .pc
# file.
AC_SUBST([GSTREAMERMM_MODULES],
         ['giomm-2.4 >= 2.28.0 libxml++-2.6 >= 2.14[]m4_foreach([gstmm_mod],
         [[], [-base], [-controller], [-dataprotocol], [-net], [-plugins-base],
              [-audio], [-cdda], [-interfaces], [-netbuffer], [-rtp], [-video]],
         [ gstreamer[]m4_defn([gstmm_mod])[]-0.10 >= 0.10.32])'])
PKG_CHECK_MODULES([GSTREAMERMM], [$GSTREAMERMM_MODULES])

PKG_CHECK_MODULES([GUI_EXAMPLES], [$GSTREAMERMM_MODULES gtkmm-2.4 >= 2.12],
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
#
# TODO: Include appsink and appsrc plug-ins in list below if they indeed are
# plug-ins (see gst-plugins-base docs for details) and when they don't cause
# gstreamermm initialization errors.

AC_SUBST([GSTREAMERMM_PLUGIN_DEFS], ["\
adder|adder|Adder \
alsamixer|alsamixer|AlsaMixer \
alsasink|alsasink|AlsaSink \
alsasrc|alsasrc|AlsaSrc \
audioconvert|audioconvert|AudioConvert \
audiorate|audiorate|AudioRate \
audioresample|audioresample|AudioResample \
audiotestsrc|audiotestsrc|AudioTestSrc \
capsfilter|capsfilter|CapsFilter \
cdparanoiasrc|cdparanoiasrc|CdParanoiaSrc \
clockoverlay|clockoverlay|ClockOverlay \
decodebin|decodebin|DecodeBin \
decodebin2|decodebin2|DecodeBin2 \
fakesink|fakesink|FakeSink \
fakesrc|fakesrc|FakeSrc \
fdsink|fdsink|FdSink \
fdsrc|fdsrc|FdSrc \
ffmpegcolorspace|ffmpegcolorspace|FfmpegColorSpace \
filesink|filesink|FileSink \
filesrc|filesrc|FileSrc \
funnel|funnel|Funnel \
gdpdepay|gdpdepay|GDPDepay \
gdppay|gdppay|GDPPay \
giosink|giosink|GioSink \
giosrc|giosrc|GioSrc \
giostreamsink|giostreamsink|GioStreamSink \
giostreamsrc|giostreamsrc|GioStreamSrc \
identity|identity|Identity \
inputselector|input-selector|InputSelector \
multifdsink|multifdsink|MultiFdSink \
multiqueue|multiqueue|MultiQueue \
oggdemux|oggdemux|OggDemux \
oggmux|oggmux|OggMux \
outputselector|output-selector|OutputSelector \
playbin|playbin|PlayBin \
playbin2|playbin2|PlayBin2 \
queue|queue|Queue \
queue2|queue2|Queue2 \
subtitleoverlay|subtitleoverlay|SubtitleOverlay \
tcpclientsink|tcpclientsink|TCPClientSink \
tcpclientsrc|tcpclientsrc|TCPClientSrc \
tcpserversink|tcpserversink|TcpServerSink \
tcpserversrc|tcpserversrc|TCPServerSrc \
tee|tee|Tee \
textoverlay|textoverlay|TextOverlay \
textrender|textrender|TextRender \
theoradec|theoradec|TheoraDec \
theoraenc|theoraenc|TheoraEnc \
theoraparse|theoraparse|TheoraParse \
timeoverlay|timeoverlay|TimeOverlay \
typefindelement|typefind|TypeFindElement \
uridecodebin|uridecodebin|UriDecodeBin \
valve|valve|Valve \
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

# Check for the existence of the plug-ins.  Note that this check doesn't
# work when cross-compiling.  That isn't much of a problem though since
# it only applies in maintainer-mode.
AS_IF([test "x$USE_MAINTAINER_MODE" != xno],
[
  gstmm_toolsdir=`$PKG_CONFIG --variable=toolsdir gstreamer-0.10 2>&AS_MESSAGE_LOG_FD`
  AC_PATH_PROGS([GST_INSPECT], [gst-inspect-0.10 gst-inspect],,
                [$gstmm_toolsdir$PATH_SEPARATOR$PATH])

  for gstmm_plugin_def in $GSTREAMERMM_PLUGIN_DEFS
  do
    # Extract plugin name and run gst-inspect to check whether the plugin
    # is installed on the build system.
    gstmm_plugin_name=`[expr "X$gstmm_plugin_def" : 'X.*|\(.*\)|.*$' 2>&]AS_MESSAGE_LOG_FD`
    AS_IF([$GST_INSPECT "$gstmm_plugin_name" >/dev/null 2>&AS_MESSAGE_LOG_FD],,
          [AC_MSG_FAILURE([[The gstreamer plug-in '$gstmm_plugin_name' does not exist.
If you built gst-plugins-base from source code then you might need to
install the appropriate -dev or -devel packages or enable experimental
plugins before rebuilding gst-plugins-base.]])])
  done
])

#########################################################################

AC_LANG([C++])
MM_ARG_ENABLE_WARNINGS([GSTREAMERMM_WXXFLAGS],
                       [-Wall], [-Wall -Wextra],
                       [G GSTREAMER])

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

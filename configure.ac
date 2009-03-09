# Configure.in
#
#  This file tests for various compiler features needed to configure 
#  the gtkmm package.  Original skeleton was provided by Stephan Kulow.
#  All tests were written by Tero Pulkkinen, Mirko Streckenbach, and 
#  Karl Nelson.
#
#  NOTE! IF YOU DO CHANGES HERE, CHECK IF YOU NEED TO MODIFY .m4 TOO!!!
#
#  Copyright 2001 Free Software Foundation
#  Copyright 1999 gtkmm Development Team
#  Copyright 1998 Stephan Kulow 
#

#We use pushdef here because we can't use shell variables before AC_INIT, but we want to use a variable with AC_INIT:
pushdef([GSTREAMERMM_MAJOR_VERSION],     [0])
pushdef([GSTREAMERMM_MINOR_VERSION],     [10])
pushdef([GSTREAMERMM_MICRO_VERSION],     [1])
pushdef([GSTREAMERMM_EXTRA_VERSION],     [])
pushdef([GSTREAMERMM_VERSION], GSTREAMERMM_MAJOR_VERSION.GSTREAMERMM_MINOR_VERSION.GSTREAMERMM_MICRO_VERSION[]GSTREAMERMM_EXTRA_VERSION)
AC_INIT([gstreamermm], GSTREAMERMM_VERSION, [gtkmm-list@gnome.org])
AC_CONFIG_SRCDIR([gstreamer/gstreamermmconfig.h.in])
AC_PREREQ(2.59)

#########################################################################
#  Version and initialization
#########################################################################
[GSTREAMERMM_MAJOR_VERSION]=GSTREAMERMM_MAJOR_VERSION
[GSTREAMERMM_MINOR_VERSION]=GSTREAMERMM_MINOR_VERSION
[GSTREAMERMM_MICRO_VERSION]=GSTREAMERMM_MICRO_VERSION
[GSTREAMERMM_EXTRA_VERSION]=GSTREAMERMM_EXTRA_VERSION
[GSTREAMERMM_VERSION]=GSTREAMERMM_VERSION
popdef([GSTREAMERMM_MAJOR_VERSION])
popdef([GSTREAMERMM_MINOR_VERSION])
popdef([GSTREAMERMM_MICRO_VERSION])
popdef([GSTREAMERMM_EXTRA_VERSION])
popdef([GSTREAMERMM_VERSION])
GSTREAMERMM_RELEASE=$GSTREAMERMM_MAJOR_VERSION.$GSTREAMERMM_MINOR_VERSION
AC_DEFINE_UNQUOTED(GSTREAMERMM_MAJOR_VERSION, $GSTREAMERMM_MAJOR_VERSION, [Major version of gstreamermm])
AC_DEFINE_UNQUOTED(GSTREAMERMM_MINOR_VERSION, $GSTREAMERMM_MINOR_VERSION, [Minor version of gstreamermm])
AC_DEFINE_UNQUOTED(GSTREAMERMM_MICRO_VERSION, $GSTREAMERMM_MICRO_VERSION, [Micro version of gstreamermm])
AC_SUBST(GSTREAMERMM_MAJOR_VERSION)
AC_SUBST(GSTREAMERMM_MINOR_VERSION)
AC_SUBST(GSTREAMERMM_MICRO_VERSION)
AC_SUBST(GSTREAMERMM_VERSION)
AC_SUBST(GSTREAMERMM_RELEASE)

#
# +1 : ? : +1  == new interface that does not break old one
# +1 : ? : 0   == new interface that breaks old one
#  ? : ? : 0   == no new interfaces, but breaks apps
#  ? :+1 : ?   == just some internal changes, nothing breaks but might work 
#                 better
# CURRENT : REVISION : AGE
LIBGSTREAMERMM_SO_VERSION=2:1:0
AC_SUBST(LIBGSTREAMERMM_SO_VERSION)

AC_CONFIG_AUX_DIR(scripts)

# Initialize automake stuff
# tar-ustar asks it to use a sensible tar format that can handle long filenames.
AM_INIT_AUTOMAKE([1.9 tar-ustar])

dnl Specify a configuration file (no autoheader)
AM_CONFIG_HEADER(config.h gstreamer/gstreamermmconfig.h)
AM_MAINTAINER_MODE
AL_ACLOCAL_INCLUDE(scripts)


#########################################################################
#  Configure arguments 
#########################################################################

#########################################################################
#  Environment Checks
#########################################################################
AC_PROG_CC
AC_PROG_CPP
AC_PROG_MAKE_SET
AC_CANONICAL_BUILD
AC_CANONICAL_HOST

dnl Used for enabling the "-no-undefined" flag while generating DLLs
dnl Copied from the official gtk+-2 configure.in
AC_MSG_CHECKING([for some Win32 platform])
case "$host" in
  *-*-mingw*|*-*-cygwin*)
    platform_win32=yes
    ;;
  *)
    platform_win32=no
    ;;
esac
AC_MSG_RESULT([$platform_win32])
AM_CONDITIONAL(PLATFORM_WIN32, test "$platform_win32" = "yes")

AC_MSG_CHECKING([for native Win32])
case "$host" in
  *-*-mingw*)
    os_win32=yes
    ;;
  *)
    os_win32=no
    ;;
esac
AC_MSG_RESULT([$os_win32])
AM_CONDITIONAL(OS_WIN32, test "$os_win32" = "yes")

AC_DISABLE_STATIC
AC_LIBTOOL_WIN32_DLL
AC_PROG_LIBTOOL

AL_PROG_GNU_M4(AC_MSG_ERROR([dnl
SUN m4 does not work for building gstreamermm. 
Please install GNU m4.]))

AL_PROG_GNU_MAKE(AC_MSG_ERROR([dnl
SUN make does not work for building gstreamermm.
Please install GNU make.]))


#########################################################################
#  Dependancy checks (gtkmm is only used by examples)
#########################################################################
gstreamermm_min_glibmm_version=2.16.0
gstreamermm_min_gtkmm_version=2.12.0
gstreamermm_min_gst_version=0.10.22
gstreamermm_min_libxmlpp_version=2.14.0

PKG_CHECK_MODULES(GSTREAMERMM, \
        glibmm-2.4 >= ${gstreamermm_min_glibmm_version} \
        giomm-2.4 >= ${gstreamermm_min_glibmm_version} \
        libxml++-2.6 >= ${gstreamermm_min_libxmlpp_version} \
        gstreamer-0.10 >= ${gstreamermm_min_gst_version} \
        gstreamer-base-0.10 >= ${gstreamermm_min_gst_version} \
        gstreamer-controller-0.10 >= ${gstreamermm_min_gst_version} \
        gstreamer-dataprotocol-0.10 >= ${gstreamermm_min_gst_version} \
        gstreamer-net-0.10 >= ${gstreamermm_min_gst_version} \
        gstreamer-plugins-base-0.10 >= ${gstreamermm_min_gst_version} \
        gstreamer-audio-0.10 >= ${gstreamermm_min_gst_version} \
        gstreamer-cdda-0.10 >= ${gstreamermm_min_gst_version} \
        gstreamer-interfaces-0.10 >= ${gstreamermm_min_gst_version} \
        gstreamer-netbuffer-0.10 >= ${gstreamermm_min_gst_version} \
        gstreamer-rtp-0.10 >= ${gstreamermm_min_gst_version} \
        gstreamer-video-0.10 >= ${gstreamermm_min_gst_version} \
        )
AC_SUBST(GSTREAMERMM_CFLAGS)
AC_SUBST(GSTREAMERMM_LIBS)

# This macro is installed by glibmm
# Doxygen needs the path to the installed perl.
GLIBMM_CHECK_PERL([5.6.0])

GLIBMM_LIBDIR=`pkg-config --variable=libdir glibmm-2.4`
GMMPROC_DIR=$GLIBMM_LIBDIR/glibmm-2.4/proc
AC_SUBST(GMMPROC_DIR)
GMMPROC=$GMMPROC_DIR/gmmproc
AC_SUBST(GMMPROC)


#########################################################################
#  Plug-in processing
#########################################################################

# make sure grep and head are available:
AC_PROG_GREP()
AC_PATH_PROG([HEAD], [head])

# make sure gst-inspect is available:
AC_PATH_PROG([GST_INSPECT], [gst-inspect])
if test x$GST_INSPECT = x ; then
  AC_MSG_ERROR([gst-inspect is needed for plug-in processing. Please, install it.])
fi
AC_ARG_VAR([GST_INSPECT], [Variable to store gst-inspect executable])
AC_SUBST(GST_INSPECT)

# To add a plugin, add the plugin definition, in the form of
# "plugin=CppClassName" (where "plugin" is the plugin name as recognized by
# gst-inspect and "CppClassName" is the desired name of the C++ class),  to the
# list of definitions below.  Also add the target .hg file name (which must be
# the same as "CppClassName" all in lowercase with a .hg extension) to the
# files_all_plugin_hg variable in the
# gstreamer/src/Makefile_list_of_hg.am_fragment file.  Finally, be sure to
# include an #undef in the form of "#undef GSTREAMERMM_PLUGIN_name" in the
# gstreamermmconfig.h.in file (where "name" is the plugin name all in caps).

GSTREAMERMM_ALL_PLUGIN_DEFS="capsfilter=CapsFilter fakesrc=FakeSrc \
fakesink=FakeSink fdsink=FdSink fdsrc=FdSrc filesrc=FileSrc filesink=FileSink \
identity=Identity multiqueue=MultiQueue queue=Queue tee=Tee \
typefind=TypeFindElement adder=Adder alsamixer=AlsaMixer alsasink=AlsaSink \
alsasrc=AlsaSrc audioconvert=AudioConvert audioresample=AudioResample \
audiotestsrc=AudioTestSrc cdparanoiasrc=CdParanoiaSrc \
clockoverlay=ClockOverlay decodebin=DecodeBin \
ffmpegcolorspace=FfmpegColorSpace gdpdepay=GDPDepay gdppay=GDPPay \
giosink=GioSink giosrc=GioSrc giostreamsink=GioStreamSink \
giostreamsrc=GioStreamSrc oggdemux=OggDemux oggmux=OggMux playbin2=PlayBin2 \
textoverlay=TextOverlay textrender=TextRender theoradec=TheoraDec \
theoraenc=TheoraEnc timeoverlay=TimeOverlay videorate=VideoRate \
videoscale=VideoScale videotestsrc=VideoTestSrc volume=Volume \
vorbisdec=VorbisDec vorbisenc=VorbisEnc vorbisparse=VorbisParse \
vorbistag=VorbisTag ximagesink=XImageSink xvimagesink=XvImageSink"

# TODO: The following plug-ins (to be added above) can't be wrapped yet because
# their signals or properties use the GValueArray type which might have to be
# wrapped in glibmm first: DecodeBin2, MultiFdSink, PlayBin, TcpServerSink,
# TheoraParse, UriDecodeBin.

for plugin_def in $GSTREAMERMM_ALL_PLUGIN_DEFS; do
  plugin_name=[`echo $plugin_def | cut -d'=' -f 1`]
  cppname=[`echo $plugin_def | cut -d'=' -f 2`]
  GSTREAMERMM_ALL_PLUGIN_CPPNAMES="$GSTREAMERMM_ALL_PLUGIN_CPPNAMES $cppname"
  if test -z "`$GST_INSPECT $plugin_name | $HEAD -n 1 | $GREP "No such element"`"; then
    plugin_define=["GSTREAMERMM_PLUGIN_`echo $plugin_name | tr [:lower:] [:upper:]`"]
    AC_DEFINE_UNQUOTED($plugin_define)
    GSTREAMERMM_EXISTING_PLUGIN_CPPNAMES="$GSTREAMERMM_EXISTING_PLUGIN_CPPNAMES $cppname"
    GSTREAMERMM_EXISTING_PLUGIN_HG=["$GSTREAMERMM_EXISTING_PLUGIN_HG `echo $cppname | tr [:upper:] [:lower:]`.hg"]
  fi
done
AC_SUBST(GSTREAMERMM_ALL_PLUGIN_DEFS)
AC_SUBST(GSTREAMERMM_ALL_PLUGIN_CPPNAMES)
AC_SUBST(GSTREAMERMM_EXISTING_PLUGIN_CPPNAMES)
AC_SUBST(GSTREAMERMM_EXISTING_PLUGIN_HG)

#########################################################################
#  C++ checks
#########################################################################
AC_PROG_CXX

# Check for the SUN Forte compiler, and define GLIBMM_COMPILER_SUN_FORTE in the header.
#GLIBMM_PROG_CXX_SUN

# Ensure MSVC-compatible struct packing convention is used when
# compiling for Win32 with gcc.
# What flag to depends on gcc version: gcc3 uses "-mms-bitfields", while
# gcc2 uses "-fnative-struct".
if test x"$os_win32" = xyes; then
  if test x"$GCC" = xyes -a x"$GXX" = xyes; then
    msnative_struct=''
    AC_MSG_CHECKING([how to get MSVC-compatible struct packing])
    if test -z "$ac_cv_prog_CC"; then
      our_gcc="$CC"
    else
      our_gcc="$ac_cv_prog_CC"
    fi
    case `$our_gcc --version | sed -e 's,\..*,.,' -e q` in
      2.)
	if $our_gcc -v --help 2>/dev/null | grep fnative-struct >/dev/null; then
	  msnative_struct='-fnative-struct'
	fi
	;;
      *)
	if $our_gcc -v --help 2>/dev/null | grep ms-bitfields >/dev/null; then
	  msnative_struct='-mms-bitfields'
	fi
	;;
    esac
    if test x"$msnative_struct" = x ; then
      AC_MSG_RESULT([no way])
      AC_MSG_WARN([produced libraries might be incompatible with MSVC-compiled code])
    else
      CXXFLAGS="$CXXFLAGS $msnative_struct"
      AC_MSG_RESULT([${msnative_struct}])
    fi
  fi
fi

AC_LANG_CPLUSPLUS


# Create a list of input directories for Doxygen.
#GSTREAMERMM_DOXYGEN_INPUT_SUBDIRS([gst])

# Evaluate the --enable-warnings=level option.
#GSTREAMERMM_ARG_ENABLE_WARNINGS()
DK_ARG_ENABLE_WARNINGS([GSTREAMERMM_WARNING_FLAGS],
    [-Wall],
    [-pedantic -Wall -Wextra])

# Add an --enable-use-deprecations configure option:
AC_ARG_ENABLE(deprecations,
              [AC_HELP_STRING([--enable-use-deprecations],
                              [warn about deprecated usages [default=no]])],,
              [enable_deprecations=no])

if test "x$enable_use_deprecations" = "xyes"; then
   DISABLE_DEPRECATED_CFLAGS="\
-DG_DISABLE_DEPRECATED \
-DGDK_DISABLE_DEPRECATED \
-DGTK_DISABLE_DEPRECATED \
-DGDK_PIXBUF_DISABLE_DEPRECATED"
   AC_SUBST(DISABLE_DEPRECATED_CFLAGS)
fi

# Add an --enable-deprecated-api option:
AC_ARG_ENABLE(deprecated-api, [AC_HELP_STRING([--enable-deprecated-api],
                                        [include (build) deprecated API in the libraries [default=yes]])],,
                        [enable_deprecated_api=yes])
if test "x$enable_deprecated_api" = "xyes"; then
AC_MSG_WARN([Deprecated API will be built, for backwards-compatibility.])
else
  DISABLE_DEPRECATED_API_CFLAGS=""
AC_SUBST(DISABLE_DEPRECATED_API_CFLAGS)
AC_MSG_WARN([Deprecated API will not be built, breaking backwards-compatibility. Do not use this build for distribution packages.])
fi

AC_ARG_ENABLE(examples,
  [AC_HELP_STRING([--enable-examples],
    [enable compilation of example programs [default=yes]])],
  [enable_examples=$enableval], [enable_examples=yes])

if test "x$enable_examples" = "xyes"; then

#Extra dependencies needed for the examples. Use --enable-examples=no to build the library without this.
PKG_CHECK_MODULES(GSTREAMERMM_EXAMPLES, gtkmm-2.4 >= ${gstreamermm_min_gtkmm_version})
AC_SUBST(GSTREAMERMM_EXAMPLES_CFLAGS)
AC_SUBST(GSTREAMERMM_EXAMPLES_LIBS)

EXAMPLE_SUBDIR="examples"
AC_CONFIG_FILES([
    examples/Makefile
    examples/optiongroup/Makefile
    examples/element_link/Makefile
    examples/ogg_player/Makefile
    examples/ogg_player_gtkmm/Makefile
    examples/media_player_gtkmm/Makefile
    ])
AC_SUBST(EXAMPLE_SUBDIR)
else
EXAMPLE_SUBDIR=""
fi

DEMO_SUBDIR=""
AC_SUBST(DEMO_SUBDIR)

AC_ARG_ENABLE(debug, [AC_HELP_STRING([--enable-debug],
                                     [compile with debugging options [default=no]])],
              enable_debug=$enableval,
              [enable_debug=no])

AC_MSG_NOTICE([got enable_debug=$enable_debug])
if test x$GSVMM_DEVEL = xon ; then
    enable_debug=yes
fi

if test x$enable_debug = xyes ; then
    DEBUG_OPTIONS="-Wall -g -Werror -Wextra"
    CXXFLAGS="$DEBUG_OPTIONS"
    CFLAGS="$DEBUG_OPTIONS"
fi

# Create a list of input directories for Doxygen.  We have to check wether
# we are building in the source directory, because Doxygen doesn't like
# duplicated directories in the input list.
GSTREAMERMM_DOXYGEN_INPUT=''
gstmm_srcdir=`cd "$srcdir" && pwd`
gstmm_builddir=`pwd`
for sublib in gstreamer
do
  if test "x$gstmm_builddir"  = "x$gstmm_srcdir" ; then
    GSTREAMERMM_DOXYGEN_INPUT="$GSTREAMERMM_DOXYGEN_INPUT $gstmm_builddir/$sublib/$sublib""mm/"
  else
    GSTREAMERMM_DOXYGEN_INPUT="$GSTREAMERMM_DOXYGEN_INPUT $gstmm_srcdir/$sublib/$sublib""mm/"
  fi
done
AC_SUBST(GSTREAMERMM_DOXYGEN_INPUT)

AC_ARG_ENABLE(docs, [AC_HELP_STRING([--enable-docs],
              [build the included docs [default=yes]])],,
                      [enable_docs=yes])
if test "x$enable_docs" = "xyes"; then
AC_PATH_PROG(DOXYGEN, doxygen)
    if test x$DOXYGEN = x ; then
        AC_MSG_ERROR([could not find the doxygen program. Please, install it])
    fi
AC_SUBST(DOXYGEN)
DOCS_SUBDIR="docs"
  AC_CONFIG_FILES([
    docs/Makefile
      docs/reference/Makefile
      docs/reference/Doxyfile
  ])
else
DOCS_SUBDIR=""
fi

AC_SUBST(DOCS_SUBDIR)

# Dummy conditional just to make automake-1.4 happy.
# We need an always-false condition in docs/Makefile.am.
AM_CONDITIONAL(GSTREAMERMM_FALSE,[false])

# HACK:  Assign a dummy in order to prevent execution of autoheader by the
# maintainer-mode rules.  That would fail since we aren't using autoheader.
AUTOHEADER=':'


AC_CONFIG_FILES([
  Makefile

  gstreamer/Makefile
  gstreamer/gstreamermm-0.10.pc
    gstreamer/src/Makefile
    gstreamer/gstreamermm/Makefile
      gstreamer/gstreamermm/private/Makefile

  tools/Makefile
    tools/generate_wrap_init.pl
    tools/generate_gst_wrap_init.pl
    tools/m4/Makefile
    tools/extra_defs_gen/Makefile

  tests/Makefile
])

AC_CONFIG_FILES([
  scripts/Makefile
])

AC_OUTPUT()


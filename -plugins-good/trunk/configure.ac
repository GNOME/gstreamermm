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
pushdef([GSTREAMERMM_PLUGINS_GOOD_MAJOR_VERSION],     [0])
pushdef([GSTREAMERMM_PLUGINS_GOOD_MINOR_VERSION],     [10])
pushdef([GSTREAMERMM_PLUGINS_GOOD_MICRO_VERSION],     [1])
pushdef([GSTREAMERMM_PLUGINS_GOOD_EXTRA_VERSION],     [])
pushdef([GSTREAMERMM_PLUGINS_GOOD_VERSION], GSTREAMERMM_PLUGINS_GOOD_MAJOR_VERSION.GSTREAMERMM_PLUGINS_GOOD_MINOR_VERSION.GSTREAMERMM_PLUGINS_GOOD_MICRO_VERSION[]GSTREAMERMM_PLUGINS_GOOD_EXTRA_VERSION)
AC_INIT([gstreamermm-plugins-good], GSTREAMERMM_PLUGINS_GOOD_VERSION, [gtkmm-list@gnome.org])
AC_CONFIG_SRCDIR([gstreamer-plugins-good/gstreamermm-plugins-good-config.h.in])
AC_PREREQ(2.59)

#########################################################################
#  Version and initialization
#########################################################################
[GSTREAMERMM_PLUGINS_GOOD_MAJOR_VERSION]=GSTREAMERMM_PLUGINS_GOOD_MAJOR_VERSION
[GSTREAMERMM_PLUGINS_GOOD_MINOR_VERSION]=GSTREAMERMM_PLUGINS_GOOD_MINOR_VERSION
[GSTREAMERMM_PLUGINS_GOOD_MICRO_VERSION]=GSTREAMERMM_PLUGINS_GOOD_MICRO_VERSION
[GSTREAMERMM_PLUGINS_GOOD_EXTRA_VERSION]=GSTREAMERMM_PLUGINS_GOOD_EXTRA_VERSION
[GSTREAMERMM_PLUGINS_GOOD_VERSION]=GSTREAMERMM_PLUGINS_GOOD_VERSION
popdef([GSTREAMERMM_PLUGINS_GOOD_MAJOR_VERSION])
popdef([GSTREAMERMM_PLUGINS_GOOD_MINOR_VERSION])
popdef([GSTREAMERMM_PLUGINS_GOOD_MICRO_VERSION])
popdef([GSTREAMERMM_PLUGINS_GOOD_EXTRA_VERSION])
popdef([GSTREAMERMM_PLUGINS_GOOD_VERSION])
GSTREAMERMM_PLUGINS_GOOD_RELEASE=$GSTREAMERMM_PLUGINS_GOOD_MAJOR_VERSION.$GSTREAMERMM_PLUGINS_GOOD_MINOR_VERSION
AC_DEFINE_UNQUOTED(GSTREAMERMM_PLUGINS_GOOD_MAJOR_VERSION, $GSTREAMERMM_PLUGINS_GOOD_MAJOR_VERSION, [Major version of gstreamermm-plugins-good])
AC_DEFINE_UNQUOTED(GSTREAMERMM_PLUGINS_GOOD_MINOR_VERSION, $GSTREAMERMM_PLUGINS_GOOD_MINOR_VERSION, [Minor version of gstreamermm-plugins-good])
AC_DEFINE_UNQUOTED(GSTREAMERMM_PLUGINS_GOOD_MICRO_VERSION, $GSTREAMERMM_PLUGINS_GOOD_MICRO_VERSION, [Micro version of gstreamermm-plugins-good])
AC_SUBST(GSTREAMERMM_PLUGINS_GOOD_MAJOR_VERSION)
AC_SUBST(GSTREAMERMM_PLUGINS_GOOD_MINOR_VERSION)
AC_SUBST(GSTREAMERMM_PLUGINS_GOOD_MICRO_VERSION)
AC_SUBST(GSTREAMERMM_PLUGINS_GOOD_VERSION)
AC_SUBST(GSTREAMERMM_PLUGINS_GOOD_RELEASE)

#
# +1 : ? : +1  == new interface that does not break old one
# +1 : ? : 0   == new interface that breaks old one
#  ? : ? : 0   == no new interfaces, but breaks apps
#  ? :+1 : ?   == just some internal changes, nothing breaks but might work 
#                 better
# CURRENT : REVISION : AGE
LIBGSTREAMERMM_PLUGINS_GOOD_SO_VERSION=2:1:0
AC_SUBST(LIBGSTREAMERMM_PLUGINS_GOOD_SO_VERSION)

AC_CONFIG_AUX_DIR(scripts)

# Initialize automake stuff
# tar-ustar asks it to use a sensible tar format that can handle long filenames.
AM_INIT_AUTOMAKE([1.9 tar-ustar])

dnl Specify a configuration file (no autoheader)
AM_CONFIG_HEADER(config.h gstreamer-plugins-good/gstreamermm-plugins-good-config.h)
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
SUN m4 does not work for building gstreamermm-plugins-good. 
Please install GNU m4.]))

AL_PROG_GNU_MAKE(AC_MSG_ERROR([dnl
SUN make does not work for building gstreamermm-plugins-good.
Please install GNU make.]))


#########################################################################
#  Dependancy checks
#########################################################################
min_gstreamer_version=0.10.22
min_gstreamermm_version=0.10.1

PKG_CHECK_MODULES(GSTREAMERMM_PLUGINS_GOOD, \
AC_SUBST(GSTREAMERMM_PLUGINS_GOOD_VERSION)
        gstreamer-0.10 >= ${min_gstreamer_version} \
        gstreamermm-0.10 >= ${min_gstreamermm_version} \
        )
AC_SUBST(GSTREAMERMM_PLUGINS_GOOD_CFLAGS)
AC_SUBST(GSTREAMERMM_PLUGINS_GOOD_LIBS)

# This macro is installed by glibmm
# Doxygen needs the path to the installed perl.
GLIBMM_CHECK_PERL([5.6.0])

GLIBMM_LIBDIR=`pkg-config --variable=libdir glibmm-2.4`
GMMPROC_DIR=$GLIBMM_LIBDIR/glibmm-2.4/proc
AC_SUBST(GMMPROC_DIR)
GMMPROC=$GMMPROC_DIR/gmmproc
AC_SUBST(GMMPROC)

GSTREAMERMM_LIBDIR=`pkg-config --variable=libdir gstreamermm-0.10`
GENERATE_PLUGIN_GMMPROC_FILE_DIR=$GSTREAMERMM_LIBDIR/gstreamermm-0.10/gen
GENERATE_PLUGIN_GMMPROC_FILE=$GENERATE_PLUGIN_GMMPROC_FILE_DIR/generate_plugin_gmmproc_file
AC_SUBST(GENERATE_PLUGIN_GMMPROC_FILE)

GSTREAMERMM_M4_DIR=$GSTREAMERMM_LIBDIR/gstreamermm-0.10/proc/m4
AC_SUBST(GSTREAMERMM_M4_DIR)


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
# space separated list of definitions below.  Also add the target .hg file name
# (which must be the same as "CppClassName" all in lowercase with a .hg
# extension) to the files_all_plugin_hg variable in the
# gstreamer-plugins-good/src/Makefile_list_of_hg.am_fragment file.  Finally, be
# sure to include an #undef in the form of "#undef
# GSTREAMERMM_PLUGINS_GOOD_PLUGIN_name" in the
# gstreamermm-plugins-good-config.h.in file (where "name" is the plugin name
# all in caps).

GSTREAMERMM_PLUGINS_GOOD_ALL_PLUGIN_DEFS="alphacolor=AlphaColor \
apedemux=ApeDemux videoflip=VideoFlip"

for plugin_def in $GSTREAMERMM_PLUGINS_GOOD_ALL_PLUGIN_DEFS; do
  plugin_name=[`echo $plugin_def | cut -d'=' -f 1`]
  cppname=[`echo $plugin_def | cut -d'=' -f 2`]
  GSTREAMERMM_PLUGINS_GOOD_ALL_PLUGIN_CPPNAMES="$GSTREAMERMM_PLUGINS_GOOD_ALL_PLUGIN_CPPNAMES $cppname"
  if test -z "`$GST_INSPECT $plugin_name | $HEAD -n 1 | $GREP "No such element"`"; then
    plugin_define=["GSTREAMERMM_PLUGINS_GOOD_PLUGIN_`echo $plugin_name | tr [:lower:] [:upper:]`"]
    AC_DEFINE_UNQUOTED($plugin_define)
    GSTREAMERMM_PLUGINS_GOOD_EXISTING_PLUGIN_CPPNAMES="$GSTREAMERMM_PLUGINS_GOOD_EXISTING_PLUGIN_CPPNAMES $cppname"
    GSTREAMERMM_PLUGINS_GOOD_EXISTING_PLUGIN_HG=["$GSTREAMERMM_PLUGINS_GOOD_EXISTING_PLUGIN_HG `echo $cppname | tr [:upper:] [:lower:]`.hg"]
  fi
done
AC_SUBST(GSTREAMERMM_PLUGINS_GOOD_ALL_PLUGIN_DEFS)
AC_SUBST(GSTREAMERMM_PLUGINS_GOOD_ALL_PLUGIN_CPPNAMES)
AC_SUBST(GSTREAMERMM_PLUGINS_GOOD_EXISTING_PLUGIN_CPPNAMES)
AC_SUBST(GSTREAMERMM_PLUGINS_GOOD_EXISTING_PLUGIN_HG)

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
#GSTREAMERMM_PLUGINS_GOOD_DOXYGEN_INPUT_SUBDIRS([gst])

# Evaluate the --enable-warnings=level option.
#GSTREAMERMM_PLUGINS_GOOD_ARG_ENABLE_WARNINGS()
DK_ARG_ENABLE_WARNINGS([GSTREAMERMM_PLUGINS_GOOD_WARNING_FLAGS],
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

EXAMPLE_SUBDIR="examples"
AC_CONFIG_FILES([
    examples/Makefile
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
AM_CONDITIONAL(GSTREAMERMM_PLUGINS_GOOD_FALSE,[false])

# HACK:  Assign a dummy in order to prevent execution of autoheader by the
# maintainer-mode rules.  That would fail since we aren't using autoheader.
AUTOHEADER=':'


AC_CONFIG_FILES([
  Makefile

  gstreamer-plugins-good/Makefile
  gstreamer-plugins-good/gstreamermm-plugins-good-0.10.pc
    gstreamer-plugins-good/src/Makefile
    gstreamer-plugins-good/gstreamermm-plugins-good/Makefile
      gstreamer-plugins-good/gstreamermm-plugins-good/private/Makefile

  tools/Makefile
    tools/generate_wrap_init.pl
    tools/m4/Makefile
    tools/extra_defs_gen/Makefile

  tests/Makefile
])

AC_CONFIG_FILES([
  scripts/Makefile
])

AC_OUTPUT()


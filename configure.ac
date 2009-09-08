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

AC_LANG([C++])
MM_ARG_ENABLE_WARNINGS([GSTREAMERMM_WXXFLAGS],
                       [-Wall],
                       [-pedantic -Wall -Wextra],
                       [G GSTREAMER])

AC_CONFIG_FILES([Makefile
                 tools/Makefile
                 tools/generate_gst_wrap_init.pl
                 gstreamer/${GSTREAMERMM_MODULE_NAME}.pc:gstreamer/gstreamermm.pc.in
                 gstreamer/${GSTREAMERMM_MODULE_NAME}-uninstalled.pc:gstreamer/gstreamermm-uninstalled.pc.in
                 gstreamer/src/Makefile
                 gstreamer/gstreamermm/Makefile
                 doc/Makefile
                 doc/reference/Doxyfile])
AC_OUTPUT

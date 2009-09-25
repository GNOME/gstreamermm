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

ACLOCAL_AMFLAGS = -I build ${ACLOCAL_FLAGS}
# TODO: Fix warnings and switch back to fatal warnings mode.
DISTCHECK_CONFIGURE_FLAGS = --enable-warnings=max

if MAINTAINER_MODE
src_subdirs = gstreamer/src
else
src_subdirs =
endif
if ENABLE_DOCUMENTATION
doc_subdirs = docs
else
doc_subdirs =
endif
SUBDIRS = tools $(src_subdirs) gstreamer/gstreamermm tests examples $(doc_subdirs)

gstreamermm_includedir = $(includedir)/$(GSTREAMERMM_MODULE_NAME)
gstreamermm_include_HEADERS = gstreamer/gstreamermm.h
gstreamermm_libincludedir = $(libdir)/$(GSTREAMERMM_MODULE_NAME)/include
nodist_gstreamermm_libinclude_HEADERS = gstreamer/gstreamermmconfig.h

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = gstreamer/$(GSTREAMERMM_MODULE_NAME).pc

dist_noinst_SCRIPTS = autogen.sh

#include $(top_srcdir)/build/dist-changelog.am

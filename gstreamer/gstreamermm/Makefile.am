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

lib_LTLIBRARIES = libgstreamermm-@GSTREAMERMM_API_VERSION@.la
include $(srcdir)/../src/plugin_filelist.am
include $(srcdir)/../src/filelist.am
include $(srcdir)/filelist.am
include $(top_srcdir)/build/compile-binding.am

local_cppflags = $(binding_includes) $(binding_cppflags) -DGSTREAMERMM_BUILD=1

AM_CPPFLAGS = $(local_cppflags) $(GSTREAMERMM_CFLAGS)
AM_CXXFLAGS = $(GSTREAMERMM_WXXFLAGS)

libgstreamermm_@GSTREAMERMM_API_VERSION@_la_SOURCES = $(binding_sources)
libgstreamermm_@GSTREAMERMM_API_VERSION@_la_LDFLAGS = -no-undefined -version-info $(GSTREAMERMM_SO_VERSION)
libgstreamermm_@GSTREAMERMM_API_VERSION@_la_LIBADD  = $(GSTREAMERMM_LIBS)

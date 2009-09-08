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

AUTOMAKE_OPTIONS = subdir-objects

include $(srcdir)/m4/filelist.am

lib_LTLIBRARIES	= extra_defs_gen/libgstreamermm_get_plugin_defs-0.10.la
extra_defs_gen_libgstreamermm_get_plugin_defs_0_10_la_SOURCES = \
			extra_defs_gen/get_plugin_defs.cc
extra_defs_gen_libgstreamermm_get_plugin_defs_0_10_la_LIBADD = \
			$(GSTREAMERMM_LIBS) -lglibmm_generate_extra_defs-2.4

defs_includedir   = $(includedir)/gstreamermm-0.10/gstreamermm_get_plugin_defs
defs_include_HEADERS = extra_defs_gen/get_plugin_defs.h
defs_ldflags 	  = $(no_undefined) -version-info $(LIBGSTREAMERMM_SO_VERSION)

#TODO: Should these go into $(datadir)/$(PACKAGE_TARNAME)/ instead as in gtkmm?
plugingen_bindir = $(libdir)/$(GSTREAMERMM_MODULE_NAME)/gen
plugingen_m4dir  = $(plugingen_bindir)/m4
dist_plugingen_m4_DATA = $(files_codegen_m4:%=m4/%) $(files_plugin_m4:%=m4/%)

noinst_PROGRAMS = extra_defs_gen/generate_defs_gst

extra_defs_gen_generate_defs_gst_SOURCES = extra_defs_gen/generate_defs_gst.cc
extra_defs_gen_generate_defs_gst_LDADD   = $(GSTREAMERMM_LIBS) \
			-lglibmm_generate_extra_defs-2.4 \
			extra_defs_gen/libgstreamermm_get_plugin_defs-0.10.la

# Build and install the generate_plugin_gmmproc_file utility executable so that
# other gstreamermm modules can also generate plug-ins.

extra_defs_gen_generate_plugin_gmmproc_file_SOURCES = \
			extra_defs_gen/generate_plugin_gmmproc_file.cc
extra_defs_gen_generate_plugin_gmmproc_file_LDADD = \
			extra_defs_gen/libgstreamermm_get_plugin_defs-0.10.la
extra_defs_gen_generate_plugin_gmmproc_file_PROGRAMS = \
			extra_defs_gen/generate_plugin_gmmproc_file
extra_defs_gen_generate_plugin_gmmproc_filedir = $(plugingen_bindir)

AM_CPPFLAGS = -I$(top_builddir) $(GTHREAD_CFLAGS) $(GSTREAMERMM_CFLAGS)
AM_CXXFLAGS = $(GSTREAMERMM_WXXFLAGS)

# Instruct GNU make to delete the targets of a rule after it failed, in
# order to avoid the complication of handling that situation manually.
.DELETE_ON_ERROR:

## Copyright (c) 2009
## The gstreamermm development team.

SUBDIRS                 = private

sublib_name             = gstreamermm-plugins-good
sublib_libname          = gstreamermm-plugins-good-0.10
sublib_libversion       = $(LIBGSTREAMERMM_PLUGINS_GOOD_SO_VERSION)
sublib_namespace        = Gst
sublib_cflags           = $(GSTREAMERMM_PLUGINS_GOOD_CFLAGS)
sublib_topdir           = gstreamer-plugins-good
sublib_win32_dlls_libs	=

sublib_files_extra_posix_cc = 
sublib_files_extra_win32_cc =
sublib_files_extra_general_cc = init.cc
sublib_files_extra_general_deprecated_cc = 

sublib_files_extra_posix_h = 
sublib_files_extra_win32_h =
sublib_files_extra_general_h = init.h
sublib_files_extra_general_deprecated_h = 

include $(top_srcdir)/build_shared/Makefile_build.am_fragment

lib_LTLIBRARIES = libgstreamermm-plugins-good-0.10.la
libgstreamermm_plugins_good_0_10_la_SOURCES = $(files_built_cc) $(files_extra_cc)
EXTRA_libgstreamermm_plugins_good_0_10_la_SOURCES = $(files_all_plugin_built_cc)
libgstreamermm_plugins_good_0_10_la_LDFLAGS = $(common_ldflags)
libgstreamermm_plugins_good_0_10_la_LIBADD  = $(GSTREAMERMM_PLUGINS_GOOD_LIBS) \
				 $(files_existing_plugin_built_lo)
libgstreamermm_plugins_good_0_10_la_DEPENDENCIES = $(files_existing_plugin_built_lo)

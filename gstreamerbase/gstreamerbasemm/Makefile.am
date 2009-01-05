## Copyright (c) 2008
## The gstreamermm development team.

SUBDIRS                 = private

sublib_name             = gstreamerbasemm
sublib_libname          = gstreamerbasemm-0.10
sublib_libversion       = $(LIBGSTREAMERBASEMM_SO_VERSION)
sublib_namespace        = GstBase
sublib_cflags           = $(GSTREAMERBASEMM_CFLAGS)
sublib_topdir           = gstreamerbase
sublib_win32_dlls_libs	=

sublib_files_extra_posix_cc = 
sublib_files_extra_win32_cc =
sublib_files_extra_general_cc = init.cc gst_wrap_init.cc
sublib_files_extra_general_deprecated_cc = 

sublib_files_extra_posix_h = 
sublib_files_extra_win32_h =
sublib_files_extra_general_h = init.h gst_wrap_init.h
sublib_files_extra_general_deprecated_h = 

include $(top_srcdir)/build_shared/Makefile_build.am_fragment

lib_LTLIBRARIES = libgstreamerbasemm-0.10.la
libgstreamerbasemm_0_10_la_SOURCES = $(files_built_cc) $(files_extra_cc)
EXTRA_libgstreamerbasemm_0_10_la_SOURCES = $(files_all_plugin_built_cc)
libgstreamerbasemm_0_10_la_LDFLAGS = $(common_ldflags)
libgstreamerbasemm_0_10_la_LIBADD  = $(GSTREAMERBASEMM_LIBS) \
				     $(top_builddir)/gstreamer/gstreamermm/.libs/libgstreamermm-0.10.la \
				     $(files_existing_plugin_built_lo)
libgstreamerbasemm_0_10_la_DEPENDENCIES = $(files_existing_plugin_built_lo)

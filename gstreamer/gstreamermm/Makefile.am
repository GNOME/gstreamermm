## Copyright (c) 2001
## The gtkmm development team.

SUBDIRS                 = private

sublib_name             = gstreamermm
sublib_libname          = gstreamermm-0.10
sublib_libversion       = $(LIBGSTREAMERMM_SO_VERSION)
sublib_namespace        = Gst
sublib_cflags           = $(GSTREAMERMM_CFLAGS)
sublib_topdir           = gstreamer
sublib_win32_dlls_libs	=

sublib_files_extra_posix_cc = 
sublib_files_extra_win32_cc =
sublib_files_extra_general_cc = init.cc miniobject.cc object.cc version.cc wrap.cc gst_wrap_init.cc
sublib_files_extra_general_deprecated_cc = 

sublib_files_extra_posix_h = 
sublib_files_extra_win32_h =
sublib_files_extra_general_h = init.h miniobject.h object.h version.h wrap.h gst_wrap_init.h
sublib_files_extra_general_deprecated_h = 

include $(top_srcdir)/build_shared/Makefile_build.am_fragment

lib_LTLIBRARIES = libgstreamermm-0.10.la
libgstreamermm_0_10_la_SOURCES = $(files_built_cc) $(files_extra_cc)
nodist_libgstreamermm_0_10_la_SOURCES = $(files_plugin_built_cc)
libgstreamermm_0_10_la_LDFLAGS = $(common_ldflags)
libgstreamermm_0_10_la_LIBADD  = $(GSTREAMERMM_LIBS)

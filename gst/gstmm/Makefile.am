## Copyright (c) 2001
## The gtkmm development team.

SUBDIRS                 = private

sublib_name             = gstmm
sublib_libname          = gstmm-1.0
sublib_libversion       = $(LIBGSTMM_SO_VERSION)
sublib_namespace        = Gst
sublib_cflags           = $(GSTMM_CFLAGS)
sublib_topdir           = gst
sublib_win32_dlls_libs	=

sublib_files_extra_posix_cc = 
sublib_files_extra_win32_cc =
sublib_files_extra_general_cc =  init.cc miniobject.cc object.cc version.cc wrap.cc gst_wrap_init.cc
sublib_files_extra_general_deprecated_cc = 

sublib_files_extra_posix_h = 
sublib_files_extra_win32_h =
sublib_files_extra_general_h = init.h miniobject.h object.h version.h wrap.h gst_wrap_init.h
sublib_files_extra_general_deprecated_h = 

include $(top_srcdir)/build_shared/Makefile_build.am_fragment

lib_LTLIBRARIES	        = libgstmm-1.0.la
libgstmm_1_0_la_SOURCES = $(files_built_cc) $(files_extra_cc)
libgstmm_1_0_la_LDFLAGS = $(common_ldflags)
libgstmm_1_0_la_LIBADD  = $(GSTMM_LIBS)


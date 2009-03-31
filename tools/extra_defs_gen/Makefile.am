# Build the library, to be installed and used by other plug-in generating
# modules:

files_h = get_plugin_defs.h gst_type_is_a_pointer.h
files_cc = get_plugin_defs.cc gst_type_is_a_pointer.cc

if PLATFORM_WIN32
no_undefined = -no-undefined
else
no_undefined =
endif

lib_LTLIBRARIES		= libgstreamermm_get_plugin_defs-0.10.la
libgstreamermm_get_plugin_defs_0_10_la_SOURCES = $(files_h) $(files_cc)
libgstreamermm_get_plugin_defs_0_10_la_LDFLAGS = $(no_undefined) -version-info \
						 $(LIBGSTREAMERMM_SO_VERSION)
libgstreamermm_get_plugin_defs_0_10_la_LIBADD = $(GSTREAMERMM_LIBS)

sublib_includedir = $(includedir)/gstreamermm-0.10/gstreamermm_get_plugin_defs
sublib_include_HEADERS	= $(files_h)

# Build the generate_defs_gst utility executable.
# This is not used to build the rest of gstreamermm.

INCLUDES = $(GSTREAMERMM_CFLAGS)
LIBS = $(GSTREAMERMM_LIBS) -lglibmm_generate_extra_defs-2.4

noinst_PROGRAMS = generate_defs_gst

generate_defs_gst_SOURCES = generate_defs_gst.cc
generate_defs_gst_LDADD = libgstreamermm_get_plugin_defs-0.10.la

# Build and install the generate_plugin_gmmproc_file utility executable so that
# other gstreamermm modules can also generate plug-ins.

generate_plugin_gmmproc_file_PROGRAMS = generate_plugin_gmmproc_file
generate_plugin_gmmproc_file_SOURCES = generate_plugin_gmmproc_file.cc
generate_plugin_gmmproc_file_LDADD = libgstreamermm_get_plugin_defs-0.10.la
generate_plugin_gmmproc_filedir = $(GENERATE_PLUGIN_GMMPROC_FILE_DIR)

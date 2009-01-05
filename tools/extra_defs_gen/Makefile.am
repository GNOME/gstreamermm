# Build the generate_properties_defs utility executable.
# This is not used to build the rest of gtkmm.

INCLUDES = $(GSTREAMERMM_CFLAGS)
LIBS = $(GSTREAMERMM_LIBS) -lglibmm_generate_extra_defs-2.4

EXTRA_DIST = get_plugin_defs.h get_plugin_defs.cc gst_type_is_a_pointer.h \
	     gst_type_is_a_pointer.cc

noinst_PROGRAMS = generate_defs_gst generate_plugin_gmmproc_file

generate_defs_gst_SOURCES = generate_defs_gst.cc get_plugin_defs.cc

generate_plugin_gmmproc_file_SOURCES = generate_plugin_gmmproc_file.cc \
				       gst_type_is_a_pointer.cc

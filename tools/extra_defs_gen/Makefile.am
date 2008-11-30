# Build the generate_properties_defs utility executable.
# This is not used to build the rest of gtkmm.

INCLUDES = $(GSTREAMERMM_CFLAGS) $(GSTREAMERBASEMM_CFLAGS)
LIBS = $(GSTREAMERMM_LIBS) $(GSTREAMERBASEMM_LIBS) -lglibmm_generate_extra_defs-2.4

EXTRA_DIST = get_plugin_defs.h get_plugin_defs.cc

noinst_PROGRAMS = generate_defs_gst generate_defs_gstbase \
		  generate_plugin_gmmproc_file

generate_defs_gst_SOURCES = generate_defs_gst.cc get_plugin_defs.cc
generate_defs_gstbase_SOURCES = generate_defs_gstbase.cc get_plugin_defs.cc

generate_plugin_gmmproc_file_SOURCES = generate_plugin_gmmproc_file.cc

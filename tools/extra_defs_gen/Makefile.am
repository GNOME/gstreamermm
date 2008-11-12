# Build the generate_properties_defs utility executable.
# This is not used to build the rest of gtkmm.

INCLUDES = $(GSTREAMERMM_CFLAGS) $(GSTREAMERBASEMM_CFLAGS)
LIBS = $(GSTREAMERMM_LIBS) $(GSTREAMERBASEMM_LIBS) -lglibmm_generate_extra_defs-2.4

noinst_PROGRAMS = generate_extra_defs generate_defs_gstbase \
		  generate_plugin_gmmproc_file

generate_extra_defs_SOURCES = generate_defs_gst.cc
generate_defs_gstbase_SOURCES = generate_defs_gstbase.cc

generate_plugin_hg_file_SOURCES = generate_plugin_gmmproc_file.cc

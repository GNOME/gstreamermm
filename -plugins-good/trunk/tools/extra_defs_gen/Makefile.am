# Build the generate_properties_defs utility executable.
# This is not used to build the rest of gtkmm.

INCLUDES = $(GSTREAMERMM_PLUGINS_GOOD_CFLAGS)
LIBS = $(GSTREAMERMM_PLUGINS_GOOD_LIBS) -lglibmm_generate_extra_defs-2.4 \
       -lgstreamermm_get_plugin_defs-0.10

noinst_PROGRAMS = generate_defs_gst

generate_defs_gst_SOURCES = generate_defs_gst.cc

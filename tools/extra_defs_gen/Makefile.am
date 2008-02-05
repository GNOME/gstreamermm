# Build the generate_properties_defs utility executable.
# This is not used to build the rest of gtkmm.

INCLUDES = $(GSTREAMERMM_CFLAGS)
LIBS = $(GSTREAMERMM_LIBS) -lglibmm_generate_extra_defs-2.4

noinst_PROGRAMS = generate_extra_defs
generate_extra_defs_SOURCES = generate_defs_gst.cc

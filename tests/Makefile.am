## Copyright 2009 The gstreamermm Development Team
##
## This library is free software: you can redistribute it and/or modify it
## under the terms of the GNU Lesser General Public License as published
## by the Free Software Foundation, either version 2.1 of the License,
## or (at your option) any later version.
##
## This library is distributed in the hope that it will be useful,
## but WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
## Lesser General Public License for more details.
##
## You should have received a copy of the GNU Lesser General Public License
## along with this program.  If not, see <http://www.gnu.org/licenses/>.

gstreamermm_includes = -I$(top_builddir)/gstreamer $(if $(srcdir:.=),-I$(top_srcdir)/gstreamer)
local_libgstreamermm = $(top_builddir)/gstreamer/gstreamermm/libgstreamermm-$(GSTREAMERMM_API_VERSION).la

AM_CPPFLAGS = -I$(top_builddir) $(gstreamermm_includes) $(GSTREAMERMM_CFLAGS)
AM_CXXFLAGS = $(GSTREAMERMM_WXXFLAGS)
LDADD = $(GSTREAMERMM_LIBS) $(local_libgstreamermm)

check_PROGRAMS = test-caps test-create-element test-pipeline-add-element \
                 test-link-elements test-create-bin test-miniobject-wrap \
                 test-message-wrap test-event-wrap test-query-wrap \
                 test-structure test-caps-structures test-interface \
                 test-create-bus test-taglist test-tagsetter test-pad \
                 test-ghost-pad test-init-check test-init \
                 test-init-check-noargs test-init-noargs test-iterator \
                 test-property-caps test-plugin-gen test-plugin-signals \
                 test-plugin-register test-plugin-appsrc test-plugin-appsink test-plugin-pushsrc test-buffer-list-iterator test-base-src

# Include run of test programs in check:
TESTS = $(check_PROGRAMS)

test_caps_SOURCES			= test-caps.cc
test_create_element_SOURCES		= test-create-element.cc
test_pipeline_add_element_SOURCES	= test-pipeline-add-element.cc
test_link_elements_SOURCES		= test-link-elements.cc
test_create_bin_SOURCES			= test-create-bin.cc
test_miniobject_wrap_SOURCES		= test-miniobject-wrap.cc
test_message_wrap_SOURCES		= test-message-wrap.cc
test_event_wrap_SOURCES			= test-event-wrap.cc
test_query_wrap_SOURCES			= test-query-wrap.cc
test_structure_SOURCES			= test-structure.cc
test_caps_structures_SOURCES		= test-caps-structures.cc
test_interface_SOURCES			= test-interface.cc
test_create_bus_SOURCES			= test-create-bus.cc
test_taglist_SOURCES			= test-taglist.cc
test_tagsetter_SOURCES			= test-tagsetter.cc
test_pad_SOURCES			= test-pad.cc
test_ghost_pad_SOURCES			= test-ghost-pad.cc
test_init_check_SOURCES			= test-init-check.cc
test_init_SOURCES			= test-init.cc
test_init_check_noargs_SOURCES		= test-init-check-noargs.cc
test_init_noargs_SOURCES		= test-init-noargs.cc
test_iterator_SOURCES			= test-iterator.cc
test_property_caps_SOURCES		= test-property-caps.cc
test_plugin_appsrc_SOURCES    = test-plugin-appsrc.cc
test_plugin_appsink_SOURCES    = test-plugin-appsink.cc
test_plugin_pushsrc_SOURCES    = test-plugin-pushsrc.cc 
test_plugin_gen_SOURCES			= test-plugin-gen.cc
test_plugin_signals_SOURCES		= test-plugin-signals.cc
test_plugin_register_SOURCES    = test-plugin-register.cc 
test_buffer_list_iterator_SOURCES	= test-buffer-list-iterator.cc
test_base_src_SOURCES			= test-base-src.cc

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
AM_CPPFLAGS = -I$(top_builddir) -I$(srcdir) $(gstreamermm_includes) $(GSTREAMERMM_CFLAGS) -std=c++0x -Wall -Werror -Wextra
AM_CXXFLAGS = $(GSTREAMERMM_WXXFLAGS) -g -Wno-missing-field-initializers
LDADD = $(GSTREAMERMM_LIBS) $(local_libgstreamermm) -lgtest -lpthread

CLEANFILES = test-integration-bininpipeline-output-image.jpg

check_PROGRAMS =                                \
        test-allocator                          \
        test-atomicqueue                        \
        test-bin                                \
        test-buffer                             \
        test-bufferlist                         \
        test-bus                                \
        test-caps                               \
        test-capsfeatures                       \
        test-element                            \
        test-ghostpad                           \
        test-init                               \
        test-iterator                           \
        test-memory                             \
        test-message                            \
        test-miniobject                         \
        test-pad                                \
        test-pipeline                           \
        test-query                              \
	test-sample				\
        test-structure                          \
        test-taglist                            \
        test-urihandler                         \
        test-value				\
                                                \
        test-plugin-appsink                     \
        test-plugin-appsrc                      \
        test-plugin-derivedfromappsink          \
        test-plugin-derivedfromappsrc           \
        test-plugin-derivedfrombasetransform    \
        test-plugin-pushsrc                     \
        test-plugin-register                    \
                                                \
        test-integration-bininpipeline          \
        test-integration-binplugin              \
        test-integration-rewritefile            \
        test-integration-seekonstartup          \
        test-integration-videoduration


# Include run of test programs in check:
TESTS = $(check_PROGRAMS)
TEST_GTEST_SOURCES = main.cc
TEST_INTEGRATION_UTILS = integration/utils.cc

test_allocator_SOURCES                          = $(TEST_GTEST_SOURCES) test-allocator.cc
test_atomicqueue_SOURCES                        = $(TEST_GTEST_SOURCES) test-atomicqueue.cc
test_bin_SOURCES                                = $(TEST_GTEST_SOURCES) test-bin.cc
test_buffer_SOURCES                             = $(TEST_GTEST_SOURCES) test-buffer.cc
test_bufferlist_SOURCES                         = $(TEST_GTEST_SOURCES) test-bufferlist.cc
test_bus_SOURCES                                = $(TEST_GTEST_SOURCES) test-bus.cc
test_capsfeatures_SOURCES                       = $(TEST_GTEST_SOURCES) test-capsfeatures.cc
test_caps_SOURCES                               = $(TEST_GTEST_SOURCES) test-caps.cc
test_element_SOURCES                            = $(TEST_GTEST_SOURCES) test-element.cc
test_ghostpad_SOURCES                           = $(TEST_GTEST_SOURCES) test-ghostpad.cc
test_init_SOURCES                               = $(TEST_GTEST_SOURCES) test-init.cc
test_iterator_SOURCES                           = $(TEST_GTEST_SOURCES) test-iterator.cc
test_memory_SOURCES                             = $(TEST_GTEST_SOURCES) test-memory.cc
test_message_SOURCES                            = $(TEST_GTEST_SOURCES) test-message.cc
test_miniobject_SOURCES                         = $(TEST_GTEST_SOURCES) test-miniobject.cc
test_pad_SOURCES                                = $(TEST_GTEST_SOURCES) test-pad.cc
test_pipeline_SOURCES                           = $(TEST_GTEST_SOURCES) test-pipeline.cc
test_query_SOURCES                              = $(TEST_GTEST_SOURCES) test-query.cc
test_sample_SOURCES                             = $(TEST_GTEST_SOURCES) test-sample.cc
test_structure_SOURCES                          = $(TEST_GTEST_SOURCES) test-structure.cc
test_taglist_SOURCES                            = $(TEST_GTEST_SOURCES) test-taglist.cc
test_urihandler_SOURCES                         = $(TEST_GTEST_SOURCES) test-urihandler.cc
test_value_SOURCES                              = $(TEST_GTEST_SOURCES) test-value.cc

test_plugin_appsink_SOURCES                     = $(TEST_GTEST_SOURCES) plugins/test-plugin-appsink.cc
test_plugin_appsrc_SOURCES                      = $(TEST_GTEST_SOURCES) plugins/test-plugin-appsrc.cc
test_plugin_derivedfromappsink_SOURCES          = $(TEST_GTEST_SOURCES) plugins/test-plugin-derivedfromappsink.cc
test_plugin_derivedfromappsrc_SOURCES           = $(TEST_GTEST_SOURCES) plugins/test-plugin-derivedfromappsrc.cc
test_plugin_derivedfrombasetransform_SOURCES    = $(TEST_GTEST_SOURCES) plugins/test-plugin-derivedfrombasetransform.cc
test_plugin_pushsrc_SOURCES                     = $(TEST_GTEST_SOURCES) plugins/test-plugin-pushsrc.cc
test_plugin_register_SOURCES                    = $(TEST_GTEST_SOURCES) plugins/test-plugin-register.cc

test_integration_bininpipeline_SOURCES          = $(TEST_GTEST_SOURCES) $(TEST_INTEGRATION_UTILS) integration/test-integration-bininpipeline.cc
test_integration_binplugin_SOURCES              = $(TEST_GTEST_SOURCES) integration/test-integration-binplugin.cc
test_integration_rewritefile_SOURCES            = $(TEST_GTEST_SOURCES) $(TEST_INTEGRATION_UTILS) integration/test-integration-rewritefile.cc
test_integration_seekonstartup_SOURCES          = $(TEST_GTEST_SOURCES) $(TEST_INTEGRATION_UTILS) integration/test-integration-seekonstartup.cc
test_integration_videoduration_SOURCES          = $(TEST_GTEST_SOURCES) $(TEST_INTEGRATION_UTILS) integration/test-integration-videoduration.cc 

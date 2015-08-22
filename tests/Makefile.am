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
gtest_includes = -I$(srcdir)/gtest/gtest-1.7.0 -I$(srcdir)/gtest/gtest-1.7.0/include
AM_CPPFLAGS = -I$(top_builddir) $(gstreamermm_includes) $(gtest_includes) $(GSTREAMERMM_CFLAGS) -std=c++0x -Wall -Werror -Wextra
AM_CXXFLAGS = $(GSTREAMERMM_WXXFLAGS) -g -Wno-missing-field-initializers
LDADD = $(GSTREAMERMM_LIBS) $(local_libgstreamermm) -lpthread

check_PROGRAMS =                                \
        test-allocator                          \
        test-atomicqueue                        \
        test-bin                                \
        test-buffer                             \
        test-bufferlist                         \
        test-bus                                \
        test-caps                               \
        test-caps                               \
        test-capsfeatures                       \
        test-element                            \
        test-ghostpad                           \
        test-init                               \
        test-memory                             \
        test-message                            \
        test-miniobject                         \
        test-pad                                \
        test-pipeline                           \
        test-query                              \
        test-structure                          \
        test-taglist                            \
        test-urihandler                         \
                                                \
        test-plugin-appsink                     \
        test-plugin-appsrc                      \
        test-plugin-derivedfromappsink          \
        test-plugin-derivedfromappsrc           \
        test-plugin-derivedfrombasetransform    \
        test-plugin-pushsrc                     \
        test-plugin-register                    \
                                                \
        test-regression-bininpipeline           \
        test-regression-binplugin               \
        test-regression-rewritefile             \
        test-regression-seekonstartup           \
        test-regression-videoduration


# Include run of test programs in check:
TESTS = $(check_PROGRAMS)
TEST_GTEST_SOURCES = main.cc gtest/gtest-1.7.0/src/gtest-all.cc
TEST_REGRESSION_UTILS = regression/utils.cc

$(TEST_GTEST_SOURCES): gtest

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
test_memory_SOURCES                             = $(TEST_GTEST_SOURCES) test-memory.cc
test_message_SOURCES                            = $(TEST_GTEST_SOURCES) test-message.cc
test_miniobject_SOURCES                         = $(TEST_GTEST_SOURCES) test-miniobject.cc
test_pad_SOURCES                                = $(TEST_GTEST_SOURCES) test-pad.cc
test_pipeline_SOURCES                           = $(TEST_GTEST_SOURCES) test-pipeline.cc
test_query_SOURCES                              = $(TEST_GTEST_SOURCES) test-query.cc
test_structure_SOURCES                          = $(TEST_GTEST_SOURCES) test-structure.cc
test_taglist_SOURCES                            = $(TEST_GTEST_SOURCES) test-taglist.cc
test_urihandler_SOURCES                         = $(TEST_GTEST_SOURCES) test-urihandler.cc

test_plugin_appsink_SOURCES                     = $(TEST_GTEST_SOURCES) plugins/test-plugin-appsink.cc
test_plugin_appsrc_SOURCES                      = $(TEST_GTEST_SOURCES) plugins/test-plugin-appsrc.cc
test_plugin_derivedfromappsink_SOURCES          = $(TEST_GTEST_SOURCES) plugins/test-plugin-derivedfromappsink.cc
test_plugin_derivedfromappsrc_SOURCES           = $(TEST_GTEST_SOURCES) plugins/test-plugin-derivedfromappsrc.cc
test_plugin_derivedfrombasetransform_SOURCES    = $(TEST_GTEST_SOURCES) plugins/test-plugin-derivedfrombasetransform.cc
test_plugin_pushsrc_SOURCES                     = $(TEST_GTEST_SOURCES) plugins/test-plugin-pushsrc.cc
test_plugin_register_SOURCES                    = $(TEST_GTEST_SOURCES) plugins/test-plugin-register.cc

test_regression_bininpipeline_SOURCES           = $(TEST_GTEST_SOURCES) $(TEST_REGRESSION_UTILS) regression/test-regression-bininpipeline.cc
test_regression_binplugin_SOURCES               = $(TEST_GTEST_SOURCES) regression/test-regression-binplugin.cc
test_regression_rewritefile_SOURCES             = $(TEST_GTEST_SOURCES) $(TEST_REGRESSION_UTILS) regression/test-regression-rewritefile.cc
test_regression_seekonstartup_SOURCES           = $(TEST_GTEST_SOURCES) $(TEST_REGRESSION_UTILS) regression/test-regression-seekonstartup.cc
test_regression_videoduration_SOURCES           = $(TEST_GTEST_SOURCES) $(TEST_REGRESSION_UTILS) regression/test-regression-videoduration.cc 

download_curl = $(CURL) --compressed --connect-timeout 300 -g -L -m 3600 -R --retry 5 \
		$(if $(wildcard $@),-z $@) -o $@
download_wget = $(WGET) -N -nd -T 300 -t 5 -P $(dir $@)
gtest_url = https://googletest.googlecode.com/files/gtest-1.7.0.zip

gtest.zip:
	$(AM_V_GEN)$(if $(filter no,$(ENABLE_UNITTESTS)),\
	echo 'Error: $@ does not exist.';\
	echo 'Unit tests are disabled.';\
	echo 'Please run configure script without --disable-unittests flag.' >&2;\
	exit 1;,\
	$(if\
	$(CURL),$(download_curl) '$(gtest_url)',$(if\
	$(WGET),$(download_wget) '$(gtest_url)',test -f $@)))

gtest: gtest.zip
	unzip -nq -d gtest gtest.zip

check_DATA = gtest
CLEANFILES = gtest.zip
clean-local:
	rm -rf gtest

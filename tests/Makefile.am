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

AM_CPPFLAGS = -I$(top_builddir) $(gstreamermm_includes) $(GSTREAMERMM_CFLAGS) -std=c++0x
AM_CXXFLAGS = $(GSTREAMERMM_WXXFLAGS) -g
LDADD = $(GSTREAMERMM_LIBS) $(local_libgstreamermm) -lgtest -lpthread

check_PROGRAMS = test-caps test-buffer test-bus test-caps test-pad \
                 test-allocator test-atomicqueue test-bin \
                 test-capsfeatures \
                 test-urihandler test-ghostpad test-init test-miniobject \
                 test-query test-structure test-taglist test-plugin-appsink \
                 test-plugin-appsrc test-plugin-register test-plugin-pushsrc \
                 test-regression-bininpipeline test-regression-binplugin \
                 test-pipeline \
                 test-regression-rewritefile test-regression-seekonstartup \
                 test-regression-videoduration

# Include run of test programs in check:
TESTS = $(check_PROGRAMS)
TEST_MAIN_SOURCE = main.cc
TEST_REGRESSION_UTILS = regression/utils.cc

test_allocator_SOURCES		= test-allocator.cc $(TEST_MAIN_SOURCE)
test_atomicqueue_SOURCES	= test-atomicqueue.cc $(TEST_MAIN_SOURCE)
test_bin_SOURCES			= test-bin.cc $(TEST_MAIN_SOURCE)
test_caps_SOURCES			= test-caps.cc $(TEST_MAIN_SOURCE)
test_capsfeatures_SOURCES	= test-capsfeatures.cc $(TEST_MAIN_SOURCE)
test_buffer_SOURCES			= test-buffer.cc $(TEST_MAIN_SOURCE)
test_bus_SOURCES			= test-bus.cc $(TEST_MAIN_SOURCE)
test_ghostpad_SOURCES		= test-ghostpad.cc $(TEST_MAIN_SOURCE)
test_init_SOURCES			= test-init.cc $(TEST_MAIN_SOURCE)
test_miniobject_SOURCES		= test-miniobject.cc $(TEST_MAIN_SOURCE)
test_pad_SOURCES			= test-pad.cc $(TEST_MAIN_SOURCE)
test_pipeline_SOURCES			= test-pipeline.cc $(TEST_MAIN_SOURCE)
test_query_SOURCES			= test-query.cc $(TEST_MAIN_SOURCE)
test_structure_SOURCES		= test-structure.cc $(TEST_MAIN_SOURCE)
test_taglist_SOURCES		= test-taglist.cc $(TEST_MAIN_SOURCE)
test_urihandler_SOURCES		= test-urihandler.cc $(TEST_MAIN_SOURCE)

test_plugin_appsink_SOURCES			= plugins/test-plugin-appsink.cc $(TEST_MAIN_SOURCE)
test_plugin_appsrc_SOURCES			= plugins/test-plugin-appsrc.cc $(TEST_MAIN_SOURCE)
test_plugin_pushsrc_SOURCES			= plugins/test-plugin-pushsrc.cc $(TEST_MAIN_SOURCE)
test_plugin_register_SOURCES		= plugins/test-plugin-register.cc $(TEST_MAIN_SOURCE)

test_regression_bininpipeline_SOURCES = regression/test-regression-bininpipeline.cc $(TEST_MAIN_SOURCE) $(TEST_REGRESSION_UTILS)
test_regression_binplugin_SOURCES = regression/test-regression-binplugin.cc $(TEST_MAIN_SOURCE) 
test_regression_rewritefile_SOURCES = regression/test-regression-rewritefile.cc $(TEST_MAIN_SOURCE) $(TEST_REGRESSION_UTILS)
test_regression_seekonstartup_SOURCES = regression/test-regression-seekonstartup.cc $(TEST_MAIN_SOURCE) $(TEST_REGRESSION_UTILS)
test_regression_videoduration_SOURCES = regression/test-regression-videoduration.cc $(TEST_MAIN_SOURCE) $(TEST_REGRESSION_UTILS)

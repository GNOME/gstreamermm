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
AM_CXXFLAGS = $(GSTREAMERMM_WXXFLAGS) -g
LDADD = $(GSTREAMERMM_LIBS) $(local_libgstreamermm) -lgtest

check_PROGRAMS = test-caps test-buffer test-bus test-caps test-pad \
                 test-structure test-taglist

# Include run of test programs in check:
TESTS = $(check_PROGRAMS)

test_caps_SOURCES			= test-caps.cc main.cc
test_buffer_SOURCES			= test-buffer.cc main.cc
test_bus_SOURCES			= test-bus.cc main.cc
test_caps_SOURCES			= test-caps.cc main.cc
test_pad_SOURCES			= test-pad.cc main.cc
test_structure_SOURCES		= test-structure.cc main.cc
test_taglist_SOURCES		= test-taglist.cc main.cc


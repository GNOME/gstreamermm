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

AUTOMAKE_OPTIONS = subdir-objects

noinst_PROGRAMS =			\
	element_link/example		\
	media_player_gtkmm/example	\
	ogg_player/example		\
	ogg_player_gtkmm/example	\
	optiongroup/example		\
	typefind/example

gstreamermm_includes = -I$(top_builddir)/gstreamer \
		      $(if $(srcdir:.=),-I$(top_srcdir)/gstreamer) \
		      $(GSTREAMERMM_EXAMPLES_CFLAGS) $(GSTREAMERMM_CFLAGS)
local_cppflags       = -I$(top_builddir) $(gstreamermm_includes)

AM_CPPFLAGS          = $(local_cppflags) $(GTHREAD_CFLAGS)
AM_CXXFLAGS          = $(GSTREAMERMM_WXXFLAGS)

local_libgstreamermm = $(top_builddir)/gstreamer/gstreamermm/libgstreamermm-$(GSTREAMERMM_API_VERSION).la

LDADD                = $(GSTREAMERMM_EXAMPLES_LIBS) $(GSTREAMERMM_LIBS) \
		       $(local_libgstreamermm)

element_link_example_SOURCES 		= element_link/element_link.cc
media_player_gtkmm_example_SOURCES 	= media_player_gtkmm/main.cc \
				  	  media_player_gtkmm/player_window.cc \
				  	  media_player_gtkmm/player_window.h
ogg_player_example_SOURCES		= ogg_player/main.cc
ogg_player_gtkmm_example_SOURCES	= ogg_player_gtkmm/main.cc \
				  	  ogg_player_gtkmm/player_window.cc \
				  	  ogg_player_gtkmm/player_window.h
optiongroup_example_SOURCES		= optiongroup/main.cc
typefind_example_SOURCES		= typefind/main.cc

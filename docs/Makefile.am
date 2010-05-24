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

include $(top_srcdir)/gstreamer/src/filelist.am
include $(top_srcdir)/gstreamer/gstreamermm/filelist.am

book_name = $(GSTREAMERMM_MODULE_NAME)
doc_input = $(addprefix $(top_srcdir)/gstreamer/gstreamermm/,$(files_built_h)) \
	    $(addprefix $(top_srcdir)/gstreamer/gstreamermm/,$(files_extra_h)) \
	    $(top_srcdir)/gstreamer/gstreamermm.h

include $(top_srcdir)/build/doc-reference.am

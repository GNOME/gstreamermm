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

lib_LTLIBRARIES = libgstreamermm-@GSTREAMERMM_API_VERSION@.la

include $(srcdir)/../src/filelist.am
include $(srcdir)/filelist.am
include $(top_srcdir)/build/compile-binding.am

stampdir = $(srcdir)/.stamps
patched_stamps = $(patched_hg:%.hg=$(stampdir)/stamp-%)

BUILT_SOURCES = $(patched_stamps)

generate_gst_wrap_init_in = $(top_builddir)/tools/generate_gst_wrap_init.pl.in
generate_gst_wrap_init = $(PERL) -- $(top_builddir)/tools/generate_gst_wrap_init.pl
generate_gst_wrap_init_flags = --namespace=Gst --parent_dir=gstreamermm

gst_wrap_init.cc: $(generate_gst_wrap_init_in) $(files_hg:%=$(srcdir)/../src/%)
	$(generate_gst_wrap_init) $(generate_gst_wrap_init_flags) \
		$(files_hg:%=$(srcdir)/../src/%) > $@

$(stampdir):
	@(test -d $(stampdir) || mkdir $(stampdir))
	
# This is to patch generated .h files in $(gensrc_destdir) (e.g. taglist.h).
$(stampdir)/stamp-%: $(stampdir) $(srcdir)/%.h
	patch -Ns $(srcdir)/$*.h $(srcdir)/$*.h.patch || true
	rm -f $(srcdir)/$*.h.rej
	@echo 'timestamp' > $@

local_cppflags = $(binding_includes) $(binding_cppflags) -DGSTREAMERMM_BUILD=1

AM_CPPFLAGS = $(local_cppflags) $(GTHREAD_CFLAGS) $(GSTREAMERMM_CFLAGS)
AM_CXXFLAGS = $(GSTREAMERMM_WXXFLAGS)

libgstreamermm_@GSTREAMERMM_API_VERSION@_la_SOURCES = $(binding_sources)
libgstreamermm_@GSTREAMERMM_API_VERSION@_la_LDFLAGS = -no-undefined -version-info $(GSTREAMERMM_SO_VERSION)
libgstreamermm_@GSTREAMERMM_API_VERSION@_la_LIBADD  = $(GSTREAMERMM_LIBS)

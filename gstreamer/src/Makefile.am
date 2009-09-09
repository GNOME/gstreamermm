# Copyright 2009 The gstreamermm Development Team
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

binding_name     = gstreamermm
wrap_init_flags  = --namespace=Gst --parent_dir=gstreamermm
codegen_srcdir   = $(top_srcdir)/tools
extradefs_srcdir = $(codegen_srcdir)/extra_defs_gen
m4_srcdir  	 = $(codegen_srcdir)/m4

# The generate_plugin_gmmproc_file utility
generate_plugin_gmmproc_file_source = $(extradefs_srcdir)/generate_plugin_gmmproc_file.cc
generate_plugin_gmmproc_file_path = $(extradefs_srcdir)/generate_plugin_gmmproc_file
generate_plugin_gmmproc_file_args = --namespace=Gst --main-defs=gst --target=gstreamermm
run_generate_plugin_gmmproc_file = $(generate_plugin_gmmproc_file_path) $(generate_plugin_gmmproc_file_args)

include $(srcdir)/filelist.am
include $(top_srcdir)/tools/m4/filelist.am
include $(top_srcdir)/build/generate-binding.am

if MAINTAINER_MODE
generate_plugin_dep = $(generate_plugin_gmmproc_file_source)
endif

# The source file from which the license header may be extracted and placed in
# plug-in generated .hg and .ccg files (use a file that probably will not
# change because it will be a plug-in generation dependency):
license_header_source_file = $(srcdir)/../gstreamermm/version.h

# This is to generate plugin .ccg files.  The generated .ccg file is piped
# through m4 using the macros in tools/m4/ctocpp_base.m4 which then produces
# the final .ccg file.
$(plugins_ccg): $(generate_plugin_dep) $(files_plugin_m4:%=$(m4_srcdir)/%) \
	$(license_header_source_file)
	$(eval list_delim = $$(patsubst $$@,+,$$(plugins_ccg)))
	$(eval prev_mems = $$(shell echo "$$(list_delim)" | cut -d'+' -f 1))
	$(eval pos = $$(shell expr `echo "$$(prev_mems)" | wc -w` + 1))
	$(eval plugin_def = $$(word $$(pos),$$(GSTREAMERMM_PLUGIN_DEFS)))
	$(eval plugin_name = $$(shell echo "$$(plugin_def)" | cut -d'=' -f 1))
	$(eval cppname = $$(subst $$(plugin_name)=,,$$(plugin_def)))
if MAINTAINER_MODE
	@if $(run_generate_plugin_gmmproc_file) --confirm-existence \
		$(plugin_name); then true; else \
		echo "The $(plugin_name) gstreamer plugin is not installed.  Aborting build. If you built gst-plugins-base from source code then you might need to install the appropriate -dev or --devel packages or enable experimenal plugins before rebuilding gst-plugins-base."; \
		false; \
	fi
endif
	sed -n '1,/^$$/p' $(license_header_source_file) > $(srcdir)/$@
	$(run_generate_plugin_gmmproc_file) --ccg $(plugin_name) \
		$(cppname) | m4 -I $(m4_srcdir) >> $(srcdir)/$@

# This is to generate plugin .hg files.  The generated .hg file is piped
# through m4 using the macros in tools/m4/ctocpp_base.m4 which then produces
# the final .hg file.
$(plugins_hg): %.hg: $(generate_plugin_dep) \
	$(files_plugin_m4:%=$(m4_srcdir)/%) $(license_header_source_file) %.ccg
	$(eval list_delim = $$(patsubst $$@,+,$$(plugins_hg)))
	$(eval prev_mems = $$(shell echo "$$(list_delim)" | cut -d'+' -f 1))
	$(eval pos = $$(shell expr `echo "$$(prev_mems)" | wc -w` + 1))
	$(eval plugin_def = $$(word $$(pos),$$(GSTREAMERMM_PLUGIN_DEFS)))
	$(eval plugin_name = $$(shell echo "$$(plugin_def)" | cut -d'=' -f 1))
	$(eval cppname = $$(subst $$(plugin_name)=,,$$(plugin_def)))
	sed -n '1,/^$$/p' $(license_header_source_file) > $(srcdir)/$@
	$(run_generate_plugin_gmmproc_file) --hg $(plugin_name) \
		$(cppname) | m4 -I $(m4_srcdir) >> $(srcdir)/$@

MAINTAINERCLEANFILES += $(plugins_hg) $(plugins_ccg)

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

binding_name    = gstreamermm
wrap_init_flags = --namespace=Gst --parent_dir=gstreamermm
codegen_srcdir  = $(top_srcdir)/tools

include $(srcdir)/plugin_filelist.am
plugins_ccg = $(plugins_hg:.hg=.ccg)

include $(srcdir)/filelist.am
include $(top_srcdir)/tools/m4/filelist.am
include $(top_srcdir)/build/generate-binding.am

other_built_sources  += 
MAINTAINERCLEANFILES += $(addprefix $(srcdir)/,$(plugins_ccg) $(plugins_hg))

generate_gst_wrap_init = $(codegen_srcdir)/generate_gst_wrap_init.pl

generate_plugin_gmmproc_file = \
	$(top_builddir)/tools/extra_defs_gen/generate_plugin_gmmproc_file$(EXEEXT) \
	--namespace=Gst --main-defs=gst --target=gstreamermm
generate_plugin_dependencies = \
	$(codegen_srcdir)/extra_defs_gen/generate_plugin_gmmproc_file.cc \
	$(addprefix $(codegen_m4_srcdir)/,$(files_plugin_m4))

target_hg_basename = $(basename $(notdir $@))
plugin_list = $(GSTREAMERMM_CORE_PLUGIN_DEFS) $(GSTREAMERMM_BASE_PLUGIN_DEFS)
target_plugin_and_classname = $(wordlist 2,3,$(subst |, ,$(filter $(target_hg_basename)|%,$(plugin_list))))
 
# This is to generate plugin .ccg files.  The generated .ccg file is piped
# through m4 using the macros in tools/m4/ctocpp_base.m4 which then produces
# the final .ccg file.
$(addprefix $(srcdir)/,$(plugins_ccg)): $(generate_plugin_dependencies)
	$(AM_V_GEN)$(generate_plugin_gmmproc_file) --ccg \
	  $(target_plugin_and_classname) | $(M4) -I $(codegen_m4_srcdir) >$@

# This is to generate plugin .hg files.  The generated .hg file is piped
# through m4 using the macros in tools/m4/ctocpp_base.m4 which then produces
# the final .hg file.
$(addprefix $(srcdir)/,$(plugins_hg)): %.hg: %.ccg $(generate_plugin_dependencies)
	$(AM_V_GEN)$(generate_plugin_gmmproc_file) \
	  --hg $(target_plugin_and_classname) | $(M4) -I $(codegen_m4_srcdir) \
	  >$@

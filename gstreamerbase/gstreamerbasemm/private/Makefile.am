## Copyright (c) 2008
## The gstreamermm development team.

include $(srcdir)/../../src/Makefile_list_of_hg.am_fragment

files_built_p_h		= $(files_hg:.hg=_p.h)
files_built_all_p_h	= $(files_all_hg:.hg=_p.h)
files_built_plugin_p_h	= $(files_plugin_hg:.hg=_p.h)
files_extra_p_h		= 
files_extra_all_p_h	= 

dist_sources = $(files_built_all_p_h) $(files_extra_all_p_h) \
	       $(files_built_plugin_p_h)
DISTFILES = $(DIST_COMMON) $(dist_sources)

CLEANFILES = $(files_built_plugin_p_h)

private_includedir	= $(includedir)/gstreamerbasemm-0.10/gstreamerbasemm/private
private_include_HEADERS	= $(files_built_p_h) $(files_extra_p_h)

maintainer-clean-local:
	(cd $(srcdir) && rm -f $(files_built_p_h) $(files_built_plugin_p_h))

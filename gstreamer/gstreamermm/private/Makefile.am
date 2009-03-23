## Copyright (c) 2001
## The gtkmm development team.

include $(srcdir)/../../src/Makefile_list_of_hg.am_fragment

files_built_p_h		= $(files_hg:.hg=_p.h)
files_built_all_p_h	= $(files_all_hg:.hg=_p.h)
files_all_plugin_p_h = $(files_all_plugin_hg:.hg=_p.h)
files_existing_plugin_p_h = $(files_existing_plugin_hg:.hg=_p.h)
files_extra_p_h		= miniobject_p.h taglist_p.h
files_extra_all_p_h	= miniobject_p.h taglist_p.h

dist_sources = $(files_built_all_p_h) $(files_extra_all_p_h) \
	       $(files_all_plugin_p_h)

DISTFILES = $(DIST_COMMON) $(dist_sources)

EXTRA_HEADERS = $(files_all_plugin_p_h)

private_includedir	= $(includedir)/gstreamermm-0.10/gstreamermm/private
private_include_HEADERS	= $(files_built_p_h) $(files_extra_p_h)

EXTRA_private_includedir = $(includedir)/gstreamermm-0.10/gstreamermm/private
EXTRA_private_include_HEADERS = $(files_existing_plugin_p_h)

maintainer-clean-local:
	(cd $(srcdir) && rm -f $(files_built_p_h) $(files_all_plugin_p_h))

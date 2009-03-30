## Copyright (c) 2009
## The gstreamermm development team.

SUBDIRS=reference

doc-clean-recursive:
	list='$(SUBDIRS)'; for subdir in $$list; do \
	  test "$$subdir" = . || (cd $$subdir && $(MAKE) $(AM_MAKEFLAGS) doc-clean); \
	done

doc-clean: doc-clean-recursive

doc-rebuild: doc-clean all

.PHONY: doc-clean doc-clean-recursive doc-rebuild


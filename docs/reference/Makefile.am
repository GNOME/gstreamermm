doxygenprog=@DOXYGEN@

doxygen_configfile=Doxyfile
beautify_docs = @GMMPROC_DIR@/beautify_docs.pl

docdir = $(datadir)/doc/gstreamermm-0.10/docs
referencedir=$(docdir)/reference/html

EXTRA_DIST=$(doxygen_configfile) reference-index.txt

HTML_INDEX=html/index.html

$(HTML_INDEX): $(doxygen_configfile) $(beautify_docs_source) $(top_srcdir)/gstreamer/gstreamermm/*.h $(top_srcdir)/gstreamerbase/gstreamerbasemm/*.h
	rm -rf html
	$(doxygenprog) $(doxygen_configfile)
	$(PERL_PATH) $(beautify_docs) html && touch $@

doc-clean:
	rm -rf html
	rm -f doxygen-warnings.txt

install-reference: $(HTML_INDEX)
	@$(NORMAL_INSTALL)
	$(mkinstalldirs) $(DESTDIR)$(referencedir)
	@dir='$(<D)'; for p in $$dir/*.html $$dir/*.css $$dir/*.png; do \
	  f="`echo $$p | sed -e 's|^.*/||'`"; \
	  echo " $(INSTALL_DATA) $$p $(DESTDIR)$(referencedir)/$$f"; \
	  $(INSTALL_DATA) $$p $(DESTDIR)$(referencedir)/$$f; \
	done

uninstall-reference: $(HTML_INDEX)
	@$(NORMAL_UNINSTALL)
	@dir='$(<D)'; for p in $$dir/*.html $$dir/*.css $$dir/*.png; do \
	  f="`echo $$p | sed -e 's|^.*/||'`"; \
	  echo " rm -f $(DESTDIR)$(referencedir)/$$f"; \
	  rm -f $(DESTDIR)$(referencedir)/$$f; \
	done

all-local: $(HTML_INDEX)

install-data-local: install-reference

uninstall-local: uninstall-reference

maintainer-clean-local: doc-clean

clean-local: doc-clean

.PHONY: doc-clean install-reference uninstall-reference


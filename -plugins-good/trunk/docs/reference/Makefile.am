doxygenprog=@DOXYGEN@

doxygen_configfile=Doxyfile
doxygen_configfile_source=$(srcdir)/Doxyfile.in
beautify_docs = @GMMPROC_DIR@/beautify_docs.pl

EXTRA_DIST= Doxyfile.in html

docdir = $(datadir)/doc/gstreamermm-plugins-good-0.10/docs
referencedir=$(docdir)/reference/html

HTML_INDEX=html/index.html

$(HTML_INDEX): $(doxygen_configfile_source) $(beautify_docs) \
	$(top_srcdir)/gstreamer-plugins-good/gstreamermm-plugins-good/*.h
	-rm -rf html
	$(doxygenprog) $(doxygen_configfile)
	$(PERL_PATH) $(beautify_docs) html && touch $@

gstreamermm-plugins-good-reference-html.tar.gz: $(HTML_INDEX)
	tar cf - html | gzip -c --best >$@

gstreamermm-plugins-good-reference-html.tar.bz2: $(HTML_INDEX)
	tar cf - html | bzip2 -c >$@

doc-clean:
	-rm -rf html
	-rm -f doxygen-warnings.txt
	-rm -f gstreamermm-plugins-good-reference-html.tar.gz \
		gstreamermm-plugins-good-reference-html.tar.bz2

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


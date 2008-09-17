INCLUDES= -I$(top_builddir)/gstreamer -I$(top_srcdir)/gstreamer \
	  -I$(top_builddir)/gstreamerbase -I$(top_srcdir)/gstreamerbase  @GSTREAMERMM_CFLAGS@

LDADD=$(top_builddir)/gstreamer/gstreamermm/libgstreamermm-0.10.la \
	$(top_builddir)/gstreamerbase/gstreamerbasemm/libgstreamerbasemm-0.10.la

noinst_PROGRAMS = test-caps test-create-element test-pipeline-add-element \
                  test-link-elements test-create-bin test-miniobject-wrap \
                  test-message-wrap test-event-wrap test-query-wrap \
		  test-structure test-caps-structures test-interface \
		  test-create-bus test-taglist test-tagsetter \
		  test-init-check test-init test-init-check-noargs \
		  test-init-noargs test-iterator test-property-caps

#TODO: Add test-pad to tests when bug #539108 is fixed.

test_caps_SOURCES=test-caps.cc
test_caps_LDFLAGS=@GSTREAMERMM_LIBS@

test_create_element_SOURCES=test-create-element.cc
test_create_element_LDFLAGS=@GSTREAMERMM_LIBS@

test_pipeline_add_element_SOURCES=test-pipeline-add-element.cc
test_pipeline_add_element_LDFLAGS=@GSTREAMERMM_LIBS@

test_link_elements_SOURCES=test-link-elements.cc
test_link_elements_LDFLAGS=@GSTREAMERMM_LIBS@

test_create_bin_SOURCES=test-create-bin.cc
test_create_bin_LDFLAGS=@GSTREAMERMM_LIBS@

test_miniobject_wrap_SOURCES=test-miniobject-wrap.cc
test_miniobject_wrap_LDFLAGS=@GSTREAMERMM_LIBS@

test_message_wrap_SOURCES=test-message-wrap.cc
test_message_wrap_LDFLAGS=@GSTREAMERMM_LIBS@

test_event_wrap_SOURCES=test-event-wrap.cc
test_event_wrap_LDFLAGS=@GSTREAMERMM_LIBS@

test_query_wrap_SOURCES=test-query-wrap.cc
test_query_wrap_LDFLAGS=@GSTREAMERMM_LIBS@

test_structure_SOURCES=test-structure.cc
test_structure_LDFLAGS=@GSTREAMERMM_LIBS@

test_caps_structures_SOURCES=test-caps-structures.cc
test_caps_structures_LDFLAGS=@GSTREAMERMM_LIBS@

test_interface_SOURCES=test-interface.cc
test_interface_LDFLAGS=@GSTREAMERMM_LIBS@

test_create_bus_SOURCES=test-create-bus.cc
test_create_bus_LDFLAGS=@GSTREAMERMM_LIBS@

test_taglist_SOURCES=test-taglist.cc
test_taglist_LDFLAGS=@GSTREAMERMM_LIBS@

test_tagsetter_SOURCES=test-tagsetter.cc
test_tagsetter_LDFLAGS=@GSTREAMERMM_LIBS@

#TODO: test_pad_SOURCES=test-pad.cc
#TODO: test_pad_LDFLAGS=@GSTREAMERMM_LIBS@

test_init_check_SOURCES=test-init-check.cc
test_init_check_LDFLAGS=@GSTREAMERMM_LIBS@

test_init_SOURCES=test-init.cc
test_init_LDFLAGS=@GSTREAMERMM_LIBS@

test_init_check_noargs_SOURCES=test-init-check-noargs.cc
test_init_check_noargs_LDFLAGS=@GSTREAMERMM_LIBS@

test_init_noargs_SOURCES=test-init-noargs.cc
test_init_noargs_LDFLAGS=@GSTREAMERMM_LIBS@

test_iterator_SOURCES=test-iterator.cc
test_iterator_LDFLAGS=@GSTREAMERMM_LIBS@

test_property_caps_SOURCES=test-property-caps.cc
test_property_caps_LDFLAGS=@GSTREAMERMM_LIBS@

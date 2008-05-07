INCLUDES= -I$(top_builddir)/gstreamer -I$(top_srcdir)/gstreamer \
	  -I$(top_builddir)/gstreamerbase -I$(top_srcdir)/gstreamerbase  @GSTREAMERMM_CFLAGS@

LDADD=$(top_builddir)/gstreamer/gstreamermm/libgstreamermm-0.10.la

noinst_PROGRAMS = test-caps test-create-element test-pipeline-add-element \
                  test-link-elements test-create-bin test-miniobject-wrap \
                  test-message-wrap test-event-wrap test-query-wrap \
		  test-structure test-caps-structures test-interface \
		  test-create-bus

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

#runtestbasic runtestlangs \
#runtestsearch runtestmimetypes \
#runtestgetbuffer

#runtestbasic_SOURCES=test-basic.cc
#runtestbasic_LDFLAGS=@GSTREAMERMM_LIBS@

#runtestlangs_SOURCES=test-langs.cc
#runtestlangs_LDFLAGS=@GSTREAMERMM_LIBS@

#runtestsearch_SOURCES=test-search.cc
#runtestsearch_LDFLAGS=@GSTREAMERMM_LIBS@

#runtestmimetypes_SOURCES=test-mime-types.cc
#runtestmimetypes_LDFLAGS=@GSTREAMERMM_LIBS@

#runtestgetbuffer_SOURCES=test-get-buffer.cc
#runtestgetbuffer_LDFLAGS=@GSTREAMERMM_LIBS@




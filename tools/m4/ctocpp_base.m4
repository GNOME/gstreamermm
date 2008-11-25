dnl
dnl Macros to convert from C to C++ types
dnl

m4_define(`_CPPTYPE',`dnl
m4_define(`TFP'__HASH(`$1'),`$2')'`dnl
m4_ifelse(`$3',,`dnl
m4_define(`TFR'__HASH(`$1'),`$2')',`dnl
m4_define(`TFR'__HASH(`$1'),`$3')dnl
')dnl
m4_ifelse(`$4',,,`m4_define(`IF'__HASH(`$1'),`$4')')dnl
')dnl

m4_define(`_CTOCPP',`dnl
m4_ifelse(`$2',,`dnl
m4_ifdef(`TFP'__HASH(`$1'), `m4_indir(`TFP'__HASH(`$1'))',`dnl
m4_errprint(`No C++ parameter conversion from $1 defined.
')`'dnl
m4_m4exit(1)`'dnl
')',`dnl
m4_ifdef(`TFR'__HASH(`$1'), `m4_indir(`TFR'__HASH(`$1'))',`dnl
m4_errprint(`No C++ return conversion from $1 defined.
')`'dnl
m4exit(1)`'dnl
')`'dnl
')`'dnl
')`'dnl

_CPPTYPE(`GParamBoolean',`bool')
_CPPTYPE(`GParamInt',`int')
_CPPTYPE(`GParamULong',`unsigned long')
_CPPTYPE(`GParamUInt64',`guint64',,`<glib.h>')
_CPPTYPE(`GParamString',`Glib::ustring')

dnl _CPPTYPE(`GstElement*',`const Glib::RefPtr<Gst::Element>&',`Glib::RefPtr<Gst::Element>',`<gstreamermm/element.h>')
dnl _CPPTYPE(`GstElementFactory*',`const Glib::RefPtr<Gst::ElementFactory>&',`Glib::RefPtr<Gst::ElementFactory>',`<gstreamermm/elementfactory.h>')

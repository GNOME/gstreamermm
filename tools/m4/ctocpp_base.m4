dnl
dnl Macros to convert from C to C++ types
dnl

dnl _CCONVERSION(ctype, param cpptype, return cpptype, cppinclude)
dnl
dnl Records a translation from a C type to a C++ type.  If a return cpptype is
dnl not given, it is assumed to be the same as the param cpptype.  A cpp
dnl include need not be specified (the <> or "" are required though).  If an
dnl include is specified, a C++ include directive may be generated with the
dnl _CCONVERSION_INCLUDE macro.
dnl
m4_define(`_CCONVERSION',`dnl
m4_define(`TFP'__HASH(`$1'),`$2')dnl
m4_ifelse(`$3',,`dnl
m4_define(`TFR'__HASH(`$1'),`$2')',`dnl
m4_define(`TFR'__HASH(`$1'),`$3')dnl
')`'dnl
m4_ifelse(`$4',,,`m4_define(`IF'__HASH(`$1'),`$4')')`'dnl
')dnl

dnl _CCONVERSION_INCLUDE(ctype)
dnl
dnl Produces a C++ include direcive of the C++ header for the ctype if a
dnl translation has been defined and an include parameter was included.  Only
dnl one directive will be generated for multiple calls (i.e. none but the first
dnl call produces anything).
dnl
m4_define(`_CCONVERSION_INCLUDE',`dnl
m4_ifdef(`IFC'__HASH(`$1'),,`dnl
m4_ifdef(`IF'__HASH(`$1'),`dnl
#include m4_indir(`IF'__HASH(`$1'))`'dnl
m4_define(`IFC'__HASH(`$1'),`complete')dnl
')`'dnl
')`'dnl
')dnl

dnl _CCONVERT(ctype, return)
dnl
dnl Translates from a specified C type to a C++ param or return type.  If a
dnl `return' (boolean) parameter is included, the return C++ type is rendered.
dnl If not (no second parameter), the C++ parameter type is rendered.
dnl
m4_define(`_CCONVERT',`dnl
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
')dnl

_CCONVERSION(`gboolean',`bool')
_CCONVERSION(`gint',`int')
_CCONVERSION(`gulong',`unsigned long')
_CCONVERSION(`guint64',`guint64')
_CCONVERSION(`gchararray',`const Glib::ustring&',`Glib::ustring')

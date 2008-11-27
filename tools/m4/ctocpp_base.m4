dnl
dnl Macros to convert from C to C++ types
dnl

dnl _CPPTYPE(ctype, param cpptype, return cpptype, cppinclude)
dnl
dnl Records a translation from a C type to a C++ type.  If a return cpptype is
dnl not given, it is assumed to be the same as the param cpptype.  A cpp
dnl include need not be specified (the <> or "" are required).  If an include
dnl is specified, a C++ include directive may be generated with the
dnl _CTOCPP_INCLUDE macro.
dnl
m4_define(`_CPPTYPE',`dnl
m4_define(`TFP'__HASH(`$1'),`$2')dnl
m4_ifelse(`$3',,`dnl
m4_define(`TFR'__HASH(`$1'),`$2')',`dnl
m4_define(`TFR'__HASH(`$1'),`$3')dnl
')`'dnl
m4_ifelse(`$4',,,`m4_define(`IF'__HASH(`$1'),`$4')')`'dnl
')dnl

dnl _CTOCPP_INCLUDE(ctype)
dnl
dnl Produces a C++ include direcive of the C++ header for the ctype if a
dnl translation has been defined and an include parameter was included.  Only
dnl one directive will be generated for multiple calls (i.e. none but the first
dnl call produces anything).
dnl
m4_define(`_CTOCPP_INCLUDE',`dnl
m4_ifdef(`IFC'__HASH(`$1'),,`dnl
m4_ifdef(`IF'__HASH(`$1'),`dnl
#include m4_indir(`IF'__HASH(`$1'))`'dnl
m4_define(`IFC'__HASH(`$1'),`complete')dnl
')`'dnl
')`'dnl
')dnl

dnl _CTOCPP(ctype, use return translation)
dnl
dnl Translates from a specified C type to a C++ param or return type.  If a
dnl `use return translation' (boolean) parameter is included, the return C++
dnl type is rendered.  If not (no second parameter), the C++ parameter type is
dnl rendered.
dnl
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
')dnl

_CPPTYPE(`GParamBoolean',`bool')
_CPPTYPE(`GParamInt',`int')
_CPPTYPE(`GParamULong',`unsigned long')
_CPPTYPE(`GParamUInt64',`guint64')
_CPPTYPE(`GParamString',`Glib::ustring')

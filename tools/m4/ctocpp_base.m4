divert(-1)
dnl
dnl Macros to convert from C to C++ types
dnl

dnl __HASH variable borrowed form glibmm's convert_base.m4 file
define(`__HASH',`__`'translit(`$*',`ABCDEFGHIJKLMNOPQRSTUVWXYZ<>[]&*, ',`abcdefghijklmnopqrstuvwxyzVBNMRSC_')`'')

dnl Macro to insert left quote
define(`_LQ',`changequote(<,>)`dnl'
changequote`'')

dnl Macro to insert right quote
define(`_RQ',`changequote(<,>)dnl`
'changequote`'')

dnl _CCONVERSION(ctype, cpptype, param cpptype, return cpptype, cppinclude)
dnl
dnl Records a translation from a C type to a C++ type.  If a return cpptype is
dnl not given, it is assumed to be the same as the param cpptype.  A cpp
dnl include need not be specified (the <> or "" are required though).  If an
dnl include is specified, a C++ include directive may be generated with the
dnl _CCONVERSION_INCLUDE macro.
dnl
define(`_CCONVERSION',`dnl
define(`TFT'__HASH(`$1'),`$2')dnl
define(`TFP'__HASH(`$1'),`$3')dnl
ifelse(`$4',,`dnl
define(`TFR'__HASH(`$1'),`$3')',`dnl
define(`TFR'__HASH(`$1'),`$4')dnl
')`'dnl
ifelse(`$5',,,`define(`IF'__HASH(`$1'),`$5')')`'dnl
')dnl

dnl _CCONVERSION_INCLUDE(ctype)
dnl
dnl Produces a C++ include direcive of the C++ header for the ctype if a
dnl translation has been defined and an include parameter was included.  Only
dnl one directive will be generated for multiple calls (i.e. none but the first
dnl call produces anything).
dnl
define(`_CCONVERSION_INCLUDE',`dnl
ifdef(`IFC'__HASH(`$1'),,`dnl
ifdef(`IF'__HASH(`$1'),`dnl
#include indir(`IF'__HASH(`$1'))
dnl
define(`IFC'__HASH(`$1'),`complete')dnl
')`'dnl
')`'dnl
')dnl

dnl _CCONVERT(ctype, conversion type)
dnl
dnl Translates from a specified C type to a C++ type, param or return type.
dnl `conversion type' may be:
dnl `type' - For a C to C++ type translation.
dnl `param' - For a C to C++ parameter translation.
dnl `ret' - For a C to C++ return translation.
dnl
define(`_CCONVERT',`dnl
ifelse(dnl
`$2',`type',`dnl
ifdef(`TFT'__HASH(`$1'), `indir(`TFT'__HASH(`$1'))',`dnl
errprint(`No C++ type conversion from $1 defined.
')`'dnl
m4exit(1)`'dnl
')',dnl
`$2',`param',`dnl
ifdef(`TFP'__HASH(`$1'), `indir(`TFP'__HASH(`$1'))',`dnl
errprint(`No C++ parameter conversion from $1 defined.
')`'dnl
m4exit(1)`'dnl
')',dnl
`$2',`ret',`dnl
ifdef(`TFR'__HASH(`$1'), `indir(`TFR'__HASH(`$1'))',`dnl
ifdef(`TFP'__HASH(`$1'), `indir(`TFP'__HASH(`$1'))',`dnl
errprint(`No C++ return conversion from $1 defined.
')`'dnl
m4exit(1)`'dnl
')`'dnl
')`'dnl
')`'dnl
')dnl

#Basic C to C++ translations
_CCONVERSION(`void',`void',`void')
_CCONVERSION(`gboolean',`bool',`bool')
_CCONVERSION(`gint',`int',`int')
_CCONVERSION(`guint',`guint',`guint')
_CCONVERSION(`gulong',`unsigned long',`unsigned long')
_CCONVERSION(`gint64',`gint64',`gint64')
_CCONVERSION(`guint64',`guint64',`guint64')
_CCONVERSION(`gfloat',`float',`float')
_CCONVERSION(`gdouble',`double',`double')

#String C to C++ translations
_CCONVERSION(`gchararray',`Glib::ustring',`const Glib::ustring&',`Glib::ustring')

include(ctocpp.m4)
divert(0)dnl

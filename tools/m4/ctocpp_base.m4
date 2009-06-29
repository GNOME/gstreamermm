divert(-1)
dnl
dnl Macros to translate from C to C++ types.
dnl

dnl __HASH variable borrowed form glibmm's convert_base.m4 file
define(`__HASH',`__`'translit(`$*',`ABCDEFGHIJKLMNOPQRSTUVWXYZ<>[]&*, ',`abcdefghijklmnopqrstuvwxyzVBNMRSC_')`'')

dnl _GET_TYPE_FUNC(GtkWidget) -> gtk_widget_get_type().  Borrowed from glibmm's convert_base.m4 file (see glibmm's m4 file for docs).
define(`_GET_TYPE_FUNC',`dnl
translit(substr(patsubst(patsubst(`$1',`[A-Z][A-Z]+',`_\&'),`[A-Z][a-z]',`_\&'),1),`[A-Z]',`[a-z]')_get_type()`'dnl
')

dnl Macro to insert left quote
define(`_LQ',`changequote(<,>)`dnl'
changequote`'')

dnl Macro to insert right quote
define(`_RQ',`changequote(<,>)dnl`
'changequote`'')

dnl _TRANSLATION(ctype, cpptype, param cpptype, return cpptype, cppinclude)
dnl
dnl Records a translation from a C type to a C++ type.  If a return cpptype is
dnl not given, it is assumed to be the same as the param cpptype.  A cpp
dnl include need not be specified (the <> or "" are required though).  If an
dnl include is specified, a C++ include directive may be generated with the
dnl _TRANSLATION_INCLUDE macro.
dnl
define(`_TRANSLATION',`dnl
define(`TFT'__HASH(`$1'),`$2')dnl
define(`TFP'__HASH(`$1'),`$3')dnl
ifelse(`$4',,`dnl
define(`TFR'__HASH(`$1'),`$3')',`dnl
define(`TFR'__HASH(`$1'),`$4')dnl
')`'dnl
ifelse(`$5',,,`define(`IF'__HASH(`$1'),`$5')')`'dnl
')dnl

dnl _TRANSLATION_INCLUDE(ctype)
dnl
dnl Produces a C++ include direcive of the C++ header for the ctype if a
dnl translation has been defined and an include parameter was included.  Only
dnl one directive will be generated for multiple calls (i.e. none but the first
dnl call produces anything).
dnl
define(`_TRANSLATION_INCLUDE',`dnl
ifdef(`IFC'__HASH(`$1'),,`dnl
ifdef(`IF'__HASH(`$1'),`dnl
#include indir(`IF'__HASH(`$1'))
dnl
define(`IFC'__HASH(`$1'),`complete')dnl
')`'dnl
')`'dnl
')dnl

dnl _TRANSLATE(ctype, translation type)
dnl
dnl Translates from a specified C type to a C++ type, param or return type.
dnl `translation type' may be:
dnl `type' - For a C to C++ type translation.
dnl `param' - For a C to C++ parameter translation.
dnl `return' - For a C to C++ return translation.
dnl
define(`_TRANSLATE',`dnl
ifelse(dnl
`$2',`type',`dnl
ifdef(`TFT'__HASH(`$1'), `indir(`TFT'__HASH(`$1'))',`dnl
errprint(`No C++ type translation from $1 is defined.
')`'dnl
m4exit(1)`'dnl
')',dnl
`$2',`param',`dnl
ifdef(`TFP'__HASH(`$1'), `indir(`TFP'__HASH(`$1'))',`dnl
errprint(`No C++ parameter translation from $1 is defined.
')`'dnl
m4exit(1)`'dnl
')',dnl
`$2',`return',`dnl
ifdef(`TFR'__HASH(`$1'), `indir(`TFR'__HASH(`$1'))',`dnl
ifdef(`TFP'__HASH(`$1'), `indir(`TFP'__HASH(`$1'))',`dnl
errprint(`No C++ return translation from $1 is defined.
')`'dnl
m4exit(1)`'dnl
')`'dnl
')`'dnl
')`'dnl
')dnl

dnl _ENUM_IS_WRAPPED(CEnumType)
dnl
dnl Used to tell when an enum has been wrapped.  When a _WRAP_PLUGIN_ENUM() is
dnl used to wrap enums used in plug-ins, the enum will be wrapped only if it
dnl hasn't been flagged as wrapped by this macro.
dnl
define(`_ENUM_IS_WRAPPED',`dnl
define(`EIW'__HASH(`$1'))dnl
')dnl

dnl _WRAP_PLUGIN_ENUM(CppEnumType, CEnumType)
dnl
dnl Attempts to generate a _WRAP_ENUM() and a _TRANSLATION() macro for an enum
dnl used by a plug-in.  If the enum has been flagged as wrapped by the
dnl _ENUM_IS_WRAPPED() macro nothing will be generated.
define(`_WRAP_PLUGIN_ENUM',`dnl
ifdef(`EIW'__HASH(`$2'),,`dnl
_WRAP_ENUM($1,$2)dnl
_TRANSLATION(`$2',`$1',`$1')dnl
')`'dnl
')dnl

dnl _PLUGIN_ENUM_GET_TYPE_FUNC(CEnumType)
dnl
dnl Attempts to generate a *_get_type() function for an enum specific to a
dnl plug-in.  If the enum has been flagged as wrapped by the
dnl _ENUM_IS_WRAPPED() macro it is taken taken to be a non-plugin enum and
dnl nothing will be generated.
define(`_PLUGIN_ENUM_GET_TYPE_FUNC',`dnl
ifdef(`EIW'__HASH(`$1'),,`dnl
static GType _GET_TYPE_FUNC($1)
{
  static GType const type = g_type_from_name("$1");
  return type;
}

')`'dnl
')dnl

#Basic C to C++ translations
_TRANSLATION(`void',`void',`void')
_TRANSLATION(`gboolean',`bool',`bool')
_TRANSLATION(`gint',`int',`int')
_TRANSLATION(`guint',`guint',`guint')
_TRANSLATION(`gulong',`unsigned long',`unsigned long')
_TRANSLATION(`gint64',`gint64',`gint64')
_TRANSLATION(`guint64',`guint64',`guint64')
_TRANSLATION(`gfloat',`float',`float')
_TRANSLATION(`gdouble',`double',`double')

#String C to C++ translations
_TRANSLATION(`gchararray',`Glib::ustring',`const Glib::ustring&',`Glib::ustring')

#Wrapped enums
_ENUM_IS_WRAPPED(GstActivateMode)
_ENUM_IS_WRAPPED(GstAssocFlags)
_ENUM_IS_WRAPPED(GstAutoplugSelectResult)
_ENUM_IS_WRAPPED(GstBufferCopyFlags)
_ENUM_IS_WRAPPED(GstBufferFlag)
_ENUM_IS_WRAPPED(GstBufferingMode)
_ENUM_IS_WRAPPED(GstBusFlags)
_ENUM_IS_WRAPPED(GstBusSyncReply)
_ENUM_IS_WRAPPED(GstClockEntryType)
_ENUM_IS_WRAPPED(GstClockFlags)
_ENUM_IS_WRAPPED(GstClockReturn)
_ENUM_IS_WRAPPED(GstColorBalanceType)
_ENUM_IS_WRAPPED(GstElementFlags)
_ENUM_IS_WRAPPED(GstEventType)
_ENUM_IS_WRAPPED(GstEventTypeFlags)
_ENUM_IS_WRAPPED(GstFlowReturn)
_ENUM_IS_WRAPPED(GstFormat)
_ENUM_IS_WRAPPED(GstIndexCertainty)
_ENUM_IS_WRAPPED(GstIndexEntryType)
_ENUM_IS_WRAPPED(GstIndexFlags)
_ENUM_IS_WRAPPED(GstIndexLookupMethod)
_ENUM_IS_WRAPPED(GstIndexResolverMethod)
_ENUM_IS_WRAPPED(GstIteratorItem)
_ENUM_IS_WRAPPED(GstIteratorResult)
_ENUM_IS_WRAPPED(GstMessageType)
_ENUM_IS_WRAPPED(GstMiniObjectFlags)
_ENUM_IS_WRAPPED(GstPadDirection)
_ENUM_IS_WRAPPED(GstPadFlags)
_ENUM_IS_WRAPPED(GstPadLinkReturn)
_ENUM_IS_WRAPPED(GstPadPresence)
_ENUM_IS_WRAPPED(GstPadTemplateFlags)
_ENUM_IS_WRAPPED(GstQueryType)
_ENUM_IS_WRAPPED(GstRank)
_ENUM_IS_WRAPPED(GstSeekFlags)
_ENUM_IS_WRAPPED(GstSeekType)
_ENUM_IS_WRAPPED(GstState)
_ENUM_IS_WRAPPED(GstStateChange)
_ENUM_IS_WRAPPED(GstStateChangeReturn)
_ENUM_IS_WRAPPED(GstTagFlag)
_ENUM_IS_WRAPPED(GstTagMergeMode)
_ENUM_IS_WRAPPED(GstTaskState)
_ENUM_IS_WRAPPED(GstTCPProtocol)
_ENUM_IS_WRAPPED(GstURIType)

include(ctocpp.m4)
divert(0)dnl

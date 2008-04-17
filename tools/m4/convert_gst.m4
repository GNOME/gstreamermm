dnl 
dnl Glib C names have prefix 'G' but C++ namespace Glib
dnl 
define(`_CONV_GST_ENUM',`dnl
_CONVERSION(`GST$1', `$1', (($1)(__ARG3__)))
_CONVERSION(`GST$1', `$1', ((Glib::$1)(__ARG3__)))
_CONVERSION(`$1', `GST$1', ((GST$1)(__ARG3__)))
_CONVERSION(`$1', `GST$1', ((GST$1)(__ARG3__)))
')dnl

###############Gstreamermm Class Conversions######################

#Gst::Object
_CONVERSION(`GstObject*',`Glib::RefPtr<Gst::Object>',`Glib::wrap($3)')
_CONVERSION(`GstObject*',`Glib::RefPtr<const Gst::Object>',`Glib::wrap($3)')
_CONVERSION(`const Glib::RefPtr<Gst::Object>&',`GstObject*',`Glib::unwrap($3)')
_CONVERSION(`Glib::RefPtr<Gst::Object>',`GstObject*',`Glib::unwrap($3)')

#Buffer
_CONVERSION(`GstBuffer*',`Glib::RefPtr<Buffer>',`wrap($3)')
_CONVERSION(`const Glib::RefPtr<Buffer>&',`GstBuffer*', `Glib::unwrap($3)')
_CONVERSION(`const Glib::RefPtr<Buffer>&',`const GstBuffer*', `Glib::unwrap($3)')
_CONVERSION(`Glib::RefPtr<Buffer>',`GstBuffer*', `Glib::unwrap($3)')

#Bus
_CONVERSION(`const Glib::RefPtr<Bus>&',`GstBus*', `Glib::unwrap($3)')
_CONVERSION(`GstBus*',`Glib::RefPtr<Bus>',`Glib::wrap($3)')
_CONVERSION(`GstBus*',`const Glib::RefPtr<Bus>&',`Glib::wrap($3)')

#Caps
_CONVERSION(`GstCaps*',`Glib::RefPtr<Caps>',`Glib::wrap($3)')
_CONVERSION(`const Glib::RefPtr<Caps>&',`GstCaps*', `Glib::unwrap($3)')
_CONVERSION(`const Glib::RefPtr<Caps>&',`const GstCaps*', `Glib::unwrap($3)')
_CONVERSION(`const Glib::RefPtr<const Caps>&',`const GstCaps*', `Glib::unwrap($3)')

#Clock
_CONVERSION(`GstClock*',`Glib::RefPtr<Clock>',`Glib::wrap($3)')
_CONVERSION(`GstClock*',`Glib::RefPtr<const Clock>',`Glib::wrap($3)')
_CONVERSION(`const Glib::RefPtr<Clock>&',`GstClock*', `Glib::unwrap($3)')
_CONVERSION(`const Clock&',`GstClock*',`((GstClock*) (&($3)))')
_CONVERSION(`Glib::RefPtr<Clock>',`GstClock*', `Glib::unwrap($3)')
_CONVERSION(`GstClock*',`const Glib::RefPtr<Clock>&',`Glib::wrap($3)')

#ClockID
_CONVERSION(`GstClockID',`Glib::RefPtr<ClockID>',`Glib::wrap((GstClockEntry*)($3))')
_CONVERSION(`const Glib::RefPtr<ClockID>&',`GstClockEntry*',`($3)->gobj()')
_CONVERSION(`GstClockEntry*',`const Glib::RefPtr<ClockID>&',`Glib::wrap($3)')

#Element
_CONVERSION(`Glib::RefPtr<Element>',`GstElement*', `Glib::unwrap($3)')
_CONVERSION(`GstElement*',`Glib::RefPtr<Element>',`Glib::wrap($3)')
_CONVERSION(`GstElement*',`Glib::RefPtr<const Element>',`Glib::wrap($3)')
_CONVERSION(`const Glib::RefPtr<Element>&',`GstElement*', `Glib::unwrap($3)')
_CONVERSION(`const Glib::RefPtr<const Element>&',`GstElement*', `const_cast<GstElement*>(Glib::unwrap($3))')
_CONVERSION(`State&',`GstState*',`((GstState*) (&($3)))')

#ElementFactory
_CONVERSION(`GstElementFactory*',`Glib::RefPtr<ElementFactory>',`Glib::wrap($3)')

#Event
_CONVERSION(`const Glib::RefPtr<Event>&',`GstEvent*', `Gst::unwrap($3)')
_CONVERSION(`GstEvent*',`const Glib::RefPtr<Event>&', `Gst::wrap($3)')

#Index
_CONVERSION(`GstIndex*',`Glib::RefPtr<Index>',`Glib::wrap($3)')
_CONVERSION(`const Glib::RefPtr<Index>&',`GstIndex*',`Glib::unwrap($3)')
_CONVERSION(`const IndexAssociation&',`const GstIndexAssociation*',`((GstIndexAssociation*)(&($3)))')
_CONVERSION(`GstIndex*',`const Glib::RefPtr<Index>&',`Glib::wrap($3)')
_CONVERSION(`Glib::RefPtr<Index>',`GstIndex*',`Glib::unwrap($3)')

#IndexEntry
_CONVERSION(`GstIndexEntry*',`IndexEntry',`Glib::wrap($3)')
_CONVERSION(`GstIndexEntry*',`const IndexEntry&',`Glib::wrap($3)')
_CONVERSION(`const IndexEntry&',`GstIndexEntry*',`const_cast<GstIndexEntry*>(($3).gobj())')

#IndexFactory
_CONVERSION(`GstIndexFactory*',`Glib::RefPtr<IndexFactory>',`Glib::wrap($3)')

#Message
_CONVERSION(`GstMessage*',`Glib::RefPtr<Message>',`Gst::Message::wrap($3)')
_CONVERSION(`GstMessage*',`Glib::RefPtr<const Message>',`Gst::Message::wrap($3)')
_CONVERSION(`const Glib::RefPtr<Message>&',`GstMessage*', `Glib::unwrap($3)')
_CONVERSION(`GstMessage*',`const Glib::RefPtr<Message>&',`Gst::Message::wrap($3)')

#Pad
_CONVERSION(`GstPad*',`Glib::RefPtr<Pad>',`Glib::wrap($3)')
_CONVERSION(`GstPad*',`Glib::RefPtr<const Pad>',`Glib::wrap($3)')
_CONVERSION(`Glib::RefPtr<Pad>',`GstPad*', `Glib::unwrap($3)')
_CONVERSION(`const Glib::RefPtr<Pad>&',`GstPad*', `Glib::unwrap($3)')

#PadTemplate
_CONVERSION(`const Glib::RefPtr<PadTemplate>&',`GstPadTemplate*', `Glib::unwrap($3)')
_CONVERSION(`GstPadTemplate*',`Glib::RefPtr<PadTemplate>', `Glib::wrap($3)')
_CONVERSION(`GstPadTemplate*',`const Glib::RefPtr<PadTemplate>&', `Glib::wrap($3)')

#Plugin
_CONVERSION(`const Glib::RefPtr<Plugin>&',`GstPlugin*',`Glib::unwrap($3)')
_CONVERSION(`GstPlugin*',`Glib::RefPtr<Plugin>',`Glib::wrap($3)')
_CONVERSION(`GstPlugin*',`const Glib::RefPtr<Plugin>&',`Glib::wrap($3)')

#PluginFeature
_CONVERSION(`GstPluginFeature*',`Glib::RefPtr<PluginFeature>',`Glib::wrap($3)')
_CONVERSION(`const Glib::RefPtr<PluginFeature>&',`GstPluginFeature*',`Glib::unwrap($3)')
_CONVERSION(`GstPluginFeature*',`const Glib::RefPtr<PluginFeature>&',`Glib::wrap($3)')

#Query
_CONVERSION(`const Glib::RefPtr<Query>&',`GstQuery*', `Gst::unwrap($3)')
_CONVERSION(`GstQuery*',`const Glib::RefPtr<Query>&', `Gst::wrap($3)')

#Registry
_CONVERSION(`GstRegistry*',`Glib::RefPtr<Registry>', `Glib::wrap($3)')

#Structure
_CONVERSION(`Structure&',`GstStructure*',`(($3).gobj())')

#TagList
_CONVERSION(`const TagList&',`const GstTagList*',`(($3).gobj())')
_CONVERSION(`GstTagList*',`TagList',`Glib::wrap($3)')

#URIHandler
_CONVERSION(`const Glib::RefPtr<URIHandler>&',`GstURIHandler*',`Glib::unwrap($3)')

###################General Conversions############################

#Basic General Conversions
_CONVERSION(`gint64&',`gint64*',`&($3)')
_CONVERSION(`bool&',`gboolean*',`(($2) &($3))')
_CONVERSION(`const guint&',`guint',`$3')
_CONVERSION(`const guint32&',`guint32',`$3')

#Basic Gstreamermm Conversions
_CONVERSION(`ClockTimeDiff',`GstClockTimeDiff',`GstClockTimeDiff ($3)')
_CONVERSION(`ClockTimeDiff&',`GstClockTimeDiff*',`(GstClockTimeDiff*)(&($3))')
_CONVERSION(`Format&',`GstFormat*',`(($2) &($3))')
_CONVERSION(`GstClockTimeDiff*',`ClockTimeDiff&',`(ClockTimeDiff&)(*($3))')
_CONVERSION(`const GstQueryType*',`const QueryType*',`(QueryType*)($3)')
_CONVERSION(`GstState*',`State&',`(State&)($3)')
_CONVERSION(`GstTagFlag',`TagFlag',`(TagFlag)($3)')
_CONVERSION(`guint64',`ClockTime',`(ClockTime ($3))')
_CONVERSION(`const URIType',`const GstURIType',`(GstURIType($3))')

#C++ Conversions
_CONVERSION(`const va_list&',`va_list',`const_cast<va_list&>($3)')

#Glibmm Conversions
_CONVERSION(`GQuark',`Glib::QueryQuark',`Glib::QueryQuark($3)')
_CONVERSION(`const Glib::QueryQuark&',`GQuark',`$3')
_CONVERSION(`Glib::StaticRecMutex&',`GStaticRecMutex*',`($3).gobj()')

#List Conversions
_CONVERSION(`Glib::ListHandle< Glib::RefPtr<Plugin> >',`GList*',`($3).data()')
_CONVERSION(`Glib::ListHandle< Glib::RefPtr<PluginFeature> >',`GList*',`($3).data()')
_CONVERSION(`gchar**',`Glib::StringArrayHandle',`Glib::StringArrayHandle($3)')

#String Conversions
_CONVERSION(`const std::string&',`const guchar*',`(const guchar*) ($3.c_str())')
_CONVERSION(`gchar*',`const Glib::ustring&',__GCHARP_TO_USTRING)
_CONVERSION(`const gchar*',`const Glib::ustring&',__GCHARP_TO_USTRING)

#Other Conversions
_CONVERSION(`const xmlNodePtr&',`xmlNodePtr',`$3')

#############################Enums####################################

_CONV_ENUM(Gst,AssocFlags)
_CONV_ENUM(Gst,BufferCopyFlags)
_CONV_ENUM(Gst,BufferFlag)
_CONV_ENUM(Gst,ClockEntryType)
_CONV_ENUM(Gst,ClockReturn)
_CONV_ENUM(Gst,ClockTime)
_CONV_ENUM(Gst,EventType)
_CONV_ENUM(Gst,FlowReturn)
_CONV_ENUM(Gst,Format)
_CONV_ENUM(Gst,IndexCertainty)
_CONV_ENUM(Gst,IndexEntryType)
_CONV_ENUM(Gst,IndexFlags)
_CONV_ENUM(Gst,IndexLookupMethod)
_CONV_ENUM(Gst,IndexResolverMethod)
_CONV_ENUM(Gst,MessageType)
_CONV_ENUM(Gst,PadDirection)
_CONV_ENUM(Gst,PadLinkReturn)
_CONV_ENUM(Gst,PadPresence)
_CONV_ENUM(Gst,QueryType)
_CONV_ENUM(Gst,SeekFlags)
_CONV_ENUM(Gst,SeekType)
_CONV_ENUM(Gst,State)
_CONV_ENUM(Gst,StateChange)
_CONV_ENUM(Gst,StateChangeReturn)
_CONV_ENUM(Gst,TagMergeMode)
_CONV_ENUM(Gst,TaskState)
_CONV_ENUM(Gst,URIType)

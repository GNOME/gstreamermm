dnl 
dnl Glib C names have prefix 'G' but C++ namespace Glib
dnl 
define(`_CONV_GST_ENUM',`dnl
_CONVERSION(`GST$1', `$1', (($1)(__ARG3__)))
_CONVERSION(`GST$1', `$1', ((Glib::$1)(__ARG3__)))
_CONVERSION(`$1', `GST$1', ((GST$1)(__ARG3__)))
_CONVERSION(`$1', `GST$1', ((GST$1)(__ARG3__)))
')dnl

#Gst::Object
_CONVERSION(`GstObject*',`Glib::RefPtr<Gst::Object>',`Glib::wrap($3)')
_CONVERSION(`GstObject*',`Glib::RefPtr<const Gst::Object>',`Glib::wrap($3)')
_CONVERSION(`const Glib::RefPtr<Gst::Object>&',`GstObject*',`Glib::unwrap($3)')
_CONVERSION(`GstObject*',`const Glib::RefPtr<Gst::Object>&',`Glib::wrap($3)')

#Buffer
_CONVERSION(`GstBuffer*',`Glib::RefPtr<Buffer>',`wrap($3)')
_CONVERSION(`const Glib::RefPtr<Buffer>&',`GstBuffer*', `Glib::unwrap($3)')
_CONVERSION(`const Glib::RefPtr<Buffer>&',`const GstBuffer*', `Glib::unwrap($3)')
_CONVERSION(`Glib::RefPtr<Buffer>',`GstBuffer*', `Glib::unwrap($3)')

#Bus
_CONVERSION(`const Glib::RefPtr<Bus>&',`GstBus*', `Glib::unwrap($3)')
_CONVERSION(`GstBus*',`Glib::RefPtr<Bus>',`Glib::wrap($3)')

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

#ClockID
_CONVERSION(`GstClockID',`Glib::RefPtr<ClockID>',`$3')
_CONVERSION(`Glib::RefPtr<ClockID>',`GstClockID',`(GstClockID ($3))')

#Element
_CONVERSION(`Glib::RefPtr<Element>',`GstElement*', `Glib::unwrap($3)')
_CONVERSION(`GstElement*',`Glib::RefPtr<Element>',`Glib::wrap($3)')
_CONVERSION(`GstElement*',`Glib::RefPtr<const Element>',`Glib::wrap($3)')
_CONVERSION(`const Glib::RefPtr<Element>&',`GstElement*', `Glib::unwrap($3)')
_CONVERSION(`State&',`GstState*',`((GstState*) (&($3)))')

#ElementFactory
_CONVERSION(`GstElementFactory*',`Glib::RefPtr<ElementFactory>',`Glib::wrap($3)')

#Event
_CONVERSION(`const Glib::RefPtr<Event>&',`GstEvent*', `Glib::unwrap($3)')

#Index
_CONVERSION(`GstIndexEntry*',`IndexEntry',`Glib::wrap($3)')
_CONVERSION(`const IndexAssociation&',`const GstIndexAssociation*',`((GstIndexAssociation*)(&($3)))')
_CONVERSION(`GstIndex*',`Glib::RefPtr<Index>',`Glib::wrap($3)')

#IndexFactory
_CONVERSION(`GstIndexFactory*',`Glib::RefPtr<IndexFactory>',`Glib::wrap($3)')

#Message
_CONVERSION(`GstMessage*',`Glib::RefPtr<Message>',`Gst::Message::wrap($3)')
_CONVERSION(`GstMessage*',`Glib::RefPtr<const Message>',`Gst::Message::wrap($3)')
_CONVERSION(`const Glib::RefPtr<Message>&',`GstMessage*', `Glib::unwrap($3)')

#Pad
_CONVERSION(`GstPad*',`Glib::RefPtr<Pad>',`Glib::wrap($3)')
_CONVERSION(`GstPad*',`Glib::RefPtr<const Pad>',`Glib::wrap($3)')
#_CONVERSION(`Glib::RefPtr<Pad>',`GstPad*', `Glib::unwrap($3)')
_CONVERSION(`const Glib::RefPtr<Pad>&',`GstPad*', `Glib::unwrap($3)')

#Plugin
_CONVERSION(`const Glib::RefPtr<Plugin>&',`GstPlugin*',`Glib::unwrap($3)')
_CONVERSION(`GstPlugin*',`Glib::RefPtr<Plugin>',`Glib::wrap($3)')
_CONVERSION(`Glib::ListHandle< Glib::RefPtr<Plugin> >',`GList*',`($3).data()')

#PluginFeature
_CONVERSION(`const TypeNameData&',`GstTypeNameData*',`($2)(&($3))')
_CONVERSION(`GstPluginFeature*',`Glib::RefPtr<PluginFeature>',`Glib::wrap($3)')
_CONVERSION(`Glib::ListHandle< Glib::RefPtr<PluginFeature> >',`GList*',`($3).data()')

#Query
_CONVERSION(`const Glib::RefPtr<Query>&',`GstQuery*', `Glib::unwrap($3)')

#Structure
_CONVERSION(`Structure&',`GstStructure*',`((GstStructure*)(&($3)))')
_CONVERSION(`GstStructure*',`Structure*',`((Structure*) ($3))')

#General Conversions
_CONVERSION(`guint64',`ClockTime',`(ClockTime ($3))')
_CONVERSION(`Format&',`GstFormat*',`(($2) &($3))')
_CONVERSION(`gint64&',`gint64*',`&($3)')
_CONVERSION(`const guint&',`guint',`$3')
_CONVERSION(`const guint32&',`guint32',`$3')
_CONVERSION(`const std::string&',`const guchar*',`(const guchar*) ($3.c_str())')
_CONVERSION(`const va_list&',`va_list',`const_cast<va_list&>($3)')
_CONVERSION(`const xmlNodePtr&',`xmlNodePtr',`$3')
_CONVERSION(`GQuark',`Glib::QueryQuark',`Glib::QueryQuark($3)')
_CONVERSION(`const Glib::QueryQuark&',`GQuark',`$3')
_CONVERSION(`gchar**',`Glib::StringArrayHandle',`Glib::StringArrayHandle($3)')

_CONV_ENUM(Gst,AssocFlags)
_CONV_ENUM(Gst,BufferCopyFlags)
_CONV_ENUM(Gst,BufferFlag)
_CONV_ENUM(Gst,ClockEntryType)
_CONV_ENUM(Gst,ClockReturn)
_CONV_ENUM(Gst,ClockTime)
_CONV_ENUM(Gst,EventType)
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

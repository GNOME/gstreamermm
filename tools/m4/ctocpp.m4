#Enums
_CCONVERSION(`GstFormat',`Gst::Format',`Gst::Format')
_CCONVERSION(`GstTCPProtocol',`Gst::TCPProtocol',`Gst::TCPProtocol')

#giomm
_CCONVERSION(`GFile*',`Gio::File',`const Glib::RefPtr<Gio::File>&',`Glib::RefPtr<Gio::File>',`<giomm/file.h>')
_CCONVERSION(`GInputStream*',`Gio::InputStream',`const Glib::RefPtr<Gio::InputStream>&',`Glib::RefPtr<Gio::InputStream>',`<giomm/inputstream.h>')
_CCONVERSION(`GOutputStream*',`Gio::OutputStream',`const Glib::RefPtr<Gio::OutputStream>&',`Glib::RefPtr<Gio::OutputStream>',`<giomm/outputstream.h>')

#gstreamermm
_CCONVERSION(`GstBuffer*',`Gst::Buffer',`const Glib::RefPtr<Gst::Buffer>&',`Glib::RefPtr<Gst::Buffer>',`<gstreamermm/buffer.h>')
_CCONVERSION(`GstCaps*',`Gst::Caps',`const Glib::RefPtr<Gst::Caps>&',`Glib::RefPtr<Gst::Caps>',`<gstreamermm/caps.h>')
_CCONVERSION(`GstElement*',`Gst::Element',`const Glib::RefPtr<Gst::Element>&',`Glib::RefPtr<Gst::Element>',`<gstreamermm/element.h>')
_CCONVERSION(`GstPad*',`Gst::Pad',`const Glib::RefPtr<Gst::Pad>&',`Glib::RefPtr<Gst::Pad>',`<gstreamermm/pad.h>')
_CCONVERSION(`GstTagList*',`Gst::TagList',`Gst::TagList',,`<gstreamermm/taglist.h>')

#Interfaces
_CCONVERSION(`GstColorBalance*',`Gst::ColorBalance',`const Glib::RefPtr<Gst::ColorBalance>&',`Glib::RefPtr<Gst::ColorBalance>',`<gstreamermm/colorbalance.h>')
_CCONVERSION(`GstImplementsInterface*',`Gst::Interface',`const Glib::RefPtr<Gst::Interface>&',`Glib::RefPtr<Gst::Interface>',`<gstreamermm/interface.h>')
_CCONVERSION(`GstMixer*',`Gst::Mixer',`const Glib::RefPtr<Gst::Mixer>&',`Glib::RefPtr<Gst::Mixer>',`<gstreamermm/mixer.h>')
_CCONVERSION(`GstNavigation*',`Gst::Navigation',`const Glib::RefPtr<Gst::Navigation>&',`Glib::RefPtr<Gst::Navigation>',`<gstreamermm/navigation.h>')
_CCONVERSION(`GstPropertyProbe*',`Gst::PropertyProbe',`const Glib::RefPtr<Gst::PropertyProbe>&',`Glib::RefPtr<Gst::PropertyProbe>',`<gstreamermm/propertyprobe.h>')
_CCONVERSION(`GstTagSetter*',`Gst::TagSetter',`const Glib::RefPtr<Gst::TagSetter>&',`Glib::RefPtr<Gst::TagSetter>',`<gstreamermm/tagsetter.h>')
_CCONVERSION(`GstURIHandler*',`Gst::URIHandler',`const Glib::RefPtr<Gst::URIHandler>&',`Glib::RefPtr<Gst::URIHandler>',`<gstreamermm/urihandler.h>')
_CCONVERSION(`GstXOverlay*',`Gst::XOverlay',`const Glib::RefPtr<Gst::XOverlay>&',`Glib::RefPtr<Gst::XOverlay>',`<gstreamermm/xoverlay.h>')

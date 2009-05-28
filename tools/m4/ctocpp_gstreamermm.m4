# Translations from C to C++ types for plug-in generation.  See the
# ctocpp_base.m4 file for documentation.

#Enums
_TRANSLATION(`GstFormat',`Gst::Format',`Gst::Format',,`<gstreamermm/format.h>')
_TRANSLATION(`GstTCPProtocol',`Gst::TCPProtocol',`Gst::TCPProtocol',,`<gstreamermm/enums.h>')

#giomm
_TRANSLATION(`GFile*',`Gio::File',`const Glib::RefPtr<Gio::File>&',`Glib::RefPtr<Gio::File>',`<giomm/file.h>')
_TRANSLATION(`GInputStream*',`Gio::InputStream',`const Glib::RefPtr<Gio::InputStream>&',`Glib::RefPtr<Gio::InputStream>',`<giomm/inputstream.h>')
_TRANSLATION(`GOutputStream*',`Gio::OutputStream',`const Glib::RefPtr<Gio::OutputStream>&',`Glib::RefPtr<Gio::OutputStream>',`<giomm/outputstream.h>')

#gstreamermm
_TRANSLATION(`GstBuffer*',`Gst::Buffer',`const Glib::RefPtr<Gst::Buffer>&',`Glib::RefPtr<Gst::Buffer>',`<gstreamermm/buffer.h>')
_TRANSLATION(`GstCaps*',`Gst::Caps',`const Glib::RefPtr<Gst::Caps>&',`Glib::RefPtr<Gst::Caps>',`<gstreamermm/caps.h>')
_TRANSLATION(`GstElement*',`Gst::Element',`const Glib::RefPtr<Gst::Element>&',`Glib::RefPtr<Gst::Element>',`<gstreamermm/element.h>')
_TRANSLATION(`GstPad*',`Gst::Pad',`const Glib::RefPtr<Gst::Pad>&',`Glib::RefPtr<Gst::Pad>',`<gstreamermm/pad.h>')
_TRANSLATION(`GstTagList*',`Gst::TagList',`Gst::TagList',,`<gstreamermm/taglist.h>')

#Interfaces
_TRANSLATION(`GstColorBalance*',`Gst::ColorBalance',`const Glib::RefPtr<Gst::ColorBalance>&',`Glib::RefPtr<Gst::ColorBalance>',`<gstreamermm/colorbalance.h>')
_TRANSLATION(`GstImplementsInterface*',`Gst::Interface',`const Glib::RefPtr<Gst::Interface>&',`Glib::RefPtr<Gst::Interface>',`<gstreamermm/interface.h>')
_TRANSLATION(`GstMixer*',`Gst::Mixer',`const Glib::RefPtr<Gst::Mixer>&',`Glib::RefPtr<Gst::Mixer>',`<gstreamermm/mixer.h>')
_TRANSLATION(`GstNavigation*',`Gst::Navigation',`const Glib::RefPtr<Gst::Navigation>&',`Glib::RefPtr<Gst::Navigation>',`<gstreamermm/navigation.h>')
_TRANSLATION(`GstPropertyProbe*',`Gst::PropertyProbe',`const Glib::RefPtr<Gst::PropertyProbe>&',`Glib::RefPtr<Gst::PropertyProbe>',`<gstreamermm/propertyprobe.h>')
_TRANSLATION(`GstTagSetter*',`Gst::TagSetter',`const Glib::RefPtr<Gst::TagSetter>&',`Glib::RefPtr<Gst::TagSetter>',`<gstreamermm/tagsetter.h>')
_TRANSLATION(`GstURIHandler*',`Gst::URIHandler',`const Glib::RefPtr<Gst::URIHandler>&',`Glib::RefPtr<Gst::URIHandler>',`<gstreamermm/urihandler.h>')
_TRANSLATION(`GstXOverlay*',`Gst::XOverlay',`const Glib::RefPtr<Gst::XOverlay>&',`Glib::RefPtr<Gst::XOverlay>',`<gstreamermm/xoverlay.h>')

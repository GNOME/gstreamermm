#Enums
_CCONVERSION(`GstFormat',`Gst::Format')

#giomm
_CCONVERSION(`GFile*',`const Glib::RefPtr<Gio::File>&',`Glib::RefPtr<Gio::File>',`<giomm/file.h>')
_CCONVERSION(`GInputStream*',`const Glib::RefPtr<Gio::InputStream>&',`Glib::RefPtr<Gio::InputStream>',`<giomm/inputstream.h>')
_CCONVERSION(`GOutputStream*',`const Glib::RefPtr<Gio::OutputStream>&',`Glib::RefPtr<Gio::OutputStream>',`<giomm/outputstream.h>')

#gstreamermm
_CCONVERSION(`GstBuffer*',`const Glib::RefPtr<Gst::Buffer>&',`Glib::RefPtr<Gst::Buffer>',`<gstreamermm/buffer.h>')
_CCONVERSION(`GstCaps*',`const Glib::RefPtr<Gst::Caps>&',`Glib::RefPtr<Gst::Caps>',`<gstreamermm/caps.h>')
_CCONVERSION(`GstElement*',`const Glib::RefPtr<Gst::Element>&',`Glib::RefPtr<Gst::Element>',`<gstreamermm/element.h>')
_CCONVERSION(`GstPad*',`const Glib::RefPtr<Gst::Pad>&',`Glib::RefPtr<Gst::Pad>',`<gstreamermm/pad.h>')
_CCONVERSION(`GstTagList*',`Gst::TagList',,`<gstreamermm/taglist.h>')


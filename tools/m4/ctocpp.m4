#Enums
_CCONVERSION(`GstFormat',`Gst::Format')

#Reference counted
_CCONVERSION(`GstBuffer*',`const Glib::RefPtr<Gst::Buffer>&',`Glib::RefPtr<Gst::Buffer>',`<gstreamermm/buffer.h>')
_CCONVERSION(`GstCaps*',`const Glib::RefPtr<Gst::Caps>&',`Glib::RefPtr<Gst::Caps>',`<gstreamermm/caps.h>')
_CCONVERSION(`GstElement*',`const Glib::RefPtr<Gst::Element>&',`Glib::RefPtr<Gst::Element>',`<gstreamermm/element.h>')
_CCONVERSION(`GstPad*',`const Glib::RefPtr<Gst::Pad>&',`Glib::RefPtr<Gst::Pad>',`<gstreamermm/pad.h>')
_CCONVERSION(`GstTagList*',`Gst::TagList',,`<gstreamermm/taglist.h>')

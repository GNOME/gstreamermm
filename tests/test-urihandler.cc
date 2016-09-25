/*
 * test-urihandler.cc
 *
 *  Created on: May 16, 2014
 *      Author: m.kolny
 */
#include "mmtest.h"
#include <gstreamermm.h>
#include <gstreamermm/private/element_p.h>

using namespace Gst;

class UriTestElement: public URIHandler, public Gst::Element {
public:
  typedef Gst::Element::BaseClassType BaseClassType;
  typedef Gst::Element::BaseObjectType BaseObjectType;
  typedef Gst::Element::CppClassType CppClassType;

public:
  static GType get_base_type() G_GNUC_CONST
  {
    return Element::get_base_type();
  }

  static void class_init(Gst::ElementClass<UriTestElement> *klass)
  {
    klass->set_metadata("uri_longname", "uri_classification",
        "uri_detail_description", "uri_detail_author");
  }

  explicit UriTestElement(GstElement *gobj)
  : Glib::ObjectBase(typeid(UriTestElement)),
    Gst::Element(gobj)
  {
  }

  bool set_uri_vfunc(const Glib::ustring& /* uri */, GError** /* error */)
  {
    return true;
  }

  const gchar * const * get_protocols_vfunc() const
  {
    static const gchar* vect[] = { "dummyprotocol", NULL };

    return vect;
  }

  URIType get_type_vfunc() override
  {
    return URI_SINK;
  }

  static bool register_uritestelement(Glib::RefPtr<Gst::Plugin> plugin)
  {
    auto t = Gst::register_mm_type<UriTestElement>("uritestelement");
    add_interface(t);

    return Gst::ElementFactory::register_element(plugin, "uritestelement", 10, t);
  }
};

TEST(URIHandlerTest, CheckURIType)
{
  Plugin::register_static(GST_VERSION_MAJOR, GST_VERSION_MINOR, "uritestelement", "uritestelement is example of C++ element",
      sigc::ptr_fun(&UriTestElement::register_uritestelement), "0.123", "LGPL", "source?", "package?",
      "http://example.com");

  Glib::ustring factory_name =
      URIHandler::make_element_from_uri(URI_SINK, "dummyprotocol:some/path", "dummy_name")->get_factory()->get_name();

  ASSERT_STREQ("uritestelement", factory_name.c_str());
}

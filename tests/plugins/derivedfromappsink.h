#ifndef TEST_DERIVEDFROMAPPSINK_H_
#define TEST_DERIVEDFROMAPPSINK_H_

#include <gst/app/gstappsink.h>
#include <gstreamermm.h>
#include <gstreamermm/private/appsink_p.h>
#include <assert.h>

class DerivedFromAppSink : public Gst::AppSink
{
public:
  static void class_init(Gst::ElementClass<DerivedFromAppSink> *klass)
  {
    klass->set_metadata("derivedfromappsink_longname",
            "derivedfromappsink_classification", "derivedfromappsink_detail_description", "derivedfromappsink_detail_author");
  }

  explicit DerivedFromAppSink(GstAppSink *gobj)
  : Glib::ObjectBase(typeid (DerivedFromAppSink)), // type must be registered before use
    Gst::AppSink(gobj)
  {
  }

  static bool register_element(Glib::RefPtr<Gst::Plugin> plugin)
  {
    return Gst::ElementFactory::register_element(plugin, "derivedfromappsink", 10, Gst::register_mm_type<DerivedFromAppSink>("derivedfromappsink"));
  }
};

#endif /* TEST_DERIVEDFROMAPPSINK_H_ */

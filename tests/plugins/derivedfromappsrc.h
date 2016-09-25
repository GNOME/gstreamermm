#ifndef TESTS_PLUGINS_DERIVEDFROMAPPSRC_H_
#define TESTS_PLUGINS_DERIVEDFROMAPPSRC_H_

#include <gst/app/gstappsrc.h>
#include <gstreamermm.h>
#include <gstreamermm/private/appsrc_p.h>
#include <assert.h>

class DerivedFromAppSrc : public Gst::AppSrc
{
public:
  static void class_init(Gst::ElementClass<DerivedFromAppSrc> *klass)
  {
    klass->set_metadata("derivedfromappsrc_longname",
          "derivedfromappsrc_classification", "derivedfromappsrc_detail_description", "derivedfromappsrc_detail_author");
  }

  explicit DerivedFromAppSrc(GstAppSrc *gobj)
  : Glib::ObjectBase(typeid (DerivedFromAppSrc)), // type must be registered before use
    Gst::AppSrc(gobj)
  {
  }

  static bool register_element(Glib::RefPtr<Gst::Plugin> plugin)
  {
    return Gst::ElementFactory::register_element(plugin, "derivedfromappsrc", 10, Gst::register_mm_type<DerivedFromAppSrc>("derivedfromappsrc"));
  }
};

#endif /* TESTS_PLUGINS_DERIVEDFROMAPPSRC_H_ */

#ifndef TESTS_PLUGINS_DERIVEDFROMBASETRANSFORM_H_
#define TESTS_PLUGINS_DERIVEDFROMBASETRANSFORM_H_

#include <gstreamermm.h>
#include <gstreamermm/private/basetransform_p.h>
#include <assert.h>

class DerivedFromBaseTransform : public Gst::BaseTransform
{
public:
  static void class_init(Gst::ElementClass<DerivedFromBaseTransform> *klass)
  {
    klass->set_metadata("derivedfrombasetransform_longname",
          "derivedfrombasetransform_classification", "derivedfrombasetransform_detail_description", "derivedfrombasetransform_detail_author");

    klass->add_pad_template(Gst::PadTemplate::create("sink", Gst::PAD_SINK, Gst::PAD_ALWAYS, Gst::Caps::create_any()));
    klass->add_pad_template(Gst::PadTemplate::create("src", Gst::PAD_SRC, Gst::PAD_ALWAYS, Gst::Caps::create_any()));
  }

  explicit DerivedFromBaseTransform(GstBaseTransform *gobj)
  : Glib::ObjectBase(typeid (DerivedFromBaseTransform)), // type must be registered before use
    Gst::BaseTransform(gobj)
  {
    set_passthrough(true);
  }

  static bool register_element(Glib::RefPtr<Gst::Plugin> plugin)
  {
    return Gst::ElementFactory::register_element(plugin, "derivedfrombasetransform", 10, Gst::register_mm_type<DerivedFromBaseTransform>("derivedfrombasetransform"));
  }
};

#endif /* TESTS_PLUGINS_DERIVEDFROMBASETRANSFORM_H_ */

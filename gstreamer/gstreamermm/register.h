/* gstreamermm - a C++ wrapper for gstreamer
 *
 * Copyright 2008 The gstreamermm Development Team
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free
 * Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#ifndef REGISTER_H_
#define REGISTER_H_

#include <glib-object.h>
#include <glibmm/property.h>
#include <glibmm/init.h>
#include <gstreamermm/padtemplate.h>

namespace Gst
{

template<class DerivedCppType>
static GType
register_mm_type(const gchar * type_name=typeid(DerivedCppType).name());

template<typename DerivedCppType>
class ElementClass
{
  friend GType register_mm_type<DerivedCppType>(const gchar * type_name);
  GstElementClass* klass;
  ElementClass(typename DerivedCppType::BaseClassType* klass): klass((GstElementClass*) klass){}
  ElementClass(ElementClass const&);
  void operator=(ElementClass const&);
public:
  void add_pad_template(const Glib::RefPtr<Gst::PadTemplate>& tpl)
  {
    gst_element_class_add_pad_template(klass, tpl->gobj());
  }
  void set_metadata(const Glib::ustring& longname, const Glib::ustring& classification,
                    const Glib::ustring& description, const Glib::ustring& author)
  {
    gst_element_class_set_metadata(klass, longname.c_str(), classification.c_str(), description.c_str(), author.c_str());
  }

  void add_metadata(const Glib::ustring& key, const Glib::ustring& value)
  {
  	gst_element_class_add_metadata(klass ,key.c_str(), value.c_str());
  }

  const GstElementClass* gobj() const { return klass; }
  GstElementClass* gobj() { return klass; }
};

template<class DerivedCppType>
static GType
register_mm_type(const gchar * type_name)
{
    struct GlibCppType
    {
        typename DerivedCppType::BaseObjectType parent;
        DerivedCppType *self;
        static void init(GlibCppType *instance, gpointer /* g_class */)
        {
            //instance->parent will be passed to C++ base of DerivedCppType; this will cause registerging "self" as MM wrapper of "parent"
            Gst::init();
            instance->self = new DerivedCppType(&instance->parent);
        }

        static void finalize(GObject *object)
        {
            //the following will destroy q_data, among which MM wrapper to this "object" is stored. This will cause implicit delete on "self", since it is registered as wrapper of "object".
            (G_OBJECT_CLASS(g_type_class_peek_parent(G_OBJECT_GET_CLASS(object))))->finalize(object);
        }
    };

    struct GlibCppTypeClass
    {
        typename DerivedCppType::BaseClassType  parent_class;
        /* nothing more */
        static void init (GlibCppTypeClass * klass, gpointer data)
        {
            DerivedCppType::CppClassType::class_init_function((void*)klass, (void*)data);
            GObjectClass *gobject_class;

            gobject_class = (GObjectClass *) klass;

            gobject_class->get_property = &Glib::custom_get_property_callback;
            gobject_class->set_property = &Glib::custom_set_property_callback;
            gobject_class->finalize =  &GlibCppType::finalize;

	    Gst::ElementClass<DerivedCppType> element_class((typename DerivedCppType::BaseClassType*) klass);
	    DerivedCppType::class_init(&element_class);
        }
    };

    Glib::init();

    // the "most derived" pure glib type
    GType parent_type = DerivedCppType::get_base_type();

    /* The typedef for GType may be gulong or gsize, depending on the
     * system and whether the compiler is c++ or not. The g_once_init_*
     * functions always take a gsize * though ... */
    static gsize gonce_data = 0;
    if (g_once_init_enter (&gonce_data)) {
        GTypeInfo info;

        info.class_size = sizeof(GlibCppTypeClass);
        info.base_init = nullptr;
        info.base_finalize = nullptr;
        info.class_init = (GClassInitFunc) &GlibCppTypeClass::init;
        info.class_finalize = nullptr;
        info.class_data = nullptr;
        info.instance_size = sizeof(GlibCppType);
        info.n_preallocs = 0;
        info.instance_init = (GInstanceInitFunc) &GlibCppType::init;
        info.value_table = nullptr;

        GType _type = g_type_register_static(parent_type, type_name, &info, (GTypeFlags)0);
        g_once_init_leave(&gonce_data, (gsize) _type);
    }
    return (GType) gonce_data;
}

} /*namespace Gst*/


#endif /* REGISTER_H_ */

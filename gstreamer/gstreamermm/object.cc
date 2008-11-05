/* gstreamermm - a C++ wrapper for gstreamer
 *
 * Copyright 2008 The gstreamermm Development Team
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the Free
 * Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#include <gstreamermm/object.h>
#include <gstreamermm/private/object_p.h>

#include <gst/gstobject.h>

namespace Gst
{


/* The *_Class implementation: */

const Glib::Class& Object_Class::init()
{
  if(!gtype_) // create the GType if necessary
  {
    // Glib::Class has to know the class init function to clone custom types.
    class_init_func_ = &Object_Class::class_init_function;

    // This is actually just optimized away, apparently with no harm.
    // Make sure that the parent type has been created.
    //CppClassParent::CppObjectType::get_type();

    // Create the wrapper type, with the same class/instance size as the base type.
    register_derived_type(gst_object_get_type());

    // Add derived versions of interfaces, if the C type implements any interfaces:
  }

  return *this;
}

void Object_Class::class_init_function(void* g_class, void* class_data)
{
  BaseClassType *const klass = static_cast<BaseClassType*>(g_class);
  CppClassParent::class_init_function(klass, class_data);
}

Glib::ObjectBase* Object_Class::wrap_new(GObject* object)
{
  return new Object((GstObject*)object);
}

/* The implementation: */

GstObject* Object::gobj_copy()
{
  reference();
  return gobj();
}

Object::Object(const Glib::ConstructParams& construct_params)
:
  Glib::Object(construct_params)
{

}

Object::Object(GstObject* castitem)
:
  Glib::Object((GObject*)(castitem))
{
  if(GST_OBJECT_IS_FLOATING(castitem))
  {
    //The floating reference is convenience for C,
    //but is useless and difficult for us:
    gst_object_ref(gobj());
    gst_object_sink(gobj());
  }
}

Object::~Object()
{
}

Object::Object()
:
  // Mark this class as non-derived to allow C++ vfuncs to be skipped.
  Glib::ObjectBase(0),
  Glib::Object(Glib::ConstructParams(object_class_.init()))
{
  //The floating reference is convenience for C,
  //but is useless and difficult for us:
  gst_object_ref(gobj());
  gst_object_sink(gobj());
}


Object::CppClassType Object::object_class_; // initialize static member

GType Object::get_type()
{
  return object_class_.init().get_type();
}

GType Object::get_base_type()
{
  return gst_object_get_type();
}

void Object::reference() const
{
  gst_object_ref(const_cast<GstObject*>(gobj())); 
}

void Object::unreference() const
{
  gst_object_unref(const_cast<GstObject*>(gobj())); 
}

bool Object::set_name(const Glib::ustring& name)
{
  return gst_object_set_name(gobj(), name.c_str());
}

bool Object::set_name()
{
  return gst_object_set_name(gobj(), NULL);
}

Glib::ustring Object::get_name() const
{
  return Glib::convert_return_gchar_ptr_to_ustring(gst_object_get_name(const_cast<GstObject*>(gobj())));
}

bool Object::set_parent(const Glib::RefPtr<Object>& parent)
{
  return gst_object_set_parent(gobj(), Glib::unwrap(parent));
}

Glib::RefPtr<Object> Object::get_parent()
{
  return Glib::wrap(gst_object_get_parent(gobj()));
}

Glib::RefPtr<const Object> Object::get_parent() const
{
  return Glib::wrap(gst_object_get_parent(const_cast<GstObject*>(gobj())));
}

void Object::unparent()
{
  gst_object_unparent(gobj()); 
}

Glib::ustring Object::get_name_prefix() const
{
  return Glib::convert_return_gchar_ptr_to_ustring(gst_object_get_name_prefix(const_cast<GstObject*>(gobj())));
}

void Object::set_name_prefix(const Glib::ustring& prefix)
{
  gst_object_set_name_prefix(gobj(), prefix.c_str()); 
}

xmlpp::Node* Object::save(xmlpp::Node* parent) const
{
  gst_object_save_thyself(const_cast<GstObject*>(gobj()), parent->cobj());

  // gst_object_save_thyself() returns parent node so do so here also.
  return parent;
}

void Object::restore(xmlpp::Node* self)
{
  gst_object_restore_thyself(gobj(), self->cobj());
}

#ifdef GLIBMM_PROPERTIES_ENABLED
Glib::PropertyProxy<Glib::ustring> Object::property_name() 
{
  return Glib::PropertyProxy<Glib::ustring>(this, "name");
}
#endif //GLIBMM_PROPERTIES_ENABLED

#ifdef GLIBMM_PROPERTIES_ENABLED
Glib::PropertyProxy_ReadOnly<Glib::ustring> Object::property_name() const
{
  return Glib::PropertyProxy_ReadOnly<Glib::ustring>(this, "name");
}
#endif //GLIBMM_PROPERTIES_ENABLED

} // namespace Gst

namespace Glib
{

Glib::RefPtr<Gst::Object> wrap(GstObject* object, bool take_copy)
{
  return Glib::RefPtr<Gst::Object>( dynamic_cast<Gst::Object*> (Glib::wrap_auto ((GObject*)(object), take_copy)) );
  //We use dynamic_cast<> in case of multiple inheritance.
}


} /* namespace Glib */



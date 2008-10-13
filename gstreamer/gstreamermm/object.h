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

#ifndef _GSTREAMERMM_OBJECT_H
#define _GSTREAMERMM_OBJECT_H


#include <glibmm.h>
#include <glibmm/object.h>
#include <libxml++/nodes/node.h>


#ifndef DOXYGEN_SHOULD_SKIP_THIS
typedef struct _GstObject GstObject;
typedef struct _GstObjectClass GstObjectClass;
#endif /* DOXYGEN_SHOULD_SKIP_THIS */


namespace Gst
{
class Object_Class;
} // namespace Gst

namespace Gst
{

//Note that this is hand-coded (instead of using .hg and .ccg files with gmmproc),
//so that we can add code to the Object(GObject*) constructor.
//(If this becomes difficult then we might add a _CUSTOM_CAST_CTOR() macro to gmmproc).

//TODO: Paragraphs about floating references their effect on elements and how
//to handle them using gst_object_ref() and gst_object_sink() are not included
//in class docs below.  Should they be?

/** Gst::Object — Base class for the GStreamer object hierarchy.
 * Gst::Object provides a root for the object hierarchy tree filed in by the
 * GStreamer library. It is currently a thin wrapper on top of Glib::Object.
 * It is an abstract class that is not very usable on its own.
 *
 * Gst::Object gives us basic refcounting, parenting functionality and
 * locking. Most of the function are just extended for special GStreamer needs
 * and can be found under the same name in the base class of Gst::Object which
 * is Glib::Object (e.g. Glib::Object::reference() becomes
 * Gst:Object::reference().
 *
 * In contrast to Glib::Object instances, Gst::Object adds a name property.
 * The functions set_name() and get_name() are used to set/get the name of the
 * object.
 *
 * Last reviewed on 2005-11-09 (0.9.4)
 */
class Object : public Glib::Object 
{
  
#ifndef DOXYGEN_SHOULD_SKIP_THIS

public:
  typedef Object CppObjectType;
  typedef Object_Class CppClassType;
  typedef GstObject BaseObjectType;
  typedef GstObjectClass BaseClassType;

private:  friend class Object_Class;
  static CppClassType object_class_;

private:
  // noncopyable
  Object(const Object&);
  Object& operator=(const Object&);

protected:
  explicit Object(const Glib::ConstructParams& construct_params);
  explicit Object(GstObject* castitem);

#endif /* DOXYGEN_SHOULD_SKIP_THIS */

public:
  virtual ~Object();

#ifndef DOXYGEN_SHOULD_SKIP_THIS
  static GType get_type()      G_GNUC_CONST;
  static GType get_base_type() G_GNUC_CONST;
#endif

  ///Provides access to the underlying C GObject.
  GstObject*       gobj()       { return reinterpret_cast<GstObject*>(gobject_); }

  ///Provides access to the underlying C GObject.
  const GstObject* gobj() const { return reinterpret_cast<GstObject*>(gobject_); }

  ///Provides access to the underlying C instance. The caller is responsible for unrefing it. Use when directly setting fields in structs.
  GstObject* gobj_copy();

protected:
  Object();

public:

  //Note that gst_object_ref() and gst_object_unref() just call the GObject functions, with some extra debug logging.
  void reference() const;
  void unreference() const;
  
  /** Sets the name of object.  For setting an arbitrary name, use set_name()
   * with no argument.  This function makes a copy of the provided name, so the
   * caller retains ownership of the name it sent.
   *
   * @param name New name of object.
   * @return true if the name could be set. Since Objects that have a parent
   * cannot be renamed, this function returns false in those cases. MT safe.
   * This function grabs and releases object's LOCK. 
   */
  bool set_name(const Glib::ustring& name);

  /** Gives object a guaranteed unique name.
   * 
   * @return true if the name could be set. Since Objects that have a parent
   * cannot be renamed, this function returns false in those cases. MT safe.
   * This function grabs and releases object's LOCK. 
   */
  bool set_name();

  /** Returns a copy of the name of object. For a nameless object, this
   * returns NULL.
   *
   * @return The name of object. MT safe. This function grabs and releases
   * object's LOCK. 
   */
  Glib::ustring get_name() const;
  
  //TODO: floating reference comment not included in set_parent() method docs
  //below.
  /** Sets the parent of object to parent. The object's reference count will
   * be incremented.
   *
   * This function causes the parent-set signal to be emitted when the parent
   * was successfully set.
   *
   * @param parent New parent of object.
   * @return true if parent could be set or false when object already had a
   * parent or object and parent are the same. MT safe. Grabs and releases
   * object's LOCK.
   */
  bool set_parent(const Glib::RefPtr<Object>& parent);

  /** Returns the parent of object. 
   *
   * @return Parent of object, this can be NULL if object has no parent. MT
   * safe. Grabs and releases object's LOCK.
   */
  Glib::RefPtr<Object> get_parent();

  /** Returns the parent of object. 
   *
   * @return Parent of object, this can be NULL if object has no parent. MT
   * safe. Grabs and releases object's LOCK.
   */
  Glib::RefPtr<const Object> get_parent() const;

  /** Clear the parent of object, removing the associated reference. This
   * function decreases the refcount of object.
   *
   * MT safe. Grabs and releases object's lock.
   */
  void unparent();
  
  /** Returns a copy of the name prefix of object. For a prefixless object,
   * this returns NULL.
   *
   * @return The name prefix of object. MT safe. This function grabs and
   * releases object's LOCK. 
   */
  Glib::ustring get_name_prefix() const;

  /** Sets the name prefix of object to name_prefix. This function makes a
   * copy of the provided name prefix, so the caller retains ownership of the
   * name prefix it sent.
   *
   * MT safe. This function grabs and releases object's LOCK.
   *
   * @param name_prefix New name prefix of object.
   *
   */
  void set_name_prefix(const Glib::ustring& prefix);

  //TODO: Is this useful? (Note that the .def needs to be fixed by hand): _WRAP_SIGNAL(void deep_notify(Glib::RefPtr<Object> prop_object, GParamSpec* prop), "deep-notify")
  //TODO: Is this useful? _WRAP_SIGNAL(void object_saved(xmlNodePtr xml_node), "object-saved")  
  //TODO: When the C signal registration has been fixed: _WRAP_SIGNAL(void parent_set(Glib::RefPtr<Object> parent), "parent-set")
  //TODO: When the C signal registration has been fixed: _WRAP_SIGNAL(void parent_unset(Glib::RefPtr<Object> parent), "parent-unset")

  /** Saves object into the parent XML node.
   * @param parent The parent XML node to save object into.
   * @return The new xmlpp::Node pointer with the saved object.
   */
  xmlpp::Node* save(xmlpp::Node* parent) const;

  /** Restores the Gst::Object with the data from the parent XML node.
   * @param self The XML node to load object from.
   */
  void restore(xmlpp::Node* self);

  #ifdef GLIBMM_PROPERTIES_ENABLED
  /** The name of the object.
   *
   * You rarely need to use properties because there are get_ and set_ methods for almost all of them.
   * @return A PropertyProxy that allows you to get or set the property of the value, or receive notification when
   * the value of the property changes.
   */
  Glib::PropertyProxy<Glib::ustring> property_name() ;
#endif //#GLIBMM_PROPERTIES_ENABLED

#ifdef GLIBMM_PROPERTIES_ENABLED
  /** The name of the object.
   *
   * You rarely need to use properties because there are get_ and set_ methods for almost all of them.
   * @return A PropertyProxy that allows you to get or set the property of the value, or receive notification when
   * the value of the property changes.
   */
  Glib::PropertyProxy_ReadOnly<Glib::ustring> property_name() const;
#endif //#GLIBMM_PROPERTIES_ENABLED

  //TODO: Wrap vfuncs. This is quite easy when using gmmproc. murrayc.
};

} // namespace Gst


namespace Glib
{
  /** A Glib::wrap() method for this object.
   * 
   * @param object The C instance.
   * @param take_copy False if the result should take ownership of the C instance. True if it should take a new copy or ref.
   * @result A C++ instance that wraps this C instance.
   *
   * @relates Gst::Object
   */
  Glib::RefPtr<Gst::Object> wrap(GstObject* object, bool take_copy = false);
}


#endif /* _GSTREAMERMM_OBJECT_H */


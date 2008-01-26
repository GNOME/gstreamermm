#ifndef _GSTMM_OBJECT_H
#define _GSTMM_OBJECT_H


#include <glibmm.h>
#include <glibmm/object.h>


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

/** TODO: Add documentation.
 *
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

  
  bool set_name(const Glib::ustring& name);
  Glib::ustring get_name() const;
  
  bool set_parent(const Glib::RefPtr<Object>& parent);
  Glib::RefPtr<Object> get_parent();
  Glib::RefPtr<const Object> get_parent() const;

  
  void unparent();
  
  Glib::ustring get_name_prefix() const;
  void set_name_prefix(const Glib::ustring& prefix);

  //TODO: Is this useful? (Note that the .def needs to be fixed by hand): _WRAP_SIGNAL(void deep_notify(Glib::RefPtr<Object> prop_object, GParamSpec* prop), "deep-notify")
  //TODO: Is this useful? _WRAP_SIGNAL(void object_saved(xmlNodePtr xml_node), "object-saved")  
  //TODO: When the C signal registration has been fixed: _WRAP_SIGNAL(void parent_set(Glib::RefPtr<Object> parent), "parent-set")
  //TODO: When the C signal registration has been fixed: _WRAP_SIGNAL(void parent_unset(Glib::RefPtr<Object> parent), "parent-unset")

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


#endif /* _GSTMM_OBJECT_H */


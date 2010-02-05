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

#ifndef _GSTREAMERMM_MINIOBJECT_H
#define _GSTREAMERMM_MINIOBJECT_H

#include <gst/gstminiobject.h>
#include <glibmm/refptr.h>
#include <glibmm/value.h>
#include <gstreamermm/wrap.h>

namespace Glib
{ class Class; }

namespace Gst
{

class MiniObject_Class;

/** This is a base class for some gstreamermm objects.
 * It is similar to Glib::Object but has no GObject property or signal support.
 */
class MiniObject
{
public:
#ifndef DOXYGEN_SHOULD_SKIP_THIS
  typedef MiniObject       CppObjectType;
  typedef MiniObject_Class CppClassType;
  typedef GstMiniObject      BaseObjectType;
  typedef GstMiniObjectClass BaseClassType;
#endif /* DOXYGEN_SHOULD_SKIP_THIS */

private:
  friend class MiniObject_Class;
  static CppClassType mini_object_class_;

  // noncopyable
  MiniObject(const MiniObject&);
  MiniObject& operator=(const MiniObject&);

protected:
  MiniObject();
  explicit MiniObject(const Glib::Class& mini_object_class);
  explicit MiniObject(GstMiniObject* castitem, bool take_copy = false);
  
public:
#ifndef DOXYGEN_SHOULD_SKIP_THIS
  static GType get_type()      G_GNUC_CONST;
  static GType get_base_type() G_GNUC_CONST;
#endif

public:
  virtual ~MiniObject();

  //Note that we don't add a constructor for gst_mini_object_new()
  //because it's just an equivalent for g_object_new(), 
  //which is just an equivalent for C++'s new(). 

  /** Returns the entire set of flags for the mini-object.
   * @return The Gst::MiniObject flags.
   */
  guint get_flags() const;

  /** Checks to see if the given flag is set.

   * @param flag The flag to check for.
   */
  bool flag_is_set(guint flag) const;

  /** Sets the given bits.
   * @param flag The flag to set, can by any number of bits in guint32. 
   */
  void set_flag(guint flag);

  /** Unsets the given bits.
   * @param flag The flag to unset, must be a single bit in guint32. 
   */
  void unset_flag(guint flag);

  /** Checks if a mini-object is writable. A mini-object is writable if the
   * reference count is one and the Gst::MINI_OBJECT_FLAG_READONLY flag is not
   * set. Modification of a mini-object should only be done after verifying
   * that it is writable.
   * 
   * MT safe
   *
   * @return true if the object is writable.
   */
  bool is_writable() const;

  /** Checks if a mini-object is writable. If not, a writable copy is made and
   * returned. This gives away the reference to the original mini object, and
   * returns a reference to the new object.
   *
   * MT safe
   *
   * @return A mini-object (possibly the same pointer) that is writable. 
   */
  Glib::RefPtr<Gst::MiniObject> create_writable();

  void reference() const;
  void unreference() const;

  ///Provides access to the underlying C GstMiniObject.
  GstMiniObject*       gobj()       { return reinterpret_cast<GstMiniObject*>(gobject_); }

  ///Provides access to the underlying C GstMiniObject.
  const GstMiniObject* gobj() const { return reinterpret_cast<GstMiniObject*>(gobject_); }

  ///Provides access to the underlying C instance. The caller is responsible for unrefing it. Use when directly setting fields in structs.
  GstMiniObject* gobj_copy();

  // static void replace(Glib::RefPtr<Gst::MiniObject> & olddata, Glib::RefPtr<Gst::MiniObject> & newdata);

#ifdef GLIBMM_VFUNCS_ENABLED
  /** Virtual function called when the Gst::MiniObject needs to be copied.
   */
  virtual Glib::RefPtr<Gst::MiniObject> copy_vfunc() const;

  /** Virtual function called when the Gst::MiniObject is about to be
   * finalized.
   */
  virtual void finalize_vfunc();
#endif //GLIBMM_VFUNCS_ENABLED


protected:
  void swap(MiniObject& other);

protected:
  GstMiniObject* gobject_;
};

} // namespace Gst

#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace Glib
{

template <>
class Value< Glib::RefPtr<Gst::MiniObject> > : public ValueBase
{
public:
  static GType value_type()
  {
    return Gst::MiniObject::get_type();
  }

  void set(const Glib::RefPtr<Gst::MiniObject>& object)
  {
    g_value_set_pointer(&gobject_, Gst::unwrap(object));
  }

  Glib::RefPtr<Gst::MiniObject> get()
  {
    return Glib::RefPtr<Gst::MiniObject>(Gst::wrap_auto(static_cast<GstMiniObject*>(g_value_get_pointer(&gobject_)), true));
  }
};

} // namespace Glib
#endif // #ifndef DOXYGEN_SHOULD_SKIP_THIS

#endif // #ifndef _GSTREAMERMM_MINIOBJECT_H

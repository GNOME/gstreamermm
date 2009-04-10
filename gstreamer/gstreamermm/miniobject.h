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

#include <glibmm/objectbase.h>
#include <gst/gstminiobject.h>

namespace Gst
{

class MiniObject_Class;

/** This is a base class for some gstreamermm objects.
 * It is similar to Glib::Object but has no GObject property or signal support.
 */
class MiniObject : public Glib::ObjectBase
{
public:
#ifndef DOXYGEN_SHOULD_SKIP_THIS
  typedef MiniObject       CppObjectType;
  typedef MiniObject_Class CppClassType;
  typedef GstMiniObject      BaseObjectType;
  typedef GstMiniObjectClass BaseClassType;
#endif /* DOXYGEN_SHOULD_SKIP_THIS */

//protected:
public:
  //friend Glib::wrap;

  MiniObject();
  MiniObject(GstMiniObject* castitem, bool take_copy = false);

public:
  virtual ~MiniObject();
  
  //Note that we don't add a constructor for gst_mini_object_new()
  //because it's just an equivalent for g_object_new(), 
  //which is just an equivalent for C++'s new(). 

//protected:
  // noncopyable
  /** A copy constructor.  Please note that copying is actually only supported
   * in sub-classes that define their own custom copy function in the C API
   * such as Gst::Event, Gst::Buffer, etc. otherwise the copy is not
   * successful and a warning is issued.
   */
  MiniObject(const MiniObject&);

  /** Assignment operator.  Please note that copying is actually only
   * supported in sub-classes that define their own custom copy function in
   * the C API such as Gst::Event, Gst::Buffer, etc. otherwise the copy
   * is not successful and a warning is issued.
   */
  MiniObject& operator=(const MiniObject&);

public:
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

  /** Creates a copy of the mini-object.  Please note that copying is
   * supported only by sub-classes of Gst::MiniObject such as Gst::Event,
   * Gst::Buffer, etc. that define their own custom copy function in the C API
   * and not directly by Gst::MiniObject, a base class.  If used from only a
   * Gst::MiniObject instance and not a sub-class instance the copy is not
   * successful and a warning is issued.
   *
   * MT safe.
   *
   * @return A copy of the mini-object or warn if this object is only a
   * Gst::MiniObject and not a sub-class that defines its own copy function.
   */
  Glib::RefPtr<Gst::MiniObject> copy() const;

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


  // static void replace(Glib::RefPtr<Gst::MiniObject> & olddata, Glib::RefPtr<Gst::MiniObject> & newdata);

protected:
  void swap(MiniObject& other);

protected:
  GstMiniObject* gobject_; //TODO: Doesn't this shadow a member variable in Glib::ObjectBase?

// TODO: Virtual functions copy_vfunc() and finalize_vfunc() are not easily
// wrapped because their class member types (GstMiniObjectCopyFunction and
// GstMiniObjectFinalizeFunction) don't include a gpointer parameter that
// callbacks can use.
};

} // namespace Gst

/*
namespace Glib
{
  inline Glib::RefPtr<Gst::MiniObject> wrap(GstMiniObject *object, bool take_copy)
  {
    return Glib::RefPtr<Gst::MiniObject>(new MiniObject(object, take_copy));
  }

} //namespace Glib
*/

#endif //#ifndef _GSTREAMERMM_MINIOBJECT_H

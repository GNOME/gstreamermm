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

#include <gstreamermm/miniobject.h>
#include <gstreamermm/private/miniobject_p.h>
#include <gstreamermm/wrap.h>

namespace Gst
{


// gst_mini_object_base_[init|finalize]() don't do anything so those don't
// have to be called from here.
void MiniObject_Class::class_init_function(void*, void*)
{}

MiniObject::MiniObject()
: gobject_(0)
{}

MiniObject::MiniObject(GstMiniObject* castitem, bool take_copy)
: gobject_(take_copy ? gst_mini_object_copy(castitem) : castitem)
{}

MiniObject::MiniObject(const MiniObject& other)
: gobject_(gst_mini_object_copy(other.gobject_))
{}

MiniObject&
MiniObject::operator=(const MiniObject& other)
{
  MiniObject temp(other);
  swap(temp);
  return *this;
}

MiniObject::~MiniObject()
{
  if(gobject_)
    gst_mini_object_unref(gobject_);
}

void MiniObject::swap(MiniObject& other)
{
  GstMiniObject *const temp = gobject_;
  gobject_ = other.gobject_;
  other.gobject_ = temp;
}

void 
MiniObject::reference() const
{
  gst_mini_object_ref(gobject_);
}

void
MiniObject::unreference() const
{
  gst_mini_object_unref(gobject_);
}

guint MiniObject::get_flags() const
{
  return GST_MINI_OBJECT_FLAGS(gobj());
}

bool MiniObject::flag_is_set(guint flag) const
{
  return GST_MINI_OBJECT_FLAG_IS_SET(gobj(), flag);
}

void MiniObject::set_flag(guint flag)
{
  GST_MINI_OBJECT_FLAG_SET(gobj(), flag);
}

void MiniObject::unset_flag(guint flag)
{
  GST_MINI_OBJECT_FLAG_UNSET(gobj(), flag);
}

Glib::RefPtr<Gst::MiniObject>
MiniObject::copy() const
{
  GstMiniObject * copy = gst_mini_object_copy(gobject_);
  return Gst::wrap(copy, false);
}

bool
MiniObject::is_writable() const
{
  return gst_mini_object_is_writable(gobject_);
}

Glib::RefPtr<Gst::MiniObject> MiniObject::create_writable()
{
  return Gst::wrap(gst_mini_object_make_writable(gobject_));
}

} //namespace Gst

/*
namespace Glib
{

Glib::RefPtr<Gst::MiniObject> wrap(GstMiniObject* object, bool take_copy)
{
  return Glib::RefPtr<Gst::MiniObject>(new MiniObject(object, take_copy));
}

} //namespace Glib

*/

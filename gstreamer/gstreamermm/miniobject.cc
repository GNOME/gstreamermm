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

#include <gstreamermm/miniobject.h>
#include <gstreamermm/private/miniobject_p.h>
#include <gstreamermm/wrap.h>

namespace Gst
{


void MiniObject_Class::class_init_function(void*, void*)
{}

MiniObject::MiniObject()
: _gobject(0)
{
}

MiniObject::MiniObject(GstMiniObject* castitem, bool take_copy)
: _gobject(take_copy ? gst_mini_object_copy(castitem) : castitem)
{
}

MiniObject::MiniObject(const MiniObject& other)
: _gobject(gst_mini_object_copy(other._gobject))
{
}

MiniObject&
MiniObject::operator=(const MiniObject& other)
{
  MiniObject temp(other);
  swap(temp);
  return *this;
}

MiniObject::~MiniObject()
{
  if(_gobject)
    gst_mini_object_unref(_gobject);
}

void MiniObject::swap(MiniObject& other)
{
  GstMiniObject *const temp = _gobject;
  _gobject = other._gobject;
  other._gobject = temp;
}

void 
MiniObject::reference() const
{
  gst_mini_object_ref(_gobject);
}

void
MiniObject::unreference() const
{
  gst_mini_object_unref(_gobject);
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
  GstMiniObject * copy = gst_mini_object_copy(_gobject);
  return Gst::wrap(copy, false);
}

bool
MiniObject::is_writable() const
{
  return gst_mini_object_is_writable(_gobject);
}

Glib::RefPtr<Gst::MiniObject> MiniObject::create_writable()
{
  return Gst::wrap(gst_mini_object_make_writable(_gobject));
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

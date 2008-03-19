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

namespace Gst
{


void MiniObject_Class::class_init_function(void*, void*)
{}

MiniObject::MiniObject()
: gobject_(0)
{
}

MiniObject::MiniObject(GstMiniObject* castitem, bool take_copy)
: gobject_(take_copy ? gst_mini_object_copy(castitem) : castitem)
{
}

MiniObject::MiniObject(const MiniObject& other)
: gobject_(gst_mini_object_copy(other.gobject_))
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

// TODO: Investigate how this works:

// TODO: As far as I can tell, derived types must implement a
// TODO: GstMiniObjectCopyFunction in a class structure.
// TODO: gst_mini_object_class_init() sets the (*GstMiniObjectCopyFunction)(...)
// TODO: to gst_mini_object_copy_default() which does nothing, but derived
// TODO: types (like GstQuery, etc) have their own functions (like
// TODO: gst_query_copy()) which do work. Jose
/*
Glib::RefPtr<Gst::MiniObject>
MiniObject::copy()
{
  GstMiniObject * copy = gst_mini_object_copy(gobject_);
  return Glib::wrap(copy, false);
}
*/

bool
MiniObject::is_writable() const
{
  return gst_mini_object_is_writable(gobject_);
}

void
MiniObject::make_writable()
{
  gst_mini_object_make_writable(gobject_);
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

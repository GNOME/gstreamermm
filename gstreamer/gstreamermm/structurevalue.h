#ifndef _GSTREAMERMM_STRUCTUREVALUE_H
#define _GSTREAMERMM_STRUCTUREVALUE_H
// -*- Mode: C++; indent-tabs-mode: nil; c-basic-offset: 2 -*-

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


#include <glib-object.h>
#include <glibmm/value.h>

namespace Gst
{

/** Base class of Gst::StructureValue templates.
 */
class StructureValueBase
{
public:
  GType type()  const { return type_;  }

protected:
  explicit StructureValueBase(GType type);

private:
  GType type_;
};


/** Template class used to convert simple C++ types to usable Gst::Structure
 * Glib::Value<> types. It is used for setting/getting fields in
 * Gst::Structures.
 */
template <class T>
class StructureValue : public StructureValueBase
{
public:
  typedef T               ElementType;
  typedef Glib::Value<T>  ValueType;

  StructureValue() : StructureValueBase(ValueType::value_type()) {}
};

} // namespace Gst


#endif /* _GSTREAMERMM_STRUCTUREVALUE_H */


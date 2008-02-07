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

#ifndef _GSTREAMERMM_OBJECT_P_H
#define _GSTREAMERMM_OBJECT_P_H


#include <glibmm/private/object_p.h>

#include <glibmm/class.h>

namespace Gst
{

class Object_Class : public Glib::Class
{
public:
#ifndef DOXYGEN_SHOULD_SKIP_THIS
  typedef Object CppObjectType;
  typedef GstObject BaseObjectType;
  typedef GstObjectClass BaseClassType;
  typedef Glib::Object_Class CppClassParent;
  typedef GObjectClass BaseClassParent;

  friend class Object;
#endif /* DOXYGEN_SHOULD_SKIP_THIS */

  const Glib::Class& init();

  static void class_init_function(void* g_class, void* class_data);

  static Glib::ObjectBase* wrap_new(GObject*);
};


} // namespace Gst


#endif /* _GSTREAMERMM_OBJECT_P_H */


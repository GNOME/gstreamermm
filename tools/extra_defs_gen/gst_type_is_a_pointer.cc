/* gst_type_is_a_pointer.cc
 *
 * Copyright 2008 The gstreamermm Development Team
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with this library; if not, write to the Free
 * Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#include "gst_type_is_a_pointer.h"
#include <gst/gst.h>

bool gst_type_is_a_pointer(GType gtype)
{
  return (g_type_is_a(gtype, G_TYPE_OBJECT) ||
    g_type_is_a(gtype, G_TYPE_BOXED) ||
    g_type_is_a(gtype, GST_TYPE_MINI_OBJECT));
}

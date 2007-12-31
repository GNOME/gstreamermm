/* generate_defs_gst.cc
 *
 * Copyright (C) 2001 The Free Software Foundation
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public
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

#include "glibmm_generate_extra_defs/generate_extra_defs.h"

#include <glib.h>
#include <gst/gst.h>

int main (int argc, char *argv[])
{
  gst_init (&argc, &argv);
  std::cout << get_defs(GST_TYPE_BUS)
            << get_defs(GST_TYPE_BIN)
            << get_defs(GST_TYPE_CLOCK)
            << get_defs(GST_TYPE_ELEMENT)
            << get_defs(GST_TYPE_OBJECT)
            << get_defs(GST_TYPE_PAD)
            << get_defs(GST_TYPE_PAD_TEMPLATE)
            << get_defs(GST_TYPE_PIPELINE)
            << get_defs(GST_TYPE_SYSTEM_CLOCK)
            << get_defs(GST_TYPE_XML);
  return 0;
}

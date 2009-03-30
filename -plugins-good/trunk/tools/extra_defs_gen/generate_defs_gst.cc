/* generate_defs_gst.cc
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

#include <glibmm_generate_extra_defs/generate_extra_defs.h>
#include <gstreamermm_get_plugin_defs/get_plugin_defs.h>
#include <gst/gst.h>

int main (int argc, char *argv[])
{
  gst_init (&argc, &argv);

  std::cout << get_plugin_defs("aasink")
            << get_plugin_defs("alphacolor")
            ;
  return 0;
}

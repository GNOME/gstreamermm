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

#include <gstreamermm/init.h>
#include <gstreamermm-plugins-good/init.h>
#include <gstreamermm-plugins-good/wrap_init.h>

namespace Gst
{

static void initialize_wrap_system()
{
  static bool s_init = false;
  if(!s_init)
  {
    // For Glib::wrap(), for Glib::Object-derived classes.
    Gst::wrap_init(); 

    s_init = true;
  }
}

void init_plugins_good()
{
  static bool s_init = false;
  if(!s_init)
  {
    Gst::init();
    initialize_wrap_system();

    s_init = true;
  }
}

} // namespace Gst

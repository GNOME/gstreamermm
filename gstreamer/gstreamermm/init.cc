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
#include <gstreamermm/wrap_init.h>
#include <glibmm/init.h>
#include <gst/gst.h>

namespace Gst
{

static void initialize_wrap_system()
{
  static bool s_init = false;
  if(!s_init)
  {
    //For Glib::wrap(), for Glib::Object-derived classes.
    Gst::wrap_init(); 
    s_init = true;
  }
}

void init(int& argc, char**& argv)
{
  static bool s_init = false;
  if(!s_init)
  {
    Glib::init();
    gst_init(&argc, &argv);
    initialize_wrap_system();
    s_init = true;
  }
}

void init()
{
  static bool s_init = false;
  if(!s_init)
  {
    Glib::init();
    gst_init(nullptr, nullptr);
    initialize_wrap_system();
    s_init = true;
  }
}

bool init_check(int& argc, char**& argv)
{
  static bool s_init = false;
  static bool result = false;

  if(!s_init)
  {
    Glib::init();

    GError* gerror = nullptr;
    result = gst_init_check(&argc, &argv, &gerror);

    if(gerror)
      ::Glib::Error::throw_exception(gerror);

    initialize_wrap_system();
    s_init = true;
  }

  return result;
}

bool init_check()
{
  static bool s_init = false;
  static bool result = false;

  if(!s_init)
  {
    Glib::init();

    GError* gerror = nullptr;
    result = gst_init_check(nullptr, nullptr, &gerror);

    if(gerror)
      ::Glib::Error::throw_exception(gerror);

    initialize_wrap_system();
    s_init = true;
  }

  return result;
}

bool is_initialized()
{
  return static_cast<bool>(gst_is_initialized());
}

void deinit()
{
  gst_deinit();
}

Glib::OptionGroup get_option_group()
{
  return Glib::OptionGroup(gst_init_get_option_group());
}

void version(guint& major, guint& minor, guint& micro, guint& nano)
{
  gst_version(&major, &minor, &micro, &nano);
}

Glib::ustring version_string()
{
  return Glib::ustring(gst_version_string());
}

bool segtrap_is_enabled()
{
  return gst_segtrap_is_enabled();
}

void segtrap_set_enabled(bool enabled)
{
  gst_segtrap_set_enabled(enabled);
}

bool registry_fork_is_enabled()
{
  return gst_registry_fork_is_enabled();
}

void registry_fork_set_enabled(bool enabled)
{
  gst_registry_fork_set_enabled(enabled);
}

bool update_registry()
{
  return gst_update_registry();
}

}

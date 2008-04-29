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

#include <gstreamermm/init.h>
#include <gstreamermm/wrap.h>
#include <gstreamermm/wrap_init.h>
#include <gstreamermm/gst_wrap_init.h>
#include <gstreamerbasemm/wrap_init.h>
#include <glibmm/init.h>
#include <gst/gst.h>

namespace Gst
{

void init(int& argc, char**& argv)
{
  static bool s_init = false;
  if(!s_init)
  {
    Glib::init();
    gst_init(&argc, &argv);

    //For Glib::wrap(), for Glib::Object-derived classes.
    Gst::wrap_init(); 

    //For Gst::wrap(), for Gst::MiniObject-derived classes.
    Gst::wrap_register_init();
    Gst::gst_wrap_init();

    //Initialize wraping for gstreamerbasemm co-library
    GstBase::wrap_init();

    s_init = true;
  }
}

#ifdef GLIBMM_EXCEPTIONS_ENABLED
bool init_check(int& argc, char**& argv)
#else
bool init_check(int& argc, char**& argv, std::auto_ptr<Glib::Error>& error)
#endif //GLIBMM_EXCEPTIONS_ENABLED
{
  Glib::init();
  GError* gerror = 0;
  bool result = gst_init_check(&argc, &argv, &gerror);

#ifdef GLIBMM_EXCEPTIONS_ENABLED
  if(gerror)
    ::Glib::Error::throw_exception(gerror);
#else
  if(gerror)
    error = ::Glib::Error::throw_exception(gerror);
#endif //GLIBMM_EXCEPTIONS_ENABLED

  Gst::wrap_init();
  return result;
}

Glib::OptionGroup get_option_group()
{
  return Glib::OptionGroup(gst_init_get_option_group());
}

}

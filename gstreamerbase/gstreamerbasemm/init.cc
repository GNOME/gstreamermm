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

#include <glibmm/init.h>
#include <gstreamerbasemm/init.h>
#include <gstreamerbasemm/wrap_init.h>
#include <gstreamermm/init.h>

namespace GstBase
{

void init(int& argc, char**& argv)
{
  static bool s_init = false;
  if(!s_init)
  {
    Gst::init(argc, argv);

    //For Glib::wrap(), for Glib::Object-derived classes.
    GstBase::wrap_init(); 

    s_init = true;
  }
}

void init()
{
  static bool s_init = false;
  if(!s_init)
  {
    Gst::init();

    //For Glib::wrap(), for Glib::Object-derived classes.
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
  static bool s_init = false;
  static bool result = false;

  if(!s_init)
  {

#ifdef GLIBMM_EXCEPTIONS_ENABLED
    result = Gst::init_check(argc, argv);
#else
    result = Gst::init_check(argc, argv, error);
#endif

    //For Glib::wrap(), for Glib::Object-derived classes.
    GstBase::wrap_init(); 

    s_init = true;
  }

  return result;
}

#ifdef GLIBMM_EXCEPTIONS_ENABLED
bool init_check()
#else
bool init_check(std::auto_ptr<Glib::Error>& error)
#endif //GLIBMM_EXCEPTIONS_ENABLED
{
  static bool s_init = false;
  static bool result = false;

  if(!s_init)
  {
#ifdef GLIBMM_EXCEPTIONS_ENABLED
    result = Gst::init_check();
#else
    result = Gst::init_check(error);
#endif

    //For Glib::wrap(), for Glib::Object-derived classes.
    GstBase::wrap_init(); 

    s_init = true;
  }

  return result;
}

} //namespace GstBase

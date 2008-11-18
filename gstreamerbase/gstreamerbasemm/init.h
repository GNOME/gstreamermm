// -*- c++ -*-

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

#ifndef _GSTREAMERBASEMM_INIT_H
#define _GSTREAMERBASEMM_INIT_H

#include <glibmm/error.h>

namespace GstBase
{

/** Initializes gstreamerbasemm and gstreamermm, if it is not already
 * initialized, parsing command line arguments.
 *
 * One of the GstBase::init() or GstBase::init_check() functions should be used
 * to initialize gstreamerbasemm before using it.  This function calls
 * Gst::init() with the command line arguments if it has not been called
 * already so this function may be used instead of that one to initialize both
 * gstreamermm and gstreamerbasemm.  If this function is used to initialize
 * gstreamermm it must be used before any other GLib functions.  If this is not
 * an option, and you want you initialize gstreamermm along with
 * gstreamerbasemm, your program must initialize the GLib thread system using
 * Glib::thread_init() before any other GLib functions are called and use
 * either GstBase::init(), or GstBase::init_check() without the command line
 * arguments before calling any gstreamermm or gstreamerbasemm functions.  GLib
 * thread initialization can be done as follows:
 *
 * @code
 * if (!Glib::thread_supported ())
 *   Glib::thread_init ();
 * ...
 * @endcode
 * 
 * @param argc Reference to application's argc.
 * @param argv Reference to application's argv.
 */
void init(int& argc, char**& argv);

/** Initializes gstreamerbasemm and gstreamermm, if it is not already
 * initialized, without parsing command line options.
 *
 * One of the GstBase::init() or GstBase::init_check() functions should be used
 * to initialize gstreamerbasemm before using it.  This function calls
 * Gst::init() if it has not been called already so this function may be used
 * instead of that one to initialize both gstreamermm and gstreamerbasemm.  If
 * this function is used to initialize gstreamermm it must be used before any
 * other GLib functions.  If this is not an option, and you want to initialize
 * gstreamermm along with gstreamerbasemm, your program must initialize the
 * GLib thread system using Glib::thread_init() before any other GLib functions
 * are called and use either this function or GstBase::init_check() without the
 * command line arguments before calling any gstreamermm or gstreamerbasemm
 * functions.  GLib thread initialization can be done as follows:
 *
 * @code
 * if (!Glib::thread_supported ())
 *   Glib::thread_init ();
 * ...
 * @endcode
 */
void init();

/** Initializes gstreamerbasemm and gstreamermm gracefully, if it is not
 * already initialized, parsing command line options.
 *
 * One of the GstBase::init() or GstBase::init_check() functions should be used
 * to initialize gstreamerbasemm before using it.  This function calls
 * Gst::init_check() with the command line arguments if it has not been called
 * already so this function may be used instead of that one to initialize both
 * gstreamermm and gstreamerbasemm.  If this function is used to initialize
 * gstreamermm it must be used before any other GLib functions.  If this is not
 * an option, and you want to initialize gstreamermm along with
 * gstreamerbasemm, your program must initialize the GLib thread system using
 * Glib::thread_init() before any other GLib functions are called and use
 * either GstBase::init() or GstBase::init_check() without the command line
 * arguments before calling any gstreamermm or gstreamerbasemm functions.  GLib
 * thread initialization can be done as follows:
 *
 * @code
 * if (!Glib::thread_supported ())
 *   Glib::thread_init ();
 * ...
 * @endcode
 * 
 * @param argc Reference to application's argc.
 * @param argv Reference to application's argv.
 * @return true if initialization was successful.
 * @throw Glib::Error
 */
#ifdef GLIBMM_EXCEPTIONS_ENABLED
  bool init_check(int& argc, char**& argv);
#else
  bool init_check(int& argc, char**& argv, std::auto_ptr<Glib::Error>& error);
#endif //GLIBMM_EXCEPTIONS_ENABLED

/** Initializes gstreamerbasemm and gstreamermm gracefully, if it is not
 * already initialized, without parsing command line options.
 *
 * One of the GstBase::init() or GstBase::init_check() functions should be used
 * to initialize gstreamerbasemm before using it.  This function calls
 * Gst::init_check() if it has not been called already so this function may be
 * used instead of that one to initialize both gstreamermm and gstreamerbasemm.
 * If this function is used to initialize gstreamermm it must be used before
 * any other GLib functions.  If this is not an option, and you want to
 * initialize gstreamermm along with gstreamerbasemm, your program must
 * initialize the GLib thread system using Glib::thread_init() before any other
 * GLib functions are called and use either this function or GstBase::init()
 * without the command line arguments before calling any gstreamermm or
 * gstreamerbasemm functions.  GLib thread initialization can be done as
 * follows:
 *
 * @code
 * if (!Glib::thread_supported ())
 *   Glib::thread_init ();
 * ...
 * @endcode
 * 
 * @return true if initialization was successful.
 * @throw Glib::Error
 */
#ifdef GLIBMM_EXCEPTIONS_ENABLED
  bool init_check();
#else
  bool init_check(std::auto_ptr<Glib::Error>& error);
#endif //GLIBMM_EXCEPTIONS_ENABLED

} //namespace GstBase

#endif //_GSTREAMERBASEMM_INIT_H


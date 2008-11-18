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

/** Initializes gstreamerbasemm parsing command line arguments.
 *
 * Either this function or GstBase::init_check() with command line parsing
 * should be called to initialize gstreamerbasemm before instantiating any of
 * its classes.  This function calls Gst::init() with the argc and argv
 * arguments if it has not been called already so this function may be used
 * instead of that one.  If this function is used to initialize gstreamermm it
 * must be used before any other GLib functions.  If this is not an option,
 * your program must initialize the GLib thread system using
 * Glib::thread_init() before any other GLib functions are called and use
 * either GstBase::init(), or GstBase::init_check() without the argc and argv
 * arguments before calling any gstreamerbasemm functions.  GLib thread
 * initialization can be done as follows:
 *
 * @code
 * if (!Glib::thread_supported ())
 *   Glib::thread_init ();
 * ...
 * @endcode
 * 
 *
 * Note: This function will terminate your program if it was unable to
 * initialize GStreamer for some reason. If you want your program to fall back,
 * use GstBase::init_check() instead.
 *
 * WARNING: This function does not work in the same way as corresponding
 * functions in other glib-style libraries, such as gtk_init(). In particular,
 * unknown command line options cause this function to abort program execution.
 *
 * @param argc Pointer to application's argc.
 * @param argv Pointer to application's argv.
 */
void init(int& argc, char**& argv);

/** Initializes gstreamerbasemm without parsing command line options.
 *
 * Either the GstBase::init() or GstBase::init_check() functions with command
 * line parsing should be called to initalize gstreamerbasemm before
 * instantiating any of its classes.  This function calls Gst::init() if it has
 * not been called already so this function may be used instead of that one.
 * If this function is used to initialize gstreamermm it must be used before
 * any other GLib functions.  If this is not an option, your program must
 * initialize the GLib thread system using Glib::thread_init() before any other
 * GLib functions are called and use either this function or
 * GstBase::init_check() without the argc and argv arguments before calling any
 * gstreamerbasemm functions.  GLib thread initialization can be done as
 * follows:
 *
 * @code
 * if (!Glib::thread_supported ())
 *   Glib::thread_init ();
 * ...
 * @endcode
 *
 * Note: This function will terminate your program if it was unable to
 * initialize gstreamerbasemm for some reason. If you want your program to fall
 * back, use GstBase::init_check() instead.
 */
void init();

/** Initializes gstreamerbasemm gracefully parsing command line arguments.
 *
 * Either this function or GstBase::init() with command line parsing should be
 * called to initialize gstreamerbasemm before instantiating any of
 * its classes.  This function calls Gst::init_check() with the argc and argv
 * arguments if it has not been called already so this function may be used
 * instead of that one.  If this function is used to initialize gstreamermm it
 * must be used before any other GLib functions.  If this is not an option,
 * your program must initialize the GLib thread system using
 * Glib::thread_init() before any other GLib functions are called and use
 * either GstBase::init() or GstBase::init_check() without the argc and argv
 * arguments before calling any gstreamerbasemm functions.  GLib thread
 * initialization can be done as follows:
 *
 * @code
 * if (!Glib::thread_supported ())
 *   Glib::thread_init ();
 * ...
 * @endcode
 * 
 * This function will return false if GStreamer could not be initialized for
 * some reason. If you want your program to fail fatally, use GstBase::init()
 * instead.
 *
 * @param argc Pointer to application's argc.
 * @param argv Pointer to application's argv.
 * @return true if GStreamer could be initialized.
 * @throw Glib::Error
 */
#ifdef GLIBMM_EXCEPTIONS_ENABLED
  bool init_check(int& argc, char**& argv);
#else
  bool init_check(int& argc, char**& argv, std::auto_ptr<Glib::Error>& error);
#endif //GLIBMM_EXCEPTIONS_ENABLED

/** Initializes gstreamerbasemm gracefully without parsing command line
 * arguments.
 *
 * Either the GstBase::init() or GstBase::init_check() functions with command
 * line parsing should be called to initalize gstreamerbasemm before
 * instantiating any of its classes.  This function calls Gst::init_check()
 * if it has not been called already so this function may be used instead of
 * that one.  If this function is used to initialize gstreamermm it
 * must be used before any other GLib functions.  If this is not an option,
 * your program must initialize the GLib thread system using
 * Glib::thread_init() before any other GLib functions are called and use
 * either this function or GstBase::init() without the argc and
 * argv arguments before calling any gstreamerbasemm functions.  GLib thread
 * initialization can be done as follows:
 *
 * @code
 * if (!Glib::thread_supported ())
 *   Glib::thread_init ();
 * ...
 * @endcode
 * 
 * This function will return false if GStreamer could not be initialized for
 * some reason. If you want your program to fail fatally, use GstBase::init()
 * instead.
 *
 * @return true if GStreamer could be initialized.
 * @throw Glib::Error
 */
#ifdef GLIBMM_EXCEPTIONS_ENABLED
  bool init_check();
#else
  bool init_check(std::auto_ptr<Glib::Error>& error);
#endif //GLIBMM_EXCEPTIONS_ENABLED

} //namespace GstBase

#endif //_GSTREAMERBASEMM_INIT_H


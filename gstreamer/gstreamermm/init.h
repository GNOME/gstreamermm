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

#ifndef _GSTREAMERMM_INIT_H
#define _GSTREAMERMM_INIT_H

#include <glibmm/error.h>
#include <glibmm/optiongroup.h>

namespace Gst
{

/** Initializes gstreamermm parsing command line arguments.
 *
 * Either this function or Gst::init_check() with command line parsing should
 * be called to initialize gstreamermm before calling any other GLib functions.
 * If this is not an option, your program must initialize the GLib thread
 * system using Glib::thread_init() before any other GLib functions are called
 * and use either Gst::init() or Gst::init_check() with no arguments before
 * calling any gstreamermm functions.  GLib thread initialization can be done
 * as follows:
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
 * use Gst::init_check() instead.
 *
 * WARNING: This function does not work in the same way as corresponding
 * functions in other glib-style libraries, such as gtk_init(). In particular,
 * unknown command line options cause this function to abort program execution.
 *
 * @param argc Pointer to application's argc.
 * @param argv Pointer to application's argv.
 */
void init(int& argc, char**& argv);

/** Initializes gstreamermm without parsing command line options.
 *
 * Either the Gst::init() or Gst::init_check() functions with command line
 * parsing should be called to initalize gstreamermm before calling any other
 * GLib functions. If this is not an option, your program must initialize the
 * GLib thread system using Glib::thread_init() before any other GLib functions
 * are called and use either this function or Gst::init_check() with no
 * arguments before calling any gstreamermm functions.  GLib thread
 * initialization can be done as follows:
 *
 * @code
 * if (!Glib::thread_supported ())
 *   Glib::thread_init ();
 * ...
 * @endcode
 *
 * Note: This function will terminate your program if it was unable to
 * initialize gstreamermm for some reason. If you want your program to fall
 * back, use Gst::init_check() instead.
 */
void init();

/** Initializes gstreamermm gracefully parsing command line arguments.
 *
 * Either this function or Gst::init() with command line parsing should be
 * called to initialize gstreamermm before calling any other GLib functions.
 * If this is not an option, your program must initialize the GLib thread
 * system using Glib::thread_init() before any other GLib functions are called
 * and use either Gst::init() or Gst::init_check() with no arguments before
 * calling any gstreamermm functions.  GLib thread initialization can be done
 * as follows:
 *
 * @code
 * if (!Glib::thread_supported ())
 *   Glib::thread_init ();
 * ...
 * @endcode
 * 
 * This function will return false if gstreamermm could not be initialized for
 * some reason. If you want your program to fail fatally, use Gst::init()
 * instead.
 *
 * @param argc Pointer to application's argc.
 * @param argv Pointer to application's argv.
 * @return true if gstreamermm could be initialized.
 * @throw Glib::Error
 */
#ifdef GLIBMM_EXCEPTIONS_ENABLED
  bool init_check(int& argc, char**& argv);
#else
  bool init_check(int& argc, char**& argv, std::auto_ptr<Glib::Error>& error);
#endif //GLIBMM_EXCEPTIONS_ENABLED

/** Initializes gstreamermm gracefully without parsing command line arguments.
 *
 * Either the Gst::init() or Gst::init_check() functions with command line
 * parsing should be called to initalize gstreamermm before calling any other
 * GLib functions. If this is not an option, your program must initialize the
 * GLib thread system using Glib::thread_init() before any other GLib functions
 * are called and use either this function or Gst::init() with no arguments
 * before calling any gstreamermm functions.  GLib thread initialization can be
 * done as follows:
 *
 * @code
 * if (!Glib::thread_supported ())
 *   Glib::thread_init ();
 * ...
 * @endcode
 * 
 * This function will return false if gstreamermm could not be initialized for
 * some reason. If you want your program to fail fatally, use Gst::init()
 * instead.
 *
 * @return true if gstreamermm could be initialized.
 * @throw Glib::Error
 */
#ifdef GLIBMM_EXCEPTIONS_ENABLED
  bool init_check();
#else
  bool init_check(std::auto_ptr<Glib::Error>& error);
#endif //GLIBMM_EXCEPTIONS_ENABLED

/** Returns a Glib::OptionGroup with GStreamer's argument specifications. The
 * group is set up to use standard GOption callbacks, so when using this group
 * in combination with GOption parsing methods, all argument parsing and
 * initialization is automated.
 *
 * This function is useful if you want to integrate GStreamer with other
 * libraries that use GOption (see g_option_context_add_group() ).
 *
 * If you use this function, you should make sure you initialise the GLib
 * threading system as one of the very first things in your program.
 *
 * @return A pointer to GStreamer's option group.
 */
Glib::OptionGroup get_option_group();
  
}//end namespace Gst

#endif //_GSTREAMERMM_INIT_H


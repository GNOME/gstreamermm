// -*- c++ -*-

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
 * and use either Gst::init(), or Gst::init_check() without the command line
 * arguments before calling any gstreamermm functions. 
 *
 * Note: This function will terminate your program if it was unable to
 * initialize GStreamer for some reason. If you want your program to fall back,
 * use Gst::init_check() instead.
 *
 * WARNING: This function does not work in the same way as corresponding
 * functions in other glib-style libraries, such as gtk_init(). In particular,
 * unknown command line options cause this function to abort program execution.
 *
 * @param argc Reference to application's argc.
 * @param argv Reference to application's argv.
 */
void init(int& argc, char**& argv);

/** Initializes gstreamermm without parsing command line options.
 *
 * Either the Gst::init() or Gst::init_check() functions with command line
 * parsing should be called to initialize gstreamermm before calling any other
 * GLib functions. If this is not an option, your program must initialize the
 * GLib thread system using Glib::thread_init() before any other GLib functions
 * are called and use either this function or Gst::init_check() without the
 * command line arguments before calling any gstreamermm functions.
 *
 * Note: This function will terminate your program if it was unable to
 * initialize GStreamer for some reason. If you want your program to fall
 * back, use Gst::init_check() instead.
 */
void init();

/** Initializes gstreamermm gracefully parsing command line arguments.
 *
 * Either this function or Gst::init() with command line parsing should be
 * called to initialize gstreamermm before calling any other GLib functions.
 * If this is not an option, your program must initialize the GLib thread
 * system using Glib::thread_init() before any other GLib functions are called
 * and use either Gst::init() or Gst::init_check() without the command line
 * arguments before calling any gstreamermm functions.
 * 
 * This function will return false if GStreamer could not be initialized for
 * some reason. If you want your program to fail fatally, use Gst::init()
 * instead.
 *
 * @param argc Reference to application's argc.
 * @param argv Reference to application's argv.
 * @return true if GStreamer could be initialized.
 * @throw Glib::Error
 */
bool init_check(int& argc, char**& argv);

/** Initializes gstreamermm gracefully without parsing command line arguments.
 *
 * Either the Gst::init() or Gst::init_check() functions with command line
 * parsing should be called to initialize gstreamermm before calling any other
 * GLib functions. If this is not an option, your program must initialize the
 * GLib thread system using Glib::thread_init() before any other GLib functions
 * are called and use either this function or Gst::init() without the command
 * line arguments before calling any gstreamermm functions.
 * 
 * This function will return false if GStreamer could not be initialized for
 * some reason. If you want your program to fail fatally, use Gst::init()
 * instead.
 *
 * @return true if GStreamer could be initialized.
 * @throw Glib::Error
 */
bool init_check();

/** Use this function to check if GStreamer has been initialized.
 * @return <tt>true</tt> if initialization has been done, <tt>false</tt>
 * otherwise.
 */
bool is_initialized(void);

/**  Clean up any resources created by GStreamer upon initialization.
 *
 * It is normally not needed to call this function in a normal application as
 * the resources will automatically be freed when the program terminates.
 * This function is therefore mostly used by testsuites and other memory
 * profiling tools.
 *
 * After this call GStreamer (including this method) should not be used
 * anymore. 
 */
void deinit();

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

/**
 * Gets the version number of the GStreamer library.
 *
 * @param major The major version number.
 * @param minor The minor version number.
 * @param micro The micro version number.
 * @param nano The nano version number.
 */
void version(guint& major, guint& minor, guint& micro, guint& nano);

/**
 * This function returns a string that is useful for describing this version
 * of GStreamer to the outside world: user agent strings, logging, ...
 *
 * @return A newly allocated string describing this version
 * of GStreamer.
 */
Glib::ustring version_string();

/**
 * Some functions in the GStreamer core might install a custom SIGSEGV handler
 * to better catch and report errors to the application. Currently this feature
 * is enabled by default when loading plugins.
 *
 * Applications might want to disable this behaviour with the
 * gst_segtrap_set_enabled() function. This is typically done if the application
 * wants to install its own handler without GStreamer interfering.
 *
 * @return <tt>true</tt> if GStreamer is allowed to install a custom SIGSEGV handler.
 */
bool segtrap_is_enabled();

/**
 * Applications might want to disable/enable the SIGSEGV handling of
 * the GStreamer core. See gst_segtrap_is_enabled() for more information.
 *
 * @param enabled Whether a custom SIGSEGV handler should be installed.
 */
void segtrap_set_enabled(bool enabled);

/**
 * By default GStreamer will perform scanning and rebuilding of the
 * registry file using a helper child process.
 *
 * Applications might want to disable this behaviour with the
 * gst_registry_fork_set_enabled() function, in which case new plugins
 * are scanned (and loaded) into the application process.
 *
 * @return <tt>true</tt> if GStreamer will use the child helper process when
 * rebuilding the registry.
 */
bool registry_fork_is_enabled();

/**
 * Applications might want to disable/enable spawning of a child helper process
 * when rebuilding the registry. See gst_registry_fork_is_enabled() for more
 * information.
 *
 * @param enabled Whether rebuilding the registry can use a temporary child helper process.
 */
void registry_fork_set_enabled(bool enabled);

/**
 * Forces GStreamer to re-scan its plugin paths and update the default
 * plugin registry.
 *
 * Applications will almost never need to call this function, it is only
 * useful if the application knows new plugins have been installed (or old
 * ones removed) since the start of the application (or, to be precise, the
 * first call to gst_init()) and the application wants to make use of any
 * newly-installed plugins without restarting the application.
 *
 * Applications should assume that the registry update is neither atomic nor
 * thread-safe and should therefore not have any dynamic pipelines running
 * (including the playbin and decodebin elements) and should also not create
 * any elements or access the GStreamer registry while the update is in
 * progress.
 *
 * Note that this function may block for a significant amount of time.
 *
 * @return <tt>true</tt> if the registry has been updated successfully (does not
 *          imply that there were changes), otherwise <tt>false</tt>.
 */
bool update_registry();


/*! A gstreamermm init example.
 * @example basics/init_gstreamermm.cc
 */

}//end namespace Gst

#endif //_GSTREAMERMM_INIT_H

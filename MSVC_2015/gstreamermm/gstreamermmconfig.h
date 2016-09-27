/* gstreamer/gstreamermmconfig.h.  Generated from gstreamermmconfig.h.in by configure.  */

/* This is part of gstreamermm */

#ifndef _GSTREAMERMM_CONFIG_H
#define _GSTREAMERMM_CONFIG_H

#include <glibmmconfig.h>

/* Major version of gstreamermm */
#define GSTREAMERMM_MAJOR_VERSION 1

/* Minor version of gstreamermm */
#define GSTREAMERMM_MINOR_VERSION 8

/* Micro version of gstreamermm */
#define GSTREAMERMM_MICRO_VERSION 0

/* Define when building gstreamermm as a static library. */
#define GSTREAMERMM_STATIC_LIB 1

/* Enable DLL-specific stuff only when not building a static library. */
#if (!defined(GSTREAMERMM_STATIC_LIB) && !defined(__CYGWIN__) && defined(_WIN32))
# define GSTREAMERMM_DLL 1
#endif

#ifdef GSTREAMERMM_DLL
# if defined(GSTREAMERMM_BUILD) && defined(_WINDLL)
   /* Do not dllexport as it is handled by gendef on MSVC. */
#  define GSTREAMERMM_API
# elif !defined(GSTREAMERMM_BUILD)
#  define GSTREAMERMM_API __declspec(dllimport)
# else
   /* Build a static library. */
#  define GSTREAMERMM_API
# endif /* GSTREAMERMM_BUILD - _WINDLL */
#else
# define GSTREAMERMM_API
#endif /* GSTREAMERMM_DLL */

#endif /* _GSTREAMERMM_CONFIG_H */

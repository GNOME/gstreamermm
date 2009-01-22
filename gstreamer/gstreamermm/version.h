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

#ifndef _GSTREAMERMM_VERSION_H
#define _GSTREAMERMM_VERSION_H

#include <glib.h>

namespace Gst
{

  /** Gets the version number of the gstreamermm library.
   *
   * @param major Pointer to a guint to store the major version number.
   * @param minor Pointer to a guint to store the minor version number.
   * @param micro Pointer to a guint to store the micro version number.
   */
  void version(guint& major, guint& minor, guint& micro);

}//end namespace Gst

#endif //_GSTREAMERMM_VERSION_H

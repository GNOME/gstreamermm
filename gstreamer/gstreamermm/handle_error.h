/* gstreamermm - a C++ wrapper for gstreamer
 *
 * Copyright 2009 The gstreamermm Development Team
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

#ifndef _GSTREAMERMM_HANDLE_ERROR_H
#define _GSTREAMERMM_HANDLE_ERROR_H

#include <glibmm/ustring.h>
#include <stdexcept>

namespace Gst
{

#ifndef DOXYGEN_SHOULD_SKIP_THIS
void gstreamermm_handle_error(const Glib::ustring& message);
#endif //DOXYGEN_SHOULD_SKIP_THIS

}

#endif //_GSTREAMERMM_HANDLE_ERROR_H

/* generate_defs_gst.cc
 *
 * Copyright (C) 2001 The Free Software Foundation
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public
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

#include "glibmm_generate_extra_defs/generate_extra_defs.h"

#include <gst/gst.h>
#include <gst/interfaces/colorbalance.h>
#include <gst/interfaces/colorbalancechannel.h>
#include <gst/interfaces/xoverlay.h>

int main (int argc, char *argv[])
{
  gst_init (&argc, &argv);
  std::cout << get_defs(GST_TYPE_COLOR_BALANCE)
            << get_defs(GST_TYPE_COLOR_BALANCE_CHANNEL)
            << get_defs(GST_TYPE_X_OVERLAY);

  return 0;
}

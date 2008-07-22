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

#include <glib.h>
#include <gst/gst.h>
#include <gst/base/gstbasesrc.h>
#include <gst/base/gstbasesink.h>
#include <gst/base/gstbasetransform.h>
#include <gst/base/gstpushsrc.h>
#include <gst/base/gstadapter.h>
#include <gst/base/gstcollectpads.h>
#include <gst/base/gstdataqueue.h>

int main (int argc, char *argv[])
{
  gst_init (&argc, &argv);

  // GStreamer core types:
  std::cout << get_defs(GST_TYPE_BUS)
            << get_defs(GST_TYPE_BIN)
            << get_defs(GST_TYPE_BUFFER)
            << get_defs(GST_TYPE_CAPS)
            << get_defs(GST_TYPE_CHILD_PROXY)
            << get_defs(GST_TYPE_CLOCK)
            << get_defs(GST_TYPE_ELEMENT)
            << get_defs(GST_TYPE_ELEMENT_FACTORY)
            << get_defs(GST_TYPE_EVENT)
            << get_defs(GST_TYPE_FORMAT)
            << get_defs(GST_TYPE_G_ERROR)
            << get_defs(GST_TYPE_GHOST_PAD)
            << get_defs(GST_TYPE_IMPLEMENTS_INTERFACE)
            << get_defs(GST_TYPE_INDEX)
            << get_defs(GST_TYPE_INDEX_FACTORY)
            << get_defs(GST_TYPE_MESSAGE)
            << get_defs(GST_TYPE_MINI_OBJECT)
            << get_defs(GST_TYPE_OBJECT)
            << get_defs(GST_TYPE_PAD)
            << get_defs(GST_TYPE_PAD_TEMPLATE)
            << get_defs(GST_TYPE_PIPELINE)
            << get_defs(GST_TYPE_PLUGIN)
            << get_defs(GST_TYPE_PLUGIN_FEATURE)
            << get_defs(GST_TYPE_QUERY)
            << get_defs(GST_TYPE_REGISTRY)
            << get_defs(GST_TYPE_SEGMENT)
            << get_defs(GST_TYPE_STRUCTURE)
            << get_defs(GST_TYPE_SYSTEM_CLOCK)
            << get_defs(GST_TYPE_TAG_LIST)
            << get_defs(GST_TYPE_TAG_SETTER)
            << get_defs(GST_TYPE_TASK)
            << get_defs(GST_TYPE_TYPE_FIND)
            << get_defs(GST_TYPE_TYPE_FIND_FACTORY)
            << get_defs(GST_TYPE_URI_HANDLER)
            << get_defs(GST_TYPE_XML)

  // GStreamer library base types:
            << get_defs(GST_TYPE_BASE_SRC)
            << get_defs(GST_TYPE_BASE_SINK)
            << get_defs(GST_TYPE_BASE_TRANSFORM)
            << get_defs(GST_TYPE_PUSH_SRC)
            << get_defs(GST_TYPE_ADAPTER)
            << get_defs(GST_TYPE_COLLECT_PADS)
            << get_defs(GST_TYPE_DATA_QUEUE)
            ;
  return 0;
}

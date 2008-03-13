// -*- Mode: C++; indent-tabs-mode: nil; c-basic-offset: 2 -*-

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

#include <gstreamermm.h>
#include <iostream>

int main (int argc, char* argv[])
{
  Gst::init(argc, argv);

  GstQuery* cquery = gst_query_new_position(GST_FORMAT_PERCENT);
  
  Glib::RefPtr<Gst::Query> query = Gst::Query::wrap(cquery);

  std::cout << "C++ query instance is !NULL: " << (bool)(query) << std::endl;

  Glib::RefPtr<Gst::QueryPosition> query_position = Glib::RefPtr<Gst::QueryPosition>::cast_dynamic(query);
  std::cout << "query is a Gst::QueryPosition: " << (bool)query_position  << std::endl;
  std::cout << "query type name: '" << Gst::get_name(query->get_query_type()) << "'" << std::endl;

  std::cout << "Query structure name: '" << query->get_structure()->get_name() << "'" << std::endl;

  return 0;
}

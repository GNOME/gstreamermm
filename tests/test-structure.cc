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
#include <glibmm/date.h>
#include <iostream>

int main (int argc, char* argv[])
{
  Gst::init(argc, argv);

  Gst::Structure structure("my_structure");

  structure.set_field(Glib::Quark("string"), "Hello; This is a ustring.");
  structure.set_field("integer", 100);
  structure.set_field("fraction", Gst::Fraction(1,2));
  structure.set_field("range", Gst::FractionRange(Gst::Fraction(1,2), Gst::Fraction(3,4)));
  Glib::Date date;
  date.set_time_current();
  structure.set_field("date", date);

  Glib::ustring value1;
  structure.get_field("string", value1);
  std::cout << "string value = '" << value1 << "'" << std::endl;

  int value2;
  structure.get_field("integer", value2);
  std::cout << "integer value = '" << value2 << "'" << std::endl;

  Gst::Fraction value3;
  structure.get_field("fraction", value3);
  std::cout << "fraction value = '" << value3.num << "/" <<
    value3.denom << "'" << std::endl;

  Gst::FractionRange value4;
  structure.get_field("range", value4);
  std::cout << "fractional range value = '[(" << value4.min.num << "/" <<
    value4.min.denom << "), (" << value4.max.num << "/" << value4.max.denom << ")]'" << std::endl;

  Glib::Date value5;
  structure.get_field("date", value5);
  std::cout << "date value = " <<  value5.get_month() << "/" <<
    (int) value5.get_day() << "/" << value5.get_year() << std::endl;

  return 0;
}

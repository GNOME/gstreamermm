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

#include <gstreamermm.h>
#include <glibmm/date.h>
#include <iostream>

int main (int argc, char* argv[])
{
  Gst::init(argc, argv);

  Gst::Structure structure("my_structure");

  structure.set_field(Glib::Quark("string"), "Hello; This is a ustring");
  structure.set_field("integer", 100);
  structure.set_field("fraction", Gst::Fraction(1,2));
  structure.set_field("range", Gst::FractionRange(Gst::Fraction(1,2),
    Gst::Fraction(3,4)));
  Glib::Date date;
  date.set_time_current();
  structure.set_field("date", date);
  structure.set_field("state", Glib::Value<Gst::State>::value_type(),
    Gst::STATE_PAUSED);

  Glib::ustring value1;
  structure.get_field("string", value1);
  std::cout << "string value after getting = '" << value1 << "'." << std::endl;

  int value2;
  structure.get_field("integer", value2);
  std::cout << "integer value after getting = " << value2 << "." <<
    std::endl;

  Gst::Fraction value3;
  structure.get_field("fraction", value3);
  std::cout << "fraction value after getting = " << value3.num << "/" <<
    value3.denom << "." << std::endl;

  Gst::FractionRange value4;
  structure.get_field("range", value4);
  std::cout << "fractional range value after getting = [(" <<
    value4.min.num << "/" << value4.min.denom << "), (" <<
    value4.max.num << "/" << value4.max.denom << ")]." << std::endl;

  Glib::Date value5;
  structure.get_field("date", value5);
  std::cout << "date value after getting = " <<  value5.get_month() << "/" <<
    (int) value5.get_day() << "/" << value5.get_year() << "." << std::endl;

  int state;
  structure.get_field("state", Glib::Value<Gst::State>::value_type(), state);
  if ((state = Gst::STATE_PAUSED))
    std::cout << "state value after getting = Gst::STATE_PAUSED." <<
      std::endl;

  return 0;
}

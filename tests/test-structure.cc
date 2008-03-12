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

  Gst::Structure structure("my_structure");

  Glib::Value<Glib::ustring> stringValue;
  stringValue.init(Glib::Value<Glib::ustring>::value_type());
  stringValue.set("Hello; This is a ustring.");

  Glib::Value<int> intValue;
  intValue.init(Glib::Value<int>::value_type());
  intValue.set(100);

  Glib::Value<Gst::Fraction> fractValue;
  fractValue.init(Glib::Value<Gst::Fraction>::value_type());
  fractValue.set(Gst::Fraction(1,2));

  Glib::Value<Gst::FractionRange> rangeValue;
  rangeValue.init(Glib::Value<Gst::FractionRange>::value_type());
  rangeValue.set(Gst::FractionRange(Gst::Fraction(1,2), Gst::Fraction(3,4)));

  structure.set_field(Glib::Quark("string"), stringValue).set_field("integer", intValue).set_field("fraction", fractValue).set_field("range", rangeValue);

  Glib::Value<Glib::ustring> value1;
  structure.get_field("string", value1);
  std::cout << "string value = '" << value1.get() << "'" << std::endl;

  Glib::Value<int> value2;
  structure.get_field("integer", value2);
  std::cout << "integer value = '" << value2.get() << "'" << std::endl;

  Glib::ValueBase value3;
  structure.get_field("fraction", value3);
  Gst::Fraction fract(value3);
  std::cout << "fraction value = '" << fract.num << "/" <<
      fract.denom << "'" << std::endl;

  Glib::ValueBase value4;
  structure.get_field("range", value4);
  Gst::FractionRange range(value4);
  std::cout << "fractional range value = '[(" << range.min.num << "/" <<
      range.min.denom << "), (" << range.max.num << "/" << range.max.denom <<
          ")]'" << std::endl;

  return 0;
}

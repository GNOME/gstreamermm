/*
 * test-value.cc
 *
 *  Created on: Aug 27, 2016
 *      Author: m.kolny
 */
#include "mmtest.h"
#include <gstreamermm.h>

TEST(ValueTest, TestDefaultRangeValue)
{
  Gst::Range<Gst::Fraction> fraction_range;
  Gst::Fraction default_fraction;

  ASSERT_EQ(default_fraction.denom, fraction_range.max.denom);
  ASSERT_EQ(default_fraction.num, fraction_range.min.num);
}

TEST(ValueTest, TestUserDefinedRangeValue)
{
  Gst::Range<int> int_range(10, 20);

  ASSERT_EQ(10, int_range.min);
  ASSERT_EQ(20, int_range.max);
}

TEST(ValueTest, TestIntRangeToGValue)
{
  Glib::Value<Gst::Range<int>> value;
  value.init(Glib::Value<Gst::Range<int>>::value_type());
  value.set(Gst::Range<int>(8000, 50000));

  Gst::Structure structure("my-structure");
  Glib::Value<int> v;
  v.init(G_TYPE_INT);
  v.set(12);
  structure.set_field("rate", value);

  Glib::Value<Gst::Range<int>> gst_value;
  structure.get_field("rate", gst_value);
  Gst::Range<int> range(gst_value);
  int max = range.max;

  ASSERT_EQ(max, 50000);
}


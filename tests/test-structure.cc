/*
 * test-structure.cc
 *
 *  Created on: 1 sie 2013
 *    Author: loganek
 */


#include "mmtest.h"
#include <gstreamermm.h>

using namespace Gst;

template<typename T>
void CheckEq(const T& expected, const T& output)
{
  EXPECT_EQ(expected, output);
}

template<>
void CheckEq(const Fraction& expected, const Fraction& output)
{
  EXPECT_EQ(expected.denom, output.denom);
  EXPECT_EQ(expected.num, output.num);
}

template<>
void CheckEq(const Range<Fraction>& expected, const Range<Fraction>& output)
{
  CheckEq(expected.min, output.min);
  CheckEq(expected.max, output.max);
}

template<>
void CheckEq(const Glib::DateTime& expected, const Glib::DateTime& output)
{
  CheckEq(expected.get_year(), output.get_year());
  CheckEq(expected.get_second(), output.get_second());
}

class StructureTest : public ::testing::Test
{
protected:
  Structure structure;

  virtual void SetUp()
  {
    structure = Structure("test-struct");
  }

  template<typename T>
  void CheckGetField(const T& expected, const Glib::ustring& field_name)
  {
    T output;
    structure.get_field(field_name, output);

    CheckEq(expected, output);
  }

  template<typename T>
  void CheckGetSetField(const T& expected, const Glib::ustring& field_name)
  {
    structure.set_field(field_name, expected);

    CheckGetField(expected, field_name);
  }
};

TEST_F(StructureTest, GetSetStringVariable)
{
  CheckGetSetField<std::string>("this is simple test", "string");
}

TEST_F(StructureTest, GetSetInt64Variable)
{
  structure.set_field<gint64>("int64", 123);
  guint64 val;
  MM_ASSERT_FALSE(structure.get_field<guint64>("int64", val));
}

TEST_F(StructureTest, GetSetIntegerVariable)
{
  CheckGetSetField(1234, "integer");
}

TEST_F(StructureTest, GetSetFractionVariable)
{
  CheckGetSetField(Fraction(5,6), "fraction");
}

TEST_F(StructureTest, GetSetFractionRangeVariable)
{
  CheckGetSetField(Gst::Range<Gst::Fraction>(Fraction(5,6), Fraction(13,14)), "fraction_range");
}

TEST_F(StructureTest, GetSetDateVariable)
{
  CheckGetSetField(Glib::Date(10, Glib::Date::DECEMBER, 1991), "date");
}

TEST_F(StructureTest, GetSetEnumVariable)
{
  State input_state = STATE_PAUSED;
  structure.set_field("state", Glib::Value<State>::value_type(), input_state);

  int output_state;
  structure.get_field("state", Glib::Value<State>::value_type(), output_state);

  EXPECT_EQ(input_state, (State)output_state);
}

TEST_F(StructureTest, CreateStructureFromFieldsList)
{
  structure = Structure("first", "field1", "sample string", "field2", 12);
  CheckGetField<std::string>("sample string", "field1");
  CheckGetField<Glib::ustring>("sample string", "field1");
  CheckGetField(12, "field2");
}

struct StructureTestStruct
{
  int x = 0;
  StructureTestStruct(int x) : x(x) {}
  StructureTestStruct() {}
};

TEST_F(StructureTest, CreateStructureWithCustomFields)
{
  structure = Structure("first", "field1", StructureTestStruct(14), "field2", StructureTestStruct(85));
  StructureTestStruct d1;
  Glib::Value<StructureTestStruct> d2;
  structure.get_field("field1", d1);
  structure.get_field("field2", d2);
  ASSERT_EQ(14, d1.x);
  ASSERT_EQ(85, d2.get().x);
}

TEST_F(StructureTest, UseStructureWithGlibValue)
{
  structure = Structure("dummy");
  Glib::Value<int> value;
  value.init(Glib::Value<int>::value_type());
  value.set(123);
  structure.set_field("field1", value);

  Glib::Value<int> read_value;
  structure.get_field("field1", read_value);
  ASSERT_EQ(123, read_value.get());
}

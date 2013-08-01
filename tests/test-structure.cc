/*
 * test-structure.cc
 *
 *  Created on: 1 sie 2013
 *      Author: loganek
 */


#include <gtest/gtest.h>
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
void CheckEq(const FractionRange& expected, const FractionRange& output)
{
    CheckEq(expected.min, output.min);
    CheckEq(expected.max, output.max);
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
    void CheckGetSetField(const T& expected, const Glib::ustring& field_name)
    {
        structure.set_field(field_name, expected);

        T output;
        structure.get_field(field_name, output);

        CheckEq(expected, output);
    }
};

TEST_F(StructureTest, GetSetStringVariable)
{
    CheckGetSetField<std::string>("this is simple test", "string");
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
    CheckGetSetField(FractionRange(Fraction(5,6), Gst::Fraction(13,14)), "fraction_range");
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

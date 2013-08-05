/*
 * test-caps.cc
 *
 *  Created on: Aug 1, 2013
 *      Author: m.kolny
 */

#include <gtest/gtest.h>
#include <gstreamermm.h>

using namespace Gst;

class CapsTest : public ::testing::Test
{
protected:
    Glib::RefPtr<Caps> caps;

    static int width;
    static Fraction framerate;

    template<typename T>
    void MakeAssert(const T& expected, const T& output)
    {
        EXPECT_EQ(expected, output);
    }
    void MakeAssert(const Fraction& expected, const Fraction& output)
    {
        EXPECT_EQ(expected.denom, output.denom);
        EXPECT_EQ(expected.num, output.num);
    }

    template<typename T>
    void CheckCaps(const Glib::ustring& field_name, T expected, int struct_id = 0)
    {
        T output;
        bool ok = caps->get_structure(struct_id).get_field(field_name, output);

        ASSERT_TRUE(ok);
        MakeAssert(expected, output);
    }
};

int CapsTest::width = 500;
Fraction CapsTest::framerate = Fraction(25, 1);

TEST_F(CapsTest, CapsCreateSimple)
{
    caps = Caps::create_simple("video/x-raw");

    ASSERT_TRUE(caps);
}

TEST_F(CapsTest, CapsCreateUsingStructure)
{
    Structure caps_struct("test-struct");
    caps_struct.set_field("width", width);
    caps_struct.set_field("framerate", framerate);

    caps = Caps::create(caps_struct);

    CheckCaps("width", width);
    CheckCaps("framerate", framerate);
}

TEST_F(CapsTest, AppendStructureToCaps)
{
    caps = Caps::create_simple("video/x-raw");

    Structure caps_struct("test-struct");
    caps_struct.set_field("width", width);

    caps->set_simple("framerate", framerate);
    caps->append_structure(caps_struct);

    CheckCaps("width", width, 1);
    CheckCaps("framerate", framerate);
}

TEST_F(CapsTest, AppendCapsToCaps)
{
    caps = Caps::create_simple("video/x-raw");
    caps->set_simple("framerate", framerate);

    Glib::RefPtr<Caps> new_caps = Caps::create_simple("video/x-raw");
    new_caps->set_simple("width", width);

    caps->append(new_caps);

    CheckCaps("width", width, 1);
    CheckCaps("framerate", framerate);
}

TEST_F(CapsTest, GetNonExistingValue)
{
    caps = Caps::create_simple("video/x-raw");

    int output;
    bool ok = caps->get_structure(0).get_field("nonexisting-value", output);

    ASSERT_FALSE(ok);
}

TEST_F(CapsTest, SetCapsToElement)
{
    Glib::RefPtr<Element> element = ElementFactory::create_element("multifilesrc", "source");

    gchar* str_caps = "image/jpeg, framerate=(fraction)2/1";

    element->set_property("caps", Caps::create_from_string(str_caps));
    element->get_property("caps", caps);

    ASSERT_STREQ(str_caps, caps->to_string().c_str());
}

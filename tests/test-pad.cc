/*
 * test-pad.cc
 *
 *  Created on: Aug 1, 2013
 *      Author: m.kolny
 */

#include <gtest/gtest.h>
#include <gstreamermm.h>

using namespace Gst;

class PadTest : public ::testing::Test
{
protected:
    Glib::RefPtr<Pad> pad;

    static Glib::ustring pad_name;
    static PadDirection pad_direction;

    void CheckPad()
    {
        ASSERT_TRUE(pad);
        EXPECT_EQ(pad_direction, pad->get_direction());
        ASSERT_STREQ(pad_name.c_str(), pad->get_name().c_str());
    }
};

PadDirection PadTest::pad_direction = PAD_SINK;
Glib::ustring PadTest::pad_name = "simple-pad";

TEST_F(PadTest, PadCorrectCreatedUsingPadDirection)
{
    pad = Pad::create(pad_name, pad_direction);

    CheckPad();
}

TEST_F(PadTest, PadCorrectCreatedUsingTemplate)
{
    Glib::RefPtr<Gst::Caps> caps = Gst::Caps::create_simple("video/x-raw,format=(yuv)");
    caps->set_simple("width", 500);
    caps->set_simple("framerate", Gst::Fraction(25, 1));

    Glib::RefPtr<PadTemplate> pad_tpl = PadTemplate::create("source-template", pad_direction, PAD_ALWAYS, caps);

    pad = Pad::create(pad_tpl, pad_name);

    CheckPad();
}


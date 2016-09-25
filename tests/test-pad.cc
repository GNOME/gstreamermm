/*
 * test-pad.cc
 *
 *  Created on: Aug 1, 2013
 *    Author: m.kolny
 */

#include "mmtest.h"
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
    MM_ASSERT_TRUE(pad);
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
  Glib::RefPtr<Gst::Caps> caps = Gst::Caps::create_simple("video/x-raw");
  caps->set_simple("width", 500);
  caps->set_simple("framerate", Gst::Fraction(25, 1));

  Glib::RefPtr<PadTemplate> pad_tpl = PadTemplate::create("source-template", pad_direction, PAD_ALWAYS, caps);

  pad = Pad::create(pad_tpl, pad_name);

  CheckPad();
}

TEST_F(PadTest, PadVerifyGetPadTemplateCaps)
{
  Glib::RefPtr<Gst::Caps> caps;
  {
    Glib::RefPtr<PadTemplate> pad_tpl =
      PadTemplate::create("source-template", pad_direction, PAD_ALWAYS, Caps::create_any());
    caps = Pad::create(pad_tpl, pad_name)->get_pad_template_caps();
  }
  ASSERT_EQ(1, caps->get_refcount());
}

TEST_F(PadTest, PadPushVerifyBufferRefcount)
{
  Glib::RefPtr<Gst::Buffer> buffer = Gst::Buffer::create();
  pad = Pad::create(pad_name, Gst::PAD_SRC);

  ASSERT_EQ(1, buffer->get_refcount());
  pad->push(std::move(buffer));
  MM_ASSERT_FALSE(buffer);
}

TEST_F(PadTest, PadEventDefault)
{
  Glib::RefPtr<Gst::Event> event = Gst::EventEos::create();
  pad = Pad::create(pad_name, pad_direction);

  ASSERT_EQ(1, event->get_refcount());
  pad->event_default(std::move(event));
  MM_ASSERT_FALSE(event);
}

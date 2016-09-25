/*
 * test-ghostpad.cc
 *
 *  Created on: Aug 5, 2013
 *    Author: m.kolny
 */

#include "mmtest.h"
#include <gstreamermm.h>

using namespace Gst;
using Glib::RefPtr;

TEST(GhostPadTest, CreatingGhostPad)
{
  Glib::ustring pad_name = "sample_name";
  PadDirection direction = PAD_SINK;
  RefPtr<GhostPad> ghost_pad = GhostPad::create(direction, pad_name);

  MM_ASSERT_TRUE(ghost_pad);
  ASSERT_EQ(direction, ghost_pad->get_direction());
  ASSERT_STREQ(pad_name.c_str(), ghost_pad->get_name().c_str());
}

TEST(GhostPadTest, CreatingGhostPadFromTemplate)
{
  PadDirection direction = PAD_SRC;
  RefPtr<Caps> caps = Caps::create_simple("video/x-raw-yuv");
  RefPtr<PadTemplate> templ = PadTemplate::create("pad-template", direction, PAD_ALWAYS, caps);

  RefPtr<GhostPad> ghost_pad = GhostPad::create(templ);

  MM_ASSERT_TRUE(ghost_pad);
  ASSERT_EQ(direction, ghost_pad->get_direction());
}

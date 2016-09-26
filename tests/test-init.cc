/*
 * test-init.cc
 *
 *  Created on: Aug 3, 2014
 *      Author: loganek
 */

#include "mmtest.h"
#include <gstreamermm.h>

using namespace Gst;
using Glib::RefPtr;

class InitTest : public ::testing::Test
{
protected:
  virtual void SetUp()
  {
    deinit();
  }
  static void TearDownTestCase()
  {
     init();
  }

};

TEST(InitTest, ShouldValidInitializeAndDeinitialize)
{
  init();
  MM_ASSERT_TRUE(is_initialized());
}

TEST(InitTest, ShouldReturnCorrectGstreamerVersion)
{
  guint major, minor, micro, nano;
  version(major, minor, micro, nano);
  /* todo fix it in gstreamer */
  EXPECT_EQ(major, (guint)GST_VERSION_MAJOR);
  EXPECT_EQ(minor, (guint)GST_VERSION_MINOR);
  EXPECT_EQ(micro, (guint)GST_VERSION_MICRO);
  EXPECT_EQ(nano, (guint)GST_VERSION_NANO);
}

TEST(InitTest, ShouldCorrectSetsSIGSEVHandling)
{
  bool prev = segtrap_is_enabled();
  segtrap_set_enabled(!prev);
  EXPECT_EQ(!prev, segtrap_is_enabled());
  segtrap_set_enabled(prev);
  EXPECT_EQ(prev, segtrap_is_enabled());
}

TEST(InitTest, ShouldCorrectSetsScanningRegistry)
{
  bool prev = registry_fork_is_enabled();
  registry_fork_set_enabled(!prev);
  EXPECT_EQ(!prev, registry_fork_is_enabled());
  registry_fork_set_enabled(prev);
  EXPECT_EQ(prev, registry_fork_is_enabled());
}

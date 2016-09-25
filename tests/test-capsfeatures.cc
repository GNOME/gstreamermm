/*
 * test-capsfeatures.cc
 *
 *  Created on: Nov 21, 2014
 *      Author: mkolny
 */

#include "mmtest.h"
#include <gstreamermm.h>

using namespace Gst;

TEST(CapsFeaturesTest, ShouldCorrectCreateEmptyFeature)
{
  CapsFeatures features;
  ASSERT_EQ(0u, features.get_size());
}

TEST(CapsFeaturesTest, AddRemoveFeaturesShouldWorkProperly)
{
  CapsFeatures features {GST_CAPS_FEATURE_MEMORY_SYSTEM_MEMORY};
  ASSERT_EQ(1u, features.get_size());
  ASSERT_STREQ(GST_CAPS_FEATURE_MEMORY_SYSTEM_MEMORY, features.get_nth(0).c_str());
  features.remove(GST_CAPS_FEATURE_MEMORY_SYSTEM_MEMORY);
  ASSERT_EQ(0u, features.get_size());
}



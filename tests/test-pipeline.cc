/*
 * test-pipeline.cc
 *
 *  Created on: Aug 14, 2014
 *      Author: m.kolny
 */

#include "mmtest.h"
#include <gstreamermm.h>

using namespace Gst;

TEST(PipelineTest, ShouldCorrectCreatePipelineWithSpecyficName)
{
  Glib::ustring name = "pipeline-name";
  Glib::RefPtr<Pipeline> pipeline = Pipeline::create(name);

  ASSERT_STREQ(name.c_str(), pipeline->get_name().c_str());
  ASSERT_EQ(1, pipeline->get_refcount());
}

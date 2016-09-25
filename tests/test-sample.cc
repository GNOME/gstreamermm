#include "mmtest.h"
#include <gstreamermm.h>

using namespace Gst;
using Glib::RefPtr;

TEST(SampleTest, CheckGetCapsMethod)
{
  auto caps = Caps::create_any();
  ASSERT_EQ(1, caps->get_refcount());

  auto sample = Sample::create(RefPtr<Buffer>(), caps, Segment(), Structure());
  ASSERT_EQ(2, caps->get_refcount());

  {
    auto tmp_caps = sample->get_caps();
    ASSERT_EQ(3, caps->get_refcount());
    MM_ASSERT_TRUE(tmp_caps->equals(caps));
  }
  
  ASSERT_EQ(2, caps->get_refcount());

}

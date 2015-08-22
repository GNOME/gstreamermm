#include <gtest/gtest.h>
#include <gstreamermm.h>

int main(int argc, char** argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  Gst::init(argc, argv);

  return RUN_ALL_TESTS();
}

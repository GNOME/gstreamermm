#include <gtest/gtest.h>

TEST(FajnyTest, FailTest)
{
  EXPECT_EQ(1, 2);
}

TEST(FajnyTest, OKTest)
{
  EXPECT_EQ(1, 1);
}

int main(int argc, char** argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

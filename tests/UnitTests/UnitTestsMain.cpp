#include <gtest/gtest.h>

TEST(GTestUnitTestSuite, AssertRuns) {
  ASSERT_TRUE(true);
}

/// ##########################################################################
/// @section Tests Entry Point
/// ##########################################################################

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

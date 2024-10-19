#include <gtest/gtest.h>

#define SHSML_IMPLEMENTATION
#include <SHSML.hpp>

TEST(SparseMatrixTest, BSRMatrixTest) { EXPECT_GE(1, 0); }

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

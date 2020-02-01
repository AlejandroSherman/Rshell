#include "gtest/gtest.h"

//include test files from the unit test folder

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

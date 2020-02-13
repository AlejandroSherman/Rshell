#ifndef _UNIT_TEST_CPP
#define _UNIT_TEST_CPP



#include "gtest/gtest.h"

//include test files from the unit test folder
#include "and_test.h"
#include "base_test.h"
#include "command_test.h"
#include "connector_test.h"
//#include "exit_test.h"
#include "or_test.h"
#include "semi_test.h"

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
#endif // !_UNIT_TEST_CPP

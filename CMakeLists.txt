CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

ADD_SUBDIRECTORY(googletest)

SET(CMAKE_CXX_STANDARD 11)

ADD_EXECUTABLE(rshell
src/main.cpp
src/base.cpp
src/command.cpp
src/and.cpp
src/or.cpp
src/semi.cpp
src/test.cpp
src/input.cpp
src/output_t.cpp
src/output_a.cpp
src/pipes.cpp
)

ADD_EXECUTABLE(test
unit_tests/unit_test.cpp
src/base.cpp
src/command.cpp
src/and.cpp
src/or.cpp
src/semi.cpp
src/test.cpp
src/input.cpp
src/output_t.cpp
src/output_a.cpp
src/pipes.cpp
)

TARGET_LINK_LIBRARIES(test gtest)

TARGET_COMPILE_DEFINITIONS(test PRIVATE gtest_disable_pthreads=ON)

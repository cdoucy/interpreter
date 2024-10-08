cmake_minimum_required(VERSION 3.0)
project(interpreter)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(TARGET interpreter-test)

set (PROJECT_ROOT ./..)
include(${PROJECT_ROOT}/src/src.cmake)
include(${PROJECT_ROOT}/inc/inc.cmake)
include(${PROJECT_ROOT}/tests/tst.cmake)

include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.13.0
)
FetchContent_MakeAvailable(googletest)

enable_testing()

SET(CMAKE_CXX_FLAGS "--coverage -fprofile-arcs -ftest-coverage ${CMAKE_CXX_FLAGS}")

add_executable(
    ${TARGET}
    ${SOURCES}
    ${TEST_SOURCES}
)

target_include_directories(
    ${TARGET}
    PUBLIC ${INCLUDES}
)

target_link_libraries(
    ${TARGET}
    GTest::gtest_main
    fmt::fmt
)

include(GoogleTest)
gtest_discover_tests(${TARGET})




cmake_minimum_required(VERSION 3.11)
project(day05)

set(CMAKE_CXX_STANDARD 17)


# Define support functions as library
# so that our test code can also loadit
add_library(support INTERFACE)
target_include_directories(
    support
    INTERFACE  ${CMAKE_CURRENT_SOURCE_DIR}/src
)


# Define main executible
add_executable(main src/day05.cpp)
target_link_libraries(main support)


# Define unit tsts
include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG v3.4.0
)

FetchContent_MakeAvailable(Catch2)


add_executable(tests tests/test_support.cpp)

target_link_libraries(
    tests
    PRIVATE Catch2::Catch2WithMain
    support
)


include(CTest)
include(Catch)
catch_discover_tests(tests)


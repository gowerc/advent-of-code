


cmake_minimum_required(VERSION 3.11)
project(day09)

set(CMAKE_CXX_STANDARD 20)


# Define support functions as library
# so that our test code can also loadit
add_library(support INTERFACE)
target_include_directories(
    support
    INTERFACE  ${CMAKE_CURRENT_SOURCE_DIR}/src
)


# Define main executible
add_executable(main src/day09.cpp)
target_link_libraries(main support)


# Define Unit test executible
add_executable(tests tests/test_support.cpp)



# Define unit tsts
include(FetchContent)

## Unittesting library
FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG v3.4.0
)
FetchContent_MakeAvailable(Catch2)


## Logging library
FetchContent_Declare(
    spdlog
    GIT_REPOSITORY https://github.com/gabime/spdlog
    GIT_TAG v1.15.1
)
FetchContent_MakeAvailable(spdlog)



target_link_libraries(main spdlog)

target_link_libraries(
    tests
    PRIVATE Catch2::Catch2WithMain
    support
    spdlog
)



include(CTest)
include(Catch)
catch_discover_tests(tests)


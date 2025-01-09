


cmake_minimum_required(VERSION 3.11)
project(day06)

set(CMAKE_CXX_STANDARD 17)


# Define support functions as library
# so that our test code can also loadit
# target_include_directories(
#     INTERFACE  ${CMAKE_CURRENT_SOURCE_DIR}/src
# )


# Define main executible
add_executable(main src/day06.cpp)


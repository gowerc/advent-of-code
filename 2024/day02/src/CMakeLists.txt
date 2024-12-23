
cmake_minimum_required(VERSION 3.11)

set(CMAKE_CXX_STANDARD 14)

add_executable(day02 main.cpp)

# Define support functions as library
# so that our test code can also loadit
add_library(funs INTERFACE)
target_include_directories(
    funs
    INTERFACE  ${CMAKE_CURRENT_SOURCE_DIR}
)

target_include_directories(day02 PUBLIC funs)
target_link_directories(day02 PUBLIC funs)
target_link_libraries(day02 funs)

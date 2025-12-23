
cmake_minimum_required(VERSION 3.13)
project(day03)


add_executable(${PROJECT_NAME} src/day03.cpp)

set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)

set(CMAKE_PREFIX_PATH "${CMAKE_PREFIX_PATH};/home/gowerc/.local/lib64/cmake/fmt")
find_package(fmt)
target_link_libraries(${PROJECT_NAME} PRIVATE fmt::fmt)


include(CTest)
if(BUILD_TESTING)
    add_subdirectory(tests)
endif()


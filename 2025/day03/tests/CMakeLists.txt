

add_executable(test01 "test_day03.cpp")

set_target_properties(test01 PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)

add_test(NAME test_cpp_0 COMMAND test01)

set(CMAKE_PREFIX_PATH "${CMAKE_PREFIX_PATH};/home/gowerc/.local/lib64/cmake/Catch2")
find_package(Catch2)
target_link_libraries(test01 PRIVATE Catch2::Catch2WithMain)

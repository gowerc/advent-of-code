

include(FetchContent)

# Fetch Catch2 library
FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG v3.4.0 # Replace with the desired version
)
FetchContent_MakeAvailable(Catch2)

# Add test executable
add_executable(tests test_funs.cpp)

# Link Catch2 and your library
target_link_libraries(
    tests
    PRIVATE Catch2::Catch2WithMain
    funs
)

# Enable CTest
include(CTest)
include(Catch)
catch_discover_tests(tests)

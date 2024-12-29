


cmake_minimum_required(VERSION 3.11)
project(day04)

set(CMAKE_CXX_STANDARD 17)

add_executable(main src/day04.cpp)



include(FetchContent)

FetchContent_Declare(
    CLI11
    GIT_REPOSITORY https://github.com/CLIUtils/CLI11
    GIT_TAG v2.4.2
)

FetchContent_MakeAvailable(CLI11)


target_link_libraries(
    main
    PRIVATE CLI11::CLI11
)



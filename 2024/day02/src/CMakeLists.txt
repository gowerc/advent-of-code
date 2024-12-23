
set(CMAKE_CXX_STANDARD 11)

add_executable(day02 main.cpp)

# Define support functions as library
# so that our test code can also loadit
add_library(funs funs.cpp)

target_include_directories(
    funs
    PUBLIC  ${CMAKE_CURRENT_SOURCE_DIR}
)

target_include_directories(day02 PUBLIC funs)
target_link_directories(day02 PUBLIC funs)
target_link_libraries(day02 funs)



#include <catch2/catch_test_macros.hpp>
#include "funs.h"
#include <vector>

TEST_CASE("max_difference() works") {
    
    std::vector<int> vec;

    vec = {1, 2, 3, 4};
    REQUIRE(max_difference(vec) == 1);

    vec = {1, 2, 3, 5};
    REQUIRE(max_difference(vec) == 2);

    vec = {10, 2, 3, 5};
    REQUIRE(max_difference(vec) == 8);

    vec = {10, 2, 30, 5};
    REQUIRE(max_difference(vec) == 28);
}


TEST_CASE("is_monotonic() works") {
    
    std::vector<int> vec;

    vec = {1, 2, 3, 4};
    REQUIRE(is_monotonic(vec) == true);

    vec = {1, 2, 3, 5};
    REQUIRE(is_monotonic(vec) == true);

    vec = {10, 2, 3, 5};
    REQUIRE(is_monotonic(vec) == false);

    vec = {10, 2, 30, 5};
    REQUIRE(is_monotonic(vec) == false);

    vec = {10, 8, 3, 1};
    REQUIRE(is_monotonic(vec) == true);

    vec = {10, 8, 7, 7};
    REQUIRE(is_monotonic(vec) == false);

    vec = {1, 2, 2, 5};
    REQUIRE(is_monotonic(vec) == false);
}

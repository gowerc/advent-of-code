#include <catch2/catch_test_macros.hpp>
#include "../src/day02funs.hpp"

// Basic test harness
TEST_CASE("Test case for add") {
    REQUIRE(is_invalid_id(111));
    REQUIRE(is_invalid_id(1212));
    REQUIRE(is_invalid_id(222222));
    REQUIRE(is_invalid_id(446446));
    REQUIRE(is_invalid_id(1188511885));
    REQUIRE(is_invalid_id(22));
    REQUIRE(is_invalid_id(99));
    REQUIRE(is_invalid_id(999));
    REQUIRE(is_invalid_id(565656));
    REQUIRE(is_invalid_id(824824824));
    REQUIRE(is_invalid_id(2121212121));
}



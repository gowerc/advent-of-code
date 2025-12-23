#include <catch2/catch_test_macros.hpp>
#include "../src/day03funs.hpp"

// Basic test harness
TEST_CASE("Test case for add") {
    REQUIRE(process01("1234") == 34);
    REQUIRE(process01("9119") == 99);
    REQUIRE(process01("1119") == 19);
    REQUIRE(process01("31412") == 42);
}

#include <catch2/catch_test_macros.hpp>

// Basic test harness
TEST_CASE("Test case for add") {
    REQUIRE(2 + 1 == 3);
    REQUIRE(2 + 2 == 4);
}


TEST_CASE( "vectors can be sized and resized", "[vector]" ) {
    // This setup will be run separately for each section
    std::vector<int> v( 5 );

    SECTION( "resizing bigger changes size and capacity" ) {
        v.resize( 10 );
        REQUIRE( v.size() == 10 );
        REQUIRE( v.capacity() >= 10 );
    }
}

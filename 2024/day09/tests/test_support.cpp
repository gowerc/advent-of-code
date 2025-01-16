
#include <catch2/catch_test_macros.hpp>
#include "../src/support.hpp"
#include <vector>
#include <string>
#include <list>

TEST_CASE("hello world") {
    
    std::vector<int> vec;
    std::string str;

    str = "1, 2, 3, 4";
    vec = {1, 2, 3, 4};
    REQUIRE(1 == 1);

}


TEST_CASE("calculate_check_sum()") {
    std::vector<int> x { 1 , 2 , 3, 4 ,  5 ,  6, 2,   1,  1,  1,  20,   1, -1 , 2};
    //                   0   1   2  3    4    5  6    7   8   9  10    11  12   13
    //                   0   2   6  12   20  30  12   7   8   9  200   11   0   26
    REQUIRE(calculate_check_sum(x) == 343);
}



TEST_CASE("parse_line()") {
    std::string line {"432111411641022054"};
    
    std::vector<int> result {
        0, 0, 0, 0,               // 4
        -1, -1, -1,               // 3
        1, 1,                     // 2
        -1,                       // 1
        2,                        // 1
        -1,                       // 1
        3, 3, 3, 3,               // 4
        -1,                       // 1
        4,                        // 1
        -1, -1, -1, -1, -1, -1,   // 6
        5, 5,5,5,                 // 4
        -1,                       // 1
                                  // 0
        -1, -1,                   // 2
        7, 7,                     // 2
                                  // 0
        8,8,8,8,8,                // 5
        -1, -1, -1, -1            // 4
    };
    REQUIRE(parse_line(line) == result);
}



TEST_CASE("sort_vector()") {
    
    std::vector<int> input {
        0, 0, 0, 0,               // 4
        -1, -1, -1,               // 3
        1, 1,                     // 2
        -1,                       // 1
        2,                        // 1
        -1,                       // 1
        3, 3, 3, 3,               // 4
        -1,                       // 1
        4,                        // 1
        -1, -1, -1, -1, -1, -1,   // 6
        5, 5,5,5,                 // 4
        -1,                       // 1
                                  // 0
        -1, -1,                   // 2
        7, 7,                     // 2
                                  // 0
        8,8,8,8,8,                // 5
        -1, -1, -1, -1            // 4
    };

    std::vector<int> output {
        0, 0, 0, 0,               // 4
        8, 8, 8,                  // 3
        1, 1,                     // 2
        8,                        // 1
        2,                        // 1
        8,                        // 1
        3, 3, 3, 3,               // 4
        7,                        // 1
        4,                        // 1
        7, 5, 5, 5, 5, -1,        // 6
        -1, -1, -1, -1,           // 4
        -1,                       // 1
        -1, -1,                   // 2
        -1, -1,                   // 2
        -1, -1, -1, -1, -1,       // 5
        -1, -1, -1, -1            // 4
    };

    REQUIRE(sort_vector_p1(input) == output);
}




TEST_CASE("sort_files_p2()") {

    std::list<File> files {
        {1, 2, 4},
        {2, 3, 3},
        {3, 2, 0},
        {4, 2, 0},
        {5, 6, 0}
    };

    std::list<File> expected {
        {1, 2, 0},
        {4, 2, 0},
        {3, 2, 0},
        {2, 3, 3},
        {5, 6, 0}
    };

    auto actual = sort_files_p2(files);
    REQUIRE(actual == expected);
}

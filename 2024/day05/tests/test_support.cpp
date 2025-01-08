
#include <catch2/catch_test_macros.hpp>
#include "../src/suppport.hpp"
#include <vector>
#include <string>

TEST_CASE("string_to_int_vec()") {
    
    std::vector<int> vec;
    std::string str;

    str = "1, 2, 3, 4";
    vec = {1, 2, 3, 4};
    REQUIRE(string_to_int_vec(str) == vec);

    str = "10,2,3";
    vec = {10, 2, 3};
    REQUIRE(string_to_int_vec(str) == vec);

}



TEST_CASE("is_valid_page()") {
    std::vector<int> page;
    std::map<int, std::vector<int>> rules;

    page = { 1 , 2 , 3 , 4};
    rules[1] = std::vector<int> {2, 3, 4};
    rules[2] = std::vector<int> {3, 4};
    rules[3] = std::vector<int> {4};
    REQUIRE( is_valid_page(page, rules) == true );

    page = { 1 , 2 , 3 , 4};
    rules[1] = std::vector<int> {2, 3, 4};
    rules[2] = std::vector<int> {3, 4};
    rules[3] = std::vector<int> {4, 1};
    REQUIRE( is_valid_page(page, rules) == false );

}


TEST_CASE ("order_by_rules()") {
    std::map<int, std::vector<int>> rules;
    rules[29] = {13};
    rules[53] = {29, 13};
    rules[61] = {13, 53, 29};
    rules[47] = {53, 13, 61, 29};
    rules[75] = {29, 53, 47, 61, 13};
    rules[97] = {13, 61, 29, 53, 47, 75};

    std::vector<int> starting {75, 53, 13, 97, 47, 61, 29};
    std::vector<int> expected {97, 75, 47, 61, 53, 29, 13};
    REQUIRE( order_by_rules(starting, rules) == expected);


    rules.clear();
    rules[4] = {10};
    rules[3] = {4, 10};
    rules[5] = {3, 10, 4};
    rules[2] = {5, 4, 3};
    rules[6] = {2, 3};
    starting = {2, 3, 4, 10, 5, 6};
    expected = {6, 2, 5, 3, 4, 10};
    REQUIRE( order_by_rules(starting, rules) == expected);


    rules.clear();
    rules[25] = {57, 32, 62, 63, 33, 77, 71, 19, 91, 21, 38, 72, 97, 93, 95, 12, 15, 82, 54, 53, 22, 67, 49, 17};
    rules[91] = {71, 63, 77, 49, 57, 51, 53, 33, 38, 82, 93, 62, 32, 41, 15, 22, 97, 21, 54, 17, 72, 95, 67, 19};
    rules[77] = {19, 79, 31, 22, 21, 67, 97, 62, 54, 82, 32, 51, 71, 53, 44, 95, 38, 57, 41, 24, 13, 93, 72, 17};
    rules[32] = {24, 21, 93, 62, 51, 72, 41, 71, 19, 95, 17, 53, 57, 65, 37, 67, 38, 44, 97, 13, 31, 79, 54, 22};
    rules[55] = {49, 82, 72, 33, 15, 93, 12, 38, 22, 89, 58, 21, 62, 67, 19, 97, 91, 17, 32, 25, 57, 63, 77, 53};
    starting = {25, 32, 77, 91, 55};
    expected = {55, 25, 91, 77, 32};
    REQUIRE( order_by_rules(starting, rules) == expected);

}

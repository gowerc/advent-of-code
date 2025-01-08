
#include <iostream>
#include <map>
#include <vector>
#include "suppport.hpp"



int main () {

    std::map<int, std::vector<int>> rules = parse_rules();
    std::vector<std::vector<int>> pages = parse_pages();

    int total{0};
    int total_2{0};
    for (auto page: pages) {
        if (is_valid_page(page, rules)) {
            total += page.at(page.size() / 2);
        } else {
            std::vector<int> page_fixed = order_by_rules(page, rules);
            total_2 += page_fixed.at(page_fixed.size() / 2);
        }
    }
    std::cout << "Total = " << total << std::endl;
    std::cout << "Total 2 = " << total_2 << std::endl;

}

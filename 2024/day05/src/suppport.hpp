#include <iostream>
#include <list>
#include <algorithm>
#include <map>
#include <unordered_set>
#include <vector>
#include <fstream>
#include <sstream>

static std::string file_pages {"./data/pages_full.txt"};
static std::string file_rules {"./data/rules_full.txt"};

std::map<int, std::vector<int>> parse_rules() {

    std::ifstream in_file { file_rules };
    if (!in_file.is_open() ) {
        std::cout << "It's over" << std::endl;
        std::exit(101);
    }

    std::string line;
    std::map<int, std::vector<int>> result;
    while (std::getline(in_file, line)) {
        std::istringstream iss(line);
        std::string part1, part2;

        if (std::getline(iss, part1, '|') && std::getline(iss, part2)) {
            int x = std::stoi(part1);
            int y = std::stoi(part2);

            if (result.find(x) != result.end()) {
                result[x].push_back(y);
            } else {
                result[x] = std::vector<int>{y};
            }
        }
    }
    return result;
}



std::vector<int> string_to_int_vec (std::string line) {
    std::vector<int> numbers;
    std::istringstream iss(line);
    std::string token;
    while (std::getline(iss, token, ',')) {
        numbers.push_back(std::stoi(token));
    }
    return numbers;
}



std::vector<std::vector<int>> parse_pages() {
    std::ifstream in_file { file_pages };
    if (!in_file.is_open() ) {
        std::cout << "It's over" << std::endl;
        std::exit(101);
    }

    std::vector<std::vector<int>> result;

    std::string line;
    while (!in_file.eof()) {
        std::getline(in_file, line);
        result.push_back(string_to_int_vec(line));
    }
    return result;
}


bool is_valid_page(std::vector<int> page, std::map<int, std::vector<int>> rules) {
    for (int i{1}; i < page.size(); i ++ ) {
        for (int j{0} ; j < i; j++) {
            for (auto val: rules[page.at(i)]) {
                if (val == page.at(j)) {
                    return false;
                }
            }
        }
    }
    return true;
}


std::vector<int> order_by_rules(std::vector<int> page, std::map<int, std::vector<int>> rules) {
    std::sort(
        page.begin(),
        page.end(),
        [&rules](int x, int y) {
            for ( int i : rules[x]) {
                if (i == y) return true;
            }
            return false;
        }
    );
    return page;
}

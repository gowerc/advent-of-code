
#include <iostream>
#include <map>
#include <vector>
#include <fstream>
#include <sstream>

std::map<int, std::vector<int>> parse_rules() {

    std::ifstream in_file { "./data/rules.txt" };
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
    std::ifstream in_file { "./data/pages.txt" };
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



int main () {

    std::map<int, std::vector<int>> rules = parse_rules();
    std::vector<std::vector<int>> pages = parse_pages();

    int total{0};
    for (int i{0}; i < pages.size(); i++) {
        if (is_valid_page(pages.at(i), rules)) {
            total += pages.at(i).at(pages.at(i).size() / 2);
        }
    }
    std::cout << "Total = " << total << std::endl;
    
}

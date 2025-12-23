
#include <iostream>
#include <fstream>
#include <fmt/core.h>
#include "day02funs.hpp"

void task1 () {
    std::ifstream fi("data/input.txt");
    std::string line;
    long long total{0};
    while (std::getline(fi, line, ',')) {
        long left, right, pos;
        pos = line.find('-');
        left = std::stol(line.substr(0, pos));
        right = std::stol(line.substr(pos + 1, line.size()));
        for (long i{left}; i <= right; i++) {
            std::string i_c(std::to_string(i));
            if (i_c.size() % 2 != 0) continue;
            std::string left_c = i_c.substr(0, i_c.size()/2);
            std::string right_c = i_c.substr(i_c.size()/2, i_c.size());
            if (left_c == right_c) {
                total += i;
            }
        }
    }
    fmt::print("Task 1 - Total = {}\n", total);
}

void task2 () {
    std::ifstream fi("data/input.txt");
    std::string line;
    long long total{0};
    while (std::getline(fi, line, ',')) {
        long left, right, pos;
        pos = line.find('-');
        left = std::stol(line.substr(0, pos));
        right = std::stol(line.substr(pos + 1));
        for (long i{left}; i <= right; i++) {
            if (is_invalid_id(i)) {
                total += i;
            }
        }
    }
    fmt::print("Task 2 - Total = {}\n", total);
}


int main() {
    fmt::print("Hello {}\n\n", "World");
    task1();
    task2();
}
 
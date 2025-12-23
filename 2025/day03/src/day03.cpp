
#include <iostream>
#include <fstream>
#include <fmt/core.h>
#include <string>
#include "./day03funs.hpp"

int main() {
    long total{0};
    std::string line;
    std::ifstream fi{"data/input.txt"};
    while(std::getline(fi, line)) {
        total+=process01(line);
    }
    fmt::print("Total = {}\n", total);
}

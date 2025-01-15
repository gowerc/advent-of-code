
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "funs.hpp"


int main () {
    std::cout << "hello world" << std::endl;

    std::ifstream in_file {"./data/data.txt"};
    if (!in_file.is_open()) {
        std::exit(1);
    }

    int total{0};
    int total_damp{0};
    std::string line{};
    std::istringstream iss;

    while (!in_file.eof()) {
        std::getline(in_file, line);
        std::istringstream iss{line};
        std::vector<int> vec;
        int val;
        while(iss >> val) {
            vec.push_back(val);
        }
        if (is_valid(vec)) total++;
        if (is_valid_damp(vec)) total_damp++;
    }
    std::cout << "total = " << total << std::endl;
    std::cout << "total_damp = " << total_damp << std::endl;
}

int add(int a, int b) {
    return a + b;
}
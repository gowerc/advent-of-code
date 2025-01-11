#include <sstream>
#include <iostream>
#include <functional>
#include <vector>
#include <cmath>
#include <algorithm>
#include <fstream>
#include <string>
#include <format>

using fun = std::function<long long(long long, long long)>;
long long f_sum(long long x, long long y) { return x + y ; };
long long f_prod(long long x, long long y) { return x * y; };

/**
 * For a given integer creates a vector of all possible function
 * combinations based on a binary expansion e.g. 3 =
 * 000
 * 001
 * 010
 * 011
 * 100
 * 101
 * 110
 * 111
 * Where 0 = `f_sum`, 1 = `f_prod`
 */
std::vector<std::vector<fun>> expand_funs(long long n) {
    std::vector<fun> ops {f_sum, f_prod};
    std::vector<std::vector<fun>> result;
    for (long long i{0}; i < std::pow(2 , n) ; i++) {
        std::vector<fun> hold;
        for (long long j{0}; j < n ; j++ ) {
            long long index = (i >> j) & 1;
            hold.push_back(ops.at(index));
        }
        result.push_back(hold);
    }
    return result;
}


/**
 * Takes a vector of integers and summarises them by recursively
 * applying the function in funs e.g. `result = funs[i](result, vals[i + 1])`
 * `vals` must be of length `funs.size() + 1`
 *
 * @param vals Vector of long longs to be combined (added or multiplied)
 * @param funs Vector of functions to apply to `vals` 
 */
long long apply_funs(std::vector<long long> vals, std::vector<fun> funs) {
    if (vals.size() != (funs.size() + 1)) {
        std::cout << "ERROR: incompatible vector sizes" << std::endl;
        std::exit(123);
    }
    long long result{vals.at(0)};
    for (long long i{0}; i < funs.size(); i++) {
        result = funs.at(i)(result, vals.at(i + 1));
    }
    return result;
}



bool is_valid(std::vector<long long> vals, long long target) {
    auto all_funs = expand_funs(vals.size() - 1);
    for (auto funs: all_funs) {
        if ( apply_funs(vals, funs) == target) return true;
    }
    return false;
}


std::pair<long long, std::vector<long long>> parse_line(const std::string& line) {
    std::istringstream iss(line);
    std::string first_val;
    std::getline(iss, first_val, ':');

    long long index = std::stoll(first_val);
    std::vector<long long> vals;
    std::string val;
    while (iss >> val) {
        vals.push_back(std::stoll(val));
    }
    return {index, vals};
}

std::vector<std::pair<long long, std::vector<long long>>> get_inputs(const std::string& filename) {
    std::vector<std::pair<long long, std::vector<long long>>> result;
    std::ifstream in_file{filename};
    if (!in_file.is_open()) {
        std::cerr << "Unable to open file" << std::endl;
        std::exit(123);
    }

    std::string line;
    while (std::getline(in_file, line)) {
        if (line.empty()) continue;
        try {
            result.push_back(parse_line(line));
        } catch (const std::exception& e) {
            std::cerr << "Error processing line: " << line << "\n";
        }
    }
    return result;
}


int main () {


    auto inputs = get_inputs("./data/data_full.txt");

    size_t total{0};
    for (auto item: inputs) {
        if ( is_valid(item.second, item.first)) {
            total += item.first;
        }
    }

    std::cout << std::format("Total = {}", total) << std::endl;
}

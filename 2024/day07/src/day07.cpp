//
//
// Original answer brute force calculated all the operation combinations and then applied
// them. Didn't realise you could just use recursion which significantly speeds up performance
//
//

#include <sstream>
#include <iostream>
#include <functional>
#include <vector>
#include <cmath>
#include <algorithm>
#include <fstream>
#include <string>
#include <format>



bool is_valid_p1(const std::vector<long long> & vals, long long target, long long current_val, size_t index) {
    if (index == vals.size()) {
        return current_val == target;
    }
    if ( is_valid_p1(vals, target, current_val + vals[index], index + 1)) {
        return true;
    }
    if ( is_valid_p1(vals, target, current_val * vals[index], index + 1)) {
        return true;
    }
    return false;
}


bool is_valid_p2(const std::vector<long long> & vals, long long target, long long current_val, size_t index) {
    if (index == vals.size()) {
        return current_val == target;
    }
    if ( is_valid_p2(vals, target, current_val + vals[index], index + 1)) {
        return true;
    }
    if ( is_valid_p2(vals, target, current_val * vals[index], index + 1)) {
        return true;
    }
    if ( is_valid_p2(vals, target, std::stoll(std::to_string(current_val) + std::to_string(vals[index])), index + 1)) {
        return true;
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
        if ( is_valid_p1(item.second, item.first, item.second[0], 1)) {
            total += item.first;
        }
    }
    std::cout << std::format("Part-One Total = {}", total) << std::endl;


    size_t total_2{0};
    for (auto item: inputs) {
        if ( is_valid_p2(item.second, item.first, item.second[0], 1)) {
            total_2 += item.first;
        }
    }
    std::cout << std::format("Part-Two Total = {}", total_2) << std::endl;

}




// using fun = std::function<long long(long long, long long)>;
// long long f_sum(long long x, long long y) { return x + y ; };
// long long f_prod(long long x, long long y) { return x * y; };


// std::vector<fun> ops_two {f_sum, f_prod};
// std::vector<fun> ops_three {f_sum, f_prod, f_concat};


// std::vector<std::vector<fun>> cartesian_product(const std::vector<fun> & ops, int n_digits) {
//     size_t n_elements {ops.size()};
//     std::vector<std::vector<fun>> result;
//     std::vector<int> hold_index(n_digits, 0);
//     std::vector<fun> hold_fun(n_digits);
//     for (int i{1}; i <= std::pow(n_elements, n_digits); i++) {
//         for (int x{0}; x < hold_fun.size() ; x ++) {
//             hold_fun.at(x) = ops.at(hold_index.at(x));
//         }
//         result.push_back(hold_fun);
//         for (int j{1}; j <= n_digits ; j++) { 
//             if ((i % static_cast<long long>(std::pow(n_elements, j - 1))) == 0) {
//                 hold_index.at(j - 1) ++;
//                 if (hold_index.at(j - 1) >= n_elements) hold_index.at(j - 1) = 0;
//             }
//         }
//     }
//     return result;
// }



/**
 * Takes a vector of integers and summarises them by recursively
 * applying the function in funs e.g. `result = funs[i](result, vals[i + 1])`
 * `vals` must be of length `funs.size() + 1`
 *
 * @param vals Vector of long longs to be combined (added or multiplied)
 * @param funs Vector of functions to apply to `vals` 
 */
// long long apply_funs(const std::vector<long long> & vals, std::vector<fun> & funs) {
//     if (vals.size() != (funs.size() + 1)) {
//         std::cout << "ERROR: incompatible vector sizes" << std::endl;
//         std::exit(123);
//     }
//     long long result{vals.at(0)};
//     for (long long i{0}; i < funs.size(); i++) {
//         result = funs[i](result, vals[i + 1]);
//     }
//     return result;
// }

// bool is_valid(const std::vector<long long> & vals, long long target, const std::vector<fun> & ops) {
//     std::vector<std::vector<fun>> all_funs = cartesian_product(ops, vals.size() - 1);
//     for (std::vector<fun> funs: all_funs) {
//         if ( apply_funs(vals, funs) == target) return true;
//     }
//     return false;
// }

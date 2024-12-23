#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>


int max_difference (std::vector<int> vec) {
    int max_diff {0};
    for (int i{1}; i < vec.size(); i++) {
        int diff = std::abs(vec.at(i) - vec.at(i-1));
        if ( diff > max_diff) max_diff = diff;
    }
    return max_diff;
}

bool is_monotonic (std::vector<int> vec) {
    if (vec.size() <= 2) return true;
    int diff = vec.at(1) - vec.at(0);
    bool is_pos;
    if (diff > 0) {
        is_pos = true;
    } else if (diff < 0) {
        is_pos = false;
    } else {
        return false;
    }
    for (int i{1}; i < vec.size(); i++) {
        if (is_pos) {
            if (vec.at(i) <= vec.at(i-1)) return false;
        } else {
            if (vec.at(i) >= vec.at(i-1)) return false;
        }
    }
    return true;
}


int main () {
    std::cout << "hello world" << std::endl;

    // std::vector<int> tvec {25, 23, 25, 28, 29, 32, 35};
    // std::cout << is_monotonic(tvec) << std::endl;

    std::ifstream in_file {"./data.txt"};
    if (!in_file.is_open()) {
        std::exit(1);
    }

    int total = 0;
    std::string line{};
    std::istringstream iss;
    
    int i{0};
    while (!in_file.eof()) {
        std::getline(in_file, line);
        std::istringstream iss{line};
        std::vector<int> vec;
        int val;
        
        while(iss >> val) {
            vec.push_back(val);
        }



        int max_diff = max_difference(vec);
        bool is_mono = is_monotonic(vec);
        bool add_to_total{false};


        if (1 <= max_diff && max_diff <= 3 ) {
            if (is_mono) {
                add_to_total = true;
            }
        }
        if (add_to_total) total++;

        // std::cout << "line         = " << line << std::endl;
        // std::cout << "vector size  = " << vec.size() << std::endl;
        // std::cout << "max_diff     = " << max_diff << std::endl;
        // std::cout << "is_mono      = " << is_mono << std::endl;
        // std::cout << "add_to_total = " << add_to_total << std::endl;
        // std::cout << "total        = " << total << std::endl;
        // std::cout << std::endl;
        // if (i > 12) break;
        // i++;
    }
    
    std::cout << total << std::endl;
}



#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <cmath>
#include <algorithm>



int main () {
    std::cout << "Hello World!" << std::endl;

    std::ifstream in_file {"./data/data_full.txt"};
    if (!in_file.is_open()) {
        std::cout << "Unable to open file" << std::endl;
        std::exit(101);
    }

    std::vector<std::vector<int>> grid_count;
    std::vector<std::vector<int>> grid_type;
    std::vector<std::vector<char>> grid_char;
    std::pair<int, int> pos;
    char c;

    int current_row_index {0};
    int current_col_index {-1};

    grid_count.push_back(std::vector<int>{});
    grid_type.push_back(std::vector<int>{});
    grid_char.push_back(std::vector<char>{});

    while (in_file.get(c)) {
        if (c == '\n') {
            current_col_index = -1;
            current_row_index++;
            grid_count.push_back(std::vector<int>{});
            grid_type.push_back(std::vector<int>{});
            grid_char.push_back(std::vector<char>{});
            continue;
        }
        current_col_index++;
        int type;
        switch(c) {
            case '.': type = 1; break;
            case '#': type = 2; break;
            case '^':
                type = 1;
                pos = {current_row_index, current_col_index};
                break;
        }
        grid_count.at(current_row_index).push_back(0);
        grid_type.at(current_row_index).push_back(type);
        grid_char.at(current_row_index).push_back(c);
    }

    // for (int i{0}; i <= current_row_index; i++) {
    //     for (int j{0}; j <= current_col_index; j++) {
    //         std::cout << grid_char.at(i).at(j);
    //     }
    //     std::cout << std::endl;
    // }

    std::pair<int, int> dir{-1, 0};

    std::cout << "Starting pos = " << "(" << pos.first << ", " << pos.second << ")" << std::endl;
    std::cout << "current_row_index = " << current_row_index << std::endl;
    std::cout << "current_col_index = " << current_col_index << std::endl;
    

    grid_count.at(pos.first).at(pos.second) ++;
    while(true) {

        if (
            (pos.first + dir.first) >= 0 && (pos.second + dir.second) >= 0 &&
            (pos.first + dir.first) <= current_row_index && (pos.second + dir.second) <= current_col_index
        ) {
            if (grid_type.at(pos.first + dir.first).at(pos.second + dir.second) == 2) {
                int new_r = dir.second;
                int new_c = - dir.first;
                dir.first = new_r;
                dir.second = new_c;
                std::cout << "TURNING = (" << dir.first << ", " << dir.second << ")" << std::endl;
            }
        }

        if (grid_type.at(pos.first).at(pos.second) == 1) {
            pos.first += dir.first;
            pos.second += dir.second;
        }

        if (
            pos.first >= current_row_index ||
            pos.second >= current_col_index ||
            pos.first < 0 ||
            pos.second < 0
        ) {
            break;
        }

        grid_count.at(pos.first).at(pos.second) ++;
        std::cout << "(" << pos.first << ", " << pos.second << ")" << std::endl;
    }

    int total {0};
    std::for_each(
        grid_count.begin(),
        grid_count.end(),
        [&total] (std::vector<int> x) {
            total += std::count_if(
                x.begin(),
                x.end(),
                [](int x) {
                    return x >= 1;
                }
            );
        }
    );
    std::cout << "Total = " << total << std::endl;
}



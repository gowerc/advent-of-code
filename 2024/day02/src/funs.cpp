#include <iostream>
#include <vector>

int max_difference (const std::vector<int> vec) {
    int max_diff {0};
    for (int i{1}; i < vec.size(); i++) {
        int diff = std::abs(vec.at(i) - vec.at(i-1));
        if ( diff > max_diff) max_diff = diff;
    }
    return max_diff;
}

bool is_monotonic (const std::vector<int> vec) {
    if (vec.size() <= 1) return true;
    bool increasing = true;
    bool decreasing = true;
    for (int i{1}; i < vec.size(); i++) {
        int diff { vec.at(i) - vec.at(i -1)};
        if (diff > 0) decreasing = false;
        if (diff < 0) increasing = false;
        if (diff == 0) return false;
    }
    return increasing || decreasing;
}


bool is_valid(const std::vector<int> vec) {
    int max_diff = max_difference(vec);
    bool is_mono = is_monotonic(vec);
    if (1 <= max_diff && max_diff <= 3 ) {
        if (is_mono) {
            return true;
        }
    }
    return false;
}


bool is_valid_damp(const std::vector<int> vec) {
    if (is_valid(vec)) return true;
    for (int i{0}; i < vec.size(); i ++) {
        std::vector<int> vec2{vec};
        vec2.erase(vec2.begin() + i);
        if (is_valid(vec2)) return true;
    }
    return false;
}

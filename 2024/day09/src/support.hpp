#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <fstream>


void printme(std::vector<char> x) {
    for ( auto z: x) std::cout << z;
    std::cout << std::endl;
}
void printme(std::vector<int> x) {
    for ( auto z: x) {
        if ( z < 0) {
            std::cout << ". ";
        } else {
            std::cout << z << " ";
        }
    }
    std::cout << std::endl;
}


std::vector<int> sort_vector_p1(std::vector<int> inp) {
    std::vector<int> value_index;
    std::vector<int> space_index;
    for (int i{0}; i < inp.size(); i++) {
        int val = inp[i];
        if (val < 0) {
            space_index.push_back(i);
        } else {
            value_index.push_back(i);
        }
    }
    std::reverse(value_index.begin(), value_index.end());
    int i{0};
    int si = space_index[i];
    int vi = value_index[i];
    while (si < vi) {
        int temp = inp[si];
        inp[si] = inp[vi];
        inp[vi] = temp;
        i++;
        si = space_index[i];
        vi = value_index[i];
    }
    return inp;
}


long long calculate_check_sum (std::vector<int> x) {
    long long result{0};
    for (int i{0}; i < x.size(); i++) {
        if (x[i] < 0) continue;
        result += i * x[i];
    }
    return result;
}


std::vector<int> parse_line (std::string x) {
    std::vector<int> result;
    bool insert {true};
    int val{0};
    for (int i{0}; i < x.size() ; i++ ) {
        int times = x.at(i) - '0';
        for ( int j{0}; j < times; j ++ ){
            if (insert) {
                result.push_back(val);
            } else {
                result.push_back(-1);
            }
        }
        if (insert) {
            val ++;
        }
        insert = !insert;
    }
    return result;
}

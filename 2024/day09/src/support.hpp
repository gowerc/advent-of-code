#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
#include <string>
#include <fstream>


#include "spdlog/spdlog.h"


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


std::vector<int> parse_line_p1 (std::string x) {
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


struct File {
    int id;
    int size;
    int space;
    bool operator==(const File &other) const {
        return id == other.id &&
            size == other.size &&
            space == other.space;
    }
    friend std::ostream &operator<<(std::ostream &os, const File &obj) {
        os << "{ID: " << obj.id
           << ", size: " << obj.size
           << ", space: " << obj.space << "}";
        return os;
    }
};


std::list<File> parse_line_p2(std::string x) {
    std::list<File> result;
    if (x.size() % 2 != 0) {
        x.push_back('0');
    }
    for (int i{0}; i*2 < x.size(); i++) {
        int index = i * 2;
        result.emplace_back(i, x.at(index) - '0', x.at(index + 1) - '0');
    }
    return result;
}


std::list<File> sort_files_p2(std::list<File> files) {
    spdlog::info("Entered sort_files_p2 {}", 1);
    auto c_itr = std::prev(files.end());
    auto s_itr = files.begin();
    while (c_itr != s_itr) {
        int increase_space{0};
        auto t_itr = s_itr;
        while(t_itr != c_itr) {
            if (t_itr->space >= c_itr->size && c_itr->size != 0) {
                File new_file{*c_itr};
                increase_space = c_itr->space + c_itr->size;
                c_itr = files.erase(c_itr);
                t_itr++;
                std::list<File>::iterator new_itr = files.insert(t_itr, new_file);
                t_itr = std::prev(std::prev(t_itr));
                new_itr->space = t_itr->space - new_itr->size;
                t_itr->space = 0;
                break;
            }
            t_itr = std::next(t_itr);
        }
        c_itr = std::prev(c_itr);
        c_itr->space += increase_space;
    }
    return files;
}


std::vector<int> convert_to_int_vec(std::list<File> files) {
    std::vector<int> result;
    for (auto file: files) {
        for (int i{0}; i < file.size ; i ++ ) {
            result.push_back(file.id);
        }
        for (int i{0}; i < file.space ; i ++ ) {
            result.push_back(-1);
        }
    }
    return result;
}

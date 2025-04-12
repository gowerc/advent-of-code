#include <algorithm>
#include <iostream>
#include <list>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <unordered_map>


// Initial approach was to model via a linked list and follow the rules exactly
// This was too slow for p2 so to simplify the problem used a map to store the number
// of times each element is in the list as the specific order doesn't matter
// this stops duplication e.g. if 20 is in the list 10 times we only have to split it once
// where as in the linked-list implementation we have to split it 10 times


std::string get_data(std::string file) {
    std::ifstream infile {file};
    if (!infile.is_open()) {
        std::cout << "ERROR: Unable to open file" << std::endl;
        std::exit(1010);
    }
    std::string content;
    // For this challenge we assume the input is just a single line from a file
    std::getline(infile, content);
    infile.close();
    return content;
}



void blink_p1 (std::list<std::string> &ll) {
    for (auto it{ll.begin()}; it != ll.end(); it ++) {
        if ( (*it) == "0" ) {
            *it = "1";
        } else if ( !((*it).size() % 2)) {
            std::string left = (*it).substr(0, (*it).size() / 2);
            std::string right = (*it).substr(((*it).size() / 2));
            ll.insert(it, std::to_string(std::stoll(left)));
            (*it) = std::to_string(std::stoll(right));
        } else {
            (*it) = std::to_string(std::stoll(*it) * 2024);
        }
    }
}



std::unordered_map<std::string, long long> blink_p2 (std::unordered_map<std::string, long long> mset) {
    std::unordered_map<std::string, long long> new_mset;
    for (auto it{mset.begin()}; it != mset.end(); it ++) {
        std::string key = it->first;
        long long val = it->second;
        if ( key == "0" ) {
            new_mset["1"] += val;
        } else if ( !(key.size() % 2)) {
            std::string left = key.substr(0, key.size() / 2);
            std::string right = key.substr((key.size() / 2));
            new_mset[std::to_string(std::stoll(left))] += val;
            new_mset[std::to_string(std::stoll(right))] += val;
        } else {
            new_mset[std::to_string(std::stoll(key) * 2024)] += val;
        }
    }
    return new_mset;
}



void solve_p1 (std::list<std::string> ll ) {
    for (int i{0}; i < 25; i ++) {
        blink_p1(ll);
    }
    std::cout << "Length p1 = " << ll.size() << "\n" << std::endl;
}



void solve_p2 (std::list<std::string> ll) {
    std::unordered_map<std::string, long long> mset;
    for (std::string x: ll) {
        mset[x]++;
    }
    for (int i{0}; i < 75; i ++) {
        mset = blink_p2(mset);
    }
    long long total{0};
    for (auto& [key, val]: mset) {
        total += val;
    }
    std::cout << "Length p2 = " << total << std::endl;
}


int main() {
    auto val = get_data("./data/data_full.txt");
    
    std::istringstream iss(val);
    std::string word;
    std::list<std::string> ll;
    while(iss >> word) {
        ll.push_back(word);
    }
    solve_p1(ll);
    solve_p2(ll);
}

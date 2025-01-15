#include <set>
#include <map>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

int main() {
    
    std::ifstream infile { "./data/data.txt" };

    if (!infile) {
        std::exit(1);
    }

    std::vector<int> list1, list2;
    int num1, num2;

    while (infile >> num1 >> num2) {
        list1.push_back(num1);
        list2.push_back(num2);
    }
    infile.close();

    std::sort( std::begin(list1), std::end(list1));
    std::sort( std::begin(list2), std::end(list2));

    int total{0};
    for (int i {0}; i < list1.size(); i++) {
        total += std::abs(list1.at(i) - list2.at(i));
    }

    std::cout << "First answer  = " << total  << std::endl;

    std::set<int> set1{list1.begin(), list1.end()};
    std::map<int, int> mmap;
    for (int x: set1) {
        mmap.insert(
            std::pair( x, std::count(list2.begin(), list2.end(), x))
        );
    }

    long total2 {0};
    for (auto item: mmap) {
        total2 += item.first * item.second;
    }
    std::cout << "Second answer = " << total2  << std::endl;

}

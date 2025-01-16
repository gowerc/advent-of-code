#include <iostream>
#include <string>
#include <fstream>
#include "support.hpp"


void solve_part_1(std::string input) {
    std::vector<int> v_input = parse_line(input);
    auto solution = calculate_check_sum(sort_vector_p1(v_input));
    std::cout << "Part-One = " << solution << std::endl;
}


int main () {

    std::string input;
    std::ifstream infile {"./data/data_full.txt"};
    if (!infile.is_open()) {
        std::cout <<  "Unable to open" << std::endl;
        std::exit(1234);
    }
    infile >> input;
    solve_part_1(input);





//    auto actual = sort_files_p2(files);



}

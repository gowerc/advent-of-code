#include <iostream>
#include <string>
#include <fstream>
#include <list>
#include "support.hpp"


#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/fmt/ostr.h"
#include "spdlog/fmt/fmt.h"





void solve_part_1(std::string input) {
    std::vector<int> v_input = parse_line_p1(input);
    auto solution = calculate_check_sum(sort_vector_p1(v_input));
    std::cout << "Part-One = " << solution << std::endl;
}


void solve_part_2(std::string input) {
    std::list<File> v_input = parse_line_p2(input);
    auto files_list = sort_files_p2(v_input);
    long long solution = calculate_check_sum(convert_to_int_vec(files_list));
    std::cout << "Part-Two = " << solution << std::endl;
}

int main () {

    // 3rd arg = true -> Overwrite,  False -> Append
    auto file_logger = spdlog::basic_logger_mt("file_logger", "logs/app.log", true);
    // Force buffer flushing straight away so log is preserved even if
    // the program crashes
    file_logger->flush_on(spdlog::level::trace);
    spdlog::set_default_logger(file_logger);
    spdlog::set_pattern("%v");


    std::string input;
    std::ifstream infile {"./data/data_full.txt"};
    if (!infile.is_open()) {
        std::cout <<  "Unable to open" << std::endl;
        std::exit(1234);
    }
    infile >> input;
    solve_part_1(input);
    solve_part_2(input);
}

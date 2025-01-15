
#include <iostream>
#include <regex>
#include <string>
#include <iterator>
#include <fstream>
#include <array>



std::vector<std::string> extract_muls(std::string line) {
    std::vector<std::string> result;
    std::regex word_regex("(mul\\(\\d+,\\d+\\))");
    auto words_begin = std::sregex_iterator(line.begin(), line.end(), word_regex);
    auto words_end = std::sregex_iterator();
    for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
        std::smatch match = *i;
        result.push_back(match.str());
    }
    return result;
}


std::vector<std::string> extract_muls_coded(std::string line) {
    std::vector<std::string> result;
    bool include_word {true};
    std::regex word_regex("(mul\\(\\d+,\\d+\\)|do\\(\\)|don't\\(\\))");
    auto words_begin = std::sregex_iterator(line.begin(), line.end(), word_regex);
    auto words_end = std::sregex_iterator();
    for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
        std::smatch match = *i;
        std::string word = match.str();
        if (word.substr(0, 3) == "do(") {
            include_word = true;
        } else if (word.substr(0, 3) == "don") {
            include_word = false;
        } else if (include_word) {
            result.push_back(word);
        }
    }
    return result;
}


std::array<int, 2> extract_digits(std::string line) {
    std::array<int, 2> result;
    std::regex word_regex("(\\d+)");
    auto words_begin = std::sregex_iterator(line.begin(), line.end(), word_regex);
    auto words_end = std::sregex_iterator();
    int N {0};
    for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
        std::smatch match = *i;
        result[N] = stoi(match.str());
        N++;
    }
    if ( N != 2) {
        std::cout << "ERROR: Didn't return 2 numbers";
        std::exit(101);
    }
    return result;
}


void solve_problem(
    std::string line,
    std::vector<std::string> (*fun)(std::string)
) {
    std::vector<std::string> matches = fun(line);

    int final_result{0};
    for ( auto el: matches) {
        std::array<int, 2> digits = extract_digits(el);
        final_result += digits[0] * digits[1];
    }
    std::cout << "Final Result = " << final_result << std::endl;
}



std::string get_data(std::string file) {
    std::ifstream in_file {file};
    std::string line;
    char c;
    while (in_file.get(c)) {
        line += c;
    }
    return line;
}


int main() {

    std::string line {get_data("./data/data.txt")};
    solve_problem(line, extract_muls);
    solve_problem(line, extract_muls_coded);

}


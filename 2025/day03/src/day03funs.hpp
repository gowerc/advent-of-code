
#include <string>
#include <iostream>

int process01(std::string line) {
    std::string word{"00"};
    for (int i{0}; i < line.size(); i++) {
        char letter = line.at(i);
        if (i < line.size() - 1 & letter > word.at(0)) {
            word.at(0) = letter;
            word.at(1) = '0';
        } else if (letter > word.at(1)) {
            word.at(1) = letter;
        }
    }
    return(std::stoi(word));
}

#include <iostream>
#include <map>
#include <functional>
#include <fstream>
#include <string>

std::map<char, std::function<int(int, int)>> operations{
    {'L', std::minus{}},
    {'R', std::plus{}}
};


void do_part_1() {
    std::ifstream fi {"input.txt"};
    if (!fi) { 
        std::cerr << "Could not open file." << std::endl;
        std::exit(1);
    }
    int score {0};
    int current{50};
    char direction;
    int amount;
    while (fi >> direction >> amount) {
        current = operations[direction](current, amount);
        current = current % 100;
        if (current == 0) score += 1;
    }
    std::cout << "Score 1 = " << score << std::endl;
    std::cout << "hello world" << std::endl;
}

void do_part_2() {
    std::ifstream fi {"input.txt"};
    if (!fi) { 
        std::cerr << "Could not open file." << std::endl;
        std::exit(1);
    }
    int score {0};
    int current{50};
    char direction;
    int amount;
    while (fi >> direction >> amount) {
        for (int i{0}; i < amount; i ++ ){
            switch(direction) {
                case 'L': current--; break;
                case 'R': current++; break;
            }
            if (current == 100) current = 0;
            if (current == -1) current = 99;
            if (current == 0) score++;
        }
    }
    std::cout << "Score 2 = " << score << std::endl;
    std::cout << "hello world" << std::endl;
}

int main() {
    do_part_1();
    do_part_2();
}

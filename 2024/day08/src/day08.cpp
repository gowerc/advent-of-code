#include <unordered_map>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>



struct Point {
    int x;
    int y;
    Point(int x, int y): x{x}, y{y} {};
    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }
    int abs_distance(Point other) {
        return std::abs(x - other.x) + std::abs(y - other.y);
    }
    friend std::ostream& operator<<(std::ostream& os, const Point& point) {
        os << "Point(" << point.x << ", " << point.y << ")";
        return os;
    }
    Point operator+(Point d) {
        return Point{x + d.x, y + d.y};
    }
    Point operator-(Point d) {
        return Point{x - d.x, y - d.y};
    }
};


std::unordered_map<char, std::vector<Point>> parse_towers(std::vector<std::string> input) {
    std::unordered_map<char, std::vector<Point>> result;
    int n_row = input.size();
    int n_col = input[0].size();
    for (int row{0}; row < n_row ; row ++ ) {
        for (int col{0}; col < n_col ; col ++ ) {
            char symbol {input.at(row).at(col)};
            if (symbol == '.') continue;
            result[symbol].emplace_back(row, col);
        }
    }
    return result;
}

std::vector<std::string> get_input (std::string filename) {
    std::ifstream in_file{filename};
    if (!in_file.is_open()) {
        std::cout << "Unable to open file" << std::endl;
        std::exit(1234);
    }
    std::string line;
    std::vector<std::string> input;
    while(getline(in_file, line)) {
        input.push_back(line);
    }
    return input;
}


namespace std {
    template<>
    struct hash<Point> {
        size_t operator()(const Point& key) const {
            return hash<std::string>()(std::to_string(key.x) + "," + std::to_string(key.y));
        }
    };
}


int solve_p1 (std::unordered_map<char, std::vector<Point>> tower_map, std::vector<std::string> input) {

    std::unordered_map<Point, bool> hold;

    int n_row = input.size();
    int n_col = input[0].size();
    for (auto towers: tower_map) {
        
        for (int node1_index{0}; node1_index < towers.second.size(); node1_index ++ ) {
            for (int node2_index{node1_index + 1}; node2_index < towers.second.size(); node2_index ++ ) {
            
                Point node1{towers.second.at(node1_index)};
                Point node2{towers.second.at(node2_index)};                
                
                std::vector<Point> proposals {{node1 + (node1 - node2)}, {node2 + (node2 - node1)}};
                for (auto proposal: proposals) {
                    if ( proposal.x < n_row && proposal.y < n_col && proposal.x >= 0 && proposal.y >= 0) {
                        bool skip{false};
                        for (auto el: towers.second) if (proposal == el) skip = true;
                        if (skip) continue;
                        hold[proposal] = true;
                    }
                }
            }
        }
    }
    return hold.size();
}

    

bool is_in_grid(Point p, int n_row, int n_col ) {
    return (p.x < n_row) && (p.y < n_col) && (p.x >= 0) && (p.y >= 0);
}




int solve_p2 (std::unordered_map<char, std::vector<Point>> tower_map, std::vector<std::string> input) {

    std::unordered_map<Point, bool> hold;

    int n_row = input.size();
    int n_col = input[0].size();
    for (auto towers: tower_map) {
        
        for (int node1_index{0}; node1_index < towers.second.size(); node1_index ++ ) {
            for (int node2_index{node1_index + 1}; node2_index < towers.second.size(); node2_index ++ ) {

                Point node1{towers.second.at(node1_index)};
                Point node2{towers.second.at(node2_index)};

                hold[node1] = true;
                hold[node2] = true;

                Point distance {node1 - node2};
                std::vector<Point> proposals;
                
                Point prop {node1 + distance};
                while (is_in_grid(prop, n_row, n_col)) {
                    proposals.push_back(prop);
                    prop = prop + distance;
                }
                prop = node2 - distance;
                while (is_in_grid(prop, n_row, n_col)) {
                    proposals.push_back(prop);
                    prop = prop - distance;
                }

                for (auto proposal: proposals) {
                    bool skip{false};
                    for (auto el: towers.second) if (proposal == el) skip = true;
                    if (skip) continue;
                    hold[proposal] = true;

                }
            }
        }
    }
    return hold.size();
}


int main () {
    std::vector<std::string> input {get_input("data/data_full.txt")};
    auto tower_map = parse_towers(input);
    std::cout << "Part 1 = " << solve_p1(tower_map, input) << std::endl;
    std::cout << "Part 2 = " << solve_p2(tower_map, input) << std::endl;
}

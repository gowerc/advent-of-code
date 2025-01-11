
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

template <typename T>
struct Matrix {
    std::vector<std::vector<T>> data {};
    Matrix(int nrow, int ncol, T init) 
        : data(nrow, std::vector<T>(ncol, init)) {}

    T &operator()(int x, int y) {
        return data.at(x).at(y);
    }
    T &operator()(std::pair<int, int> pos) {
        return data.at(pos.first).at(pos.second);
    }
};


struct Grid {

    int n_row;
    int n_col;
    Matrix<int> count;
    Matrix<char> symbol;
    std::pair<int, int> pos;
    std::pair<int, int> dir{-1, 0};
    bool is_inf_loop{false};

    Grid(int nrow, int ncol):
        n_row{nrow},
        n_col{ncol},
        count{Matrix<int>(nrow, ncol, 0)},
        symbol{Matrix<char>(nrow, ncol, '.')} {}

    void insert(size_t x, size_t y, char c) {
        if (c == '^') {
            pos = {x, y}; // "^" = Starting position
            c = '.';
        }
        count(x, y) = 0;
        symbol(x, y) = c;
    }

    void rotate() {
        int new_r = dir.second;
        int new_c = - dir.first;
        dir.first = new_r;
        dir.second = new_c;
    }

    std::pair<int, int> get_proposed_pos () {
        return std::pair<int, int> {
            pos.first + dir.first,
            pos.second + dir.second
        };
    }

    bool is_out_of_bounds (std::pair<int, int> pos) {
        if (
            pos.first >= n_row ||
            pos.second >= n_col ||
            pos.first < 0 ||
            pos.second < 0
        ) {
            return true;
        }
        return false;
    }

    bool step() {
        count(pos)++;
        // Assuming that if they've been over the same square > 4 times then they are in a loop
        if (count(pos) > 4) {
            is_inf_loop = true;
            return false;
        }
        std::pair<int, int> p_pos = get_proposed_pos();
        if (is_out_of_bounds(p_pos)) return false;
        int i{0};
        while(symbol(p_pos) != '.') {
            rotate();
            p_pos = get_proposed_pos();
            if (i > 3) {
                std::cout << "Stuck in a trap" << std::endl;
                std::exit(201);
            }
            i++;
        }
        if (is_out_of_bounds(p_pos)) return false;
        pos = p_pos;
        return true;
    }

    int unique_step_count() {
        int total {0};
        auto count_fun = [&total] (std::vector<int> x) {
            total += std::count_if( x.begin(), x.end(), [](int x) { return x >= 1; });
        };
        std::for_each( count.data.begin(), count.data.end(), count_fun);
        return total;
    }

    void add_blockade(int x, int y) {
        if (x == pos.first && y == pos.second) {
            return;
        }
        symbol(x, y) = '#';
    }

    void run_till_complete() {
        while(step()) {}
    }
};


Grid parse_data(std::string filename) {
    std::ifstream in_file {filename};
    if (!in_file.is_open()) {
        std::cout << "Unable to open file" << std::endl;
        std::exit(101);
    }

    std::vector<std::string> file_content;

    while (!in_file.eof()) {
        std::string cline;
        getline(in_file, cline);
        file_content.push_back(cline);
    }

    size_t n_row{file_content.size()};
    size_t n_col{file_content.at(0).size()};

    Grid grid(n_row, n_col);
    for (size_t i{0}; i < n_row; i++) {
        for (size_t j{0}; j < n_col; j++) {
            grid.insert(i, j, file_content.at(i).at(j));
        }
    }
    return grid;
}


void solve_part_2(Grid grid) {

    // Adding a block to any point that isn't on the original route won't change
    // the outcome so no point evaluting them
    // So we simply record every step on the original route and then see if adding a
    // block there changes the outcome
    auto is_inf_with_block = [grid](auto block) {
        Grid grid2{grid};
        grid2.add_blockade(block.first, block.second);
        grid2.run_till_complete();
        return grid2.is_inf_loop;
    };

    grid.run_till_complete();
    std::vector<std::pair<int, int>> o_route;

    for (int i{0}; i < grid.n_row; i++) {
        for (int j{0}; j < grid.n_col; j++) {
            if (grid.count(i, j) > 0) o_route.push_back({i, j});
        }
    }

    int total = std::count_if( o_route.begin(), o_route.end(), is_inf_with_block);
    std::cout << "Part-2 = " << total << std::endl;
}


void solve_part_1(Grid grid) {
    grid.run_till_complete();
    std::cout << "Part-1 = " << grid.unique_step_count() << std::endl;
}

int main () {
    Grid grid = parse_data("./data/data_full.txt");
    solve_part_1(grid);
    solve_part_2(grid);
}

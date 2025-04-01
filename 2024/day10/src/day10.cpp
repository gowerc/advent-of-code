#include <iostream>
#include <fstream>
#include <string>
#include <vector>

template<typename T>
struct Matrix {
    int nrow;
    int ncol;
    std::vector<std::vector<T>> values;

    void init (int nrow, int ncol, T default_value) {
        this->nrow = nrow;
        this->ncol = ncol;
        std::vector<T> init(ncol, default_value);
        for (int i{0}; i < nrow; i ++) {
            values.push_back(init);
        }
    }
    Matrix() =default;
    Matrix(int nrow, int ncol, T default_value){
        init(nrow, ncol, default_value);
    };
    T& operator()(int row, int col) {
        return values.at(row).at(col);
    };
};


struct Grid {
    int nrow;
    int ncol;
    Matrix<int> grid;
    Matrix<int> flag;
    Grid(std::vector<std::string> input_data) {
        nrow = input_data.size();
        ncol = input_data.at(0).size();
        grid = Matrix<int>(nrow, ncol, -1);
        flag = Matrix<int>(nrow, ncol, 0);
        for (int row{0}; row < nrow; row ++) {
            for (int col{0}; col < ncol; col ++) {
                grid(row, col) = input_data.at(row).at(col) - '0';
            }
        }
    }
    void print() {
        for (int row{0}; row < nrow; row ++ ) {
            for (int col{0}; col < ncol; col ++ ) {
                std::cout << grid(row, col);
            }
            std::cout << std::endl;
        }
    }
    int sum() {
        int total{0};
        for (int row{0}; row < nrow; row ++ ) {
            for (int col{0}; col < ncol; col ++ ) {
                total += flag(row, col);
            }
        }
        return total;
    }
};


std::vector<std::string> read_data() {
    std::ifstream file = std::ifstream("./data/data_full.txt");
    
    if (!file.is_open()) {
        std::exit(101);
    }

    std::vector<std::string> vec;

    std::string line;
    while (std::getline(file, line)) {
        vec.push_back(line);
    }
    file.close();
    return vec;
}




void walk_inner_pt1(int row, int col, Grid &grid, int old_val) {
    if (row < 0) return;
    if (col < 0) return;
    if (row >= grid.nrow) return;
    if (col >= grid.ncol) return;
    int cval = grid.grid(row, col);
    if ((old_val + 1) != cval) return;
    if (cval == 9) {
        grid.flag(row, col) = 1;
        return;
    }
    walk_inner_pt1(row + 1, col, grid, cval);
    walk_inner_pt1(row - 1, col, grid, cval);
    walk_inner_pt1(row, col + 1, grid, cval);
    walk_inner_pt1(row, col - 1, grid, cval);
}



int walk_pt1(int row, int col, Grid grid) {
    walk_inner_pt1(row , col, grid, -1);
    return grid.sum();
}



void walk_inner_pt2(int row, int col, Grid &grid, int old_val) {
    if (row < 0) return;
    if (col < 0) return;
    if (row >= grid.nrow) return;
    if (col >= grid.ncol) return;
    int cval = grid.grid(row, col);
    if ((old_val + 1) != cval) return;
    if (cval == 9) {
        grid.flag(row, col) += 1;
        return;
    }
    walk_inner_pt2(row + 1, col, grid, cval);
    walk_inner_pt2(row - 1, col, grid, cval);
    walk_inner_pt2(row, col + 1, grid, cval);
    walk_inner_pt2(row, col - 1, grid, cval);
}



int walk_pt2(int row, int col, Grid grid) {
    walk_inner_pt2(row , col, grid, -1);
    return grid.sum();
}



int main() {
    auto input_data = read_data();
    
    Grid grid(input_data);
    grid.print();

    int total_pt1{0};
    for (int row{0}; row < grid.nrow; row ++ ) {
        for (int col{0}; col < grid.ncol; col ++ ) {
            if (grid.grid(row, col) == 0) {
                int res = walk_pt1(row, col, grid);
                total_pt1 += res;
            }
        }
    }
    std::cout << "Total pt1 = " << total_pt1 << std::endl;
    
    int total_pt2{0};
    for (int row{0}; row < grid.nrow; row ++ ) {
        for (int col{0}; col < grid.ncol; col ++ ) {
            if (grid.grid(row, col) == 0) {
                int res = walk_pt2(row, col, grid);
                total_pt2 += res;
            }
        }
    }
    std::cout << "Total pt2 = " << total_pt2 << std::endl;
}


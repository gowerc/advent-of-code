#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>


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
    void print(int space = 0){
        for (auto row: values) {
            for (auto col: row) {
                std::cout << std::setw(space) << col;
            }
            std::cout << std::endl;
        }
    }
    void populate(std::vector<std::vector<char>> vec) {
        for (int row{0}; row < nrow; row++) {
            for (int col{0}; col < ncol; col++) {
                (*this)(row, col) = vec.at(row).at(col);
            }
        }
    }
};


std::vector<std::vector<char>> get_data(std::string inp) {
    std::ifstream infile {inp};
    char ch;
    std::vector<char> cvec;
    std::vector<std::vector<char>> vec;
    while (infile.get(ch)) {
        if (ch == '\n') {
            vec.push_back(cvec);
            cvec.clear();
        } else {
            cvec.push_back(ch);
        }
    }
    return vec;
}


int main() {
    std::cout << "Hello, world !" << std::endl;
    auto vec = get_data("./data/data_test.txt");

    Matrix<char> data(vec.size(), vec[0].size(), ' ');
    data.populate(vec);
    Matrix<int> index(data.nrow, data.ncol, 0);

    int current_index{2};
    index(0,0) = 1;
    for (int row{0}; row < data.nrow; row++) {
        for (int col{0}; col < data.ncol; col++) {
            char cval = data(row, col);

            char right_val = ' ';
            int right_ind = 0;
            if (col < data.ncol - 1) {
                right_val = data(row, col + 1);
                right_ind = index(row, col + 1);
            }
    
            char down_val = ' ';
            int down_ind = 0;
            if (row < data.nrow - 1) {
                down_val = data(row+ 1, col);
                down_ind = index(row + 1, col);
            }

            if (cval == right_val) {
                if (right_ind > 0) {
                    index(row, col) = right_ind;
                }
            }

            if (index(row, col) == 0) {
                index(row, col) = current_index++;
            }

            if (cval == right_val) {
                index(row, col+1) = index(row, col);
            }
            if (cval == down_val) {
                index(row +1, col) = index(row, col);
            }
        }
    }
    data.print(4);
    std::cout << std::endl;
    index.print(4);
}

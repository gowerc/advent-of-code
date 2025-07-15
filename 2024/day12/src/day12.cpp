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


int follow(char tval, int tindex, int row, int col, Matrix<char> &data, Matrix<int> &index) {
    if (row >= data.nrow || row < 0) return 0;
    if (col >= data.ncol || col < 0) return 0;
    if (data(row, col) != tval) return 0;
    if (index(row, col) != 0) return 0;
    index(row, col) = tindex;
    return 1 + 
        follow(tval, tindex, row + 1, col, data, index) +
        follow(tval, tindex, row - 1, col, data, index) +
        follow(tval, tindex, row, col + 1, data, index) +
        follow(tval, tindex, row, col - 1, data, index);
}


int get_perim(int row, int col, Matrix<int> &index) {

    int tval = index(row, col);
    int score = 0;

    if (row == 0 || row == (index.nrow - 1)) score++;
    if (col == 0 || col == (index.ncol - 1)) score++;

    if (row > 0) if (tval != index(row - 1, col)) score++;
    if (col > 0) if (tval != index(row, col - 1)) score++;
    if (row < (index.nrow - 1)) if (tval != index(row + 1, col)) score++;
    if (col < (index.ncol - 1)) if (tval != index(row, col + 1)) score++;
    return score;
}


int get_corners(int row, int col, Matrix<int> &index, bool debug = false) {

    int tval = index(row, col);
    int corners = 0;

    int ncol{index.ncol - 1};
    int nrow{index.nrow - 1};
    int up{0}, down{0}, left{0}, right{0};
    int ur{0}, ul{0}, dr{0}, dl{0};
    
    if (row > 0) if (tval == index(row - 1, col)) up = 1;
    if (col > 0) if (tval == index(row, col - 1)) left = 1;
    if (row < nrow) if (tval == index(row + 1, col)) down = 1;
    if (col < ncol) if (tval == index(row, col + 1)) right = 1;

    if (row > 0 &&  col > 0 && col < ncol && row < nrow) {
        if (tval == index(row - 1, col + 1)) ur = 1;
        if (tval == index(row - 1, col - 1)) ul = 1;
        if (tval == index(row + 1, col + 1)) dr = 1;
        if (tval == index(row + 1, col - 1)) dl = 1;
    }
    if (row == 0 && col == 0)       if (tval == index(row + 1, col + 1)) dr = 1;
    if (row == 0 && col == ncol)    if (tval == index(row + 1, col - 1)) dl = 1;
    if (row == nrow && col == 0)    if (tval == index(row - 1, col + 1)) ur = 1;
    if (row == nrow && col == ncol) if (tval == index(row - 1, col - 1)) ul = 1;

    if (col == 0 && row > 0 && row < nrow) {
        if (tval == index(row - 1, col + 1)) ur = 1;
        if (tval == index(row + 1, col + 1)) dr = 1;
    }

    if (col == ncol && row > 0 && row < nrow) {
        if (tval == index(row - 1, col - 1)) ul = 1;
        if (tval == index(row + 1, col - 1)) dl = 1;
    }
    if (row == 0 && col > 0 && col < ncol) {
        if (tval == index(row + 1, col - 1)) dl = 1;
        if (tval == index(row + 1, col + 1)) dr = 1;
    }

    if (row == nrow && col > 0 && col < ncol) {
        if (tval == index(row - 1, col - 1)) ul = 1;
        if (tval == index(row - 1, col + 1)) ur = 1;
    }


    if (debug) {
        std::cout << "up    = " << up << "\n"
                  << "down  = " << down << "\n"
                  << "left  = " << left << "\n"
                  << "right = " << right << "\n"
                  << "ul    = " << ul << "\n"
                  << "ur  = " << ur << "\n"
                  << "dl  = " << dl << "\n"
                  << "dr = " << dr << "\n"
                  << std::endl;
    }


    int total = up + down + left + right;
    if (total == 0) return 4;
    if (total == 1) return 2;
    
    if (total == 2) {
        if (up + down == 2) return 0;
        if (left + right == 2) return 0;
        if (up + right == 2) {
            if(ur == 0) return 2;
            return 1;
        }
        if (up + left == 2) {
            if(ul == 0) return 2;
            return 1;
        }
        if (down + right == 2) {
            if(dr == 0) return 2;
            return 1;
        }
        if (down + left == 2) {
            if(dl == 0) return 2;
            return 1;
        }
    }
    if (total == 3) {
        int extra {0};
        if (up + right == 2) {
            if (ur == 0) extra++;
        }
        if (up + left == 2) {
            if (ul == 0) extra++;
        }
        if (down + right == 2) {
            if (dr == 0) extra++;
        }
        if (down + left == 2) {
            if (dl == 0) extra++;
        }
        return extra;
    }
    if (total == 4) {
        int extra {0};
        if (ur == 0) extra++;
        if (ul == 0) extra++;
        if (dl == 0) extra++;
        if (dr == 0) extra++;
        return extra;
    }

    return 0;
}



int main() {
    std::cout << "Hello, world !" << std::endl;
    auto vec = get_data("./data/data_full.txt");

    Matrix<char> data(vec.size(), vec[0].size(), ' ');
    data.populate(vec);
    Matrix<int> index(data.nrow, data.ncol, 0);

    int n_max{data.nrow * data.ncol};
    std::vector<int> areaVec(n_max, 0);
    std::vector<int> perimVec(n_max, 0);
    std::vector<int> cornerVec(n_max, 0);

    Matrix<int> perim(data.nrow, data.ncol, 0);
    Matrix<int> corners(data.nrow, data.ncol, 0);
    std::vector<char> valVec(n_max, ' ');

    int current_index = 0;
    for (int row{0}; row < data.nrow; row++) {
        for (int col{0}; col < data.ncol; col++) {
            if ( index(row, col) == 0) current_index++;
            areaVec.at(index(row, col) - 1) += follow(data(row, col), current_index, row, col, data, index);
            perim(row, col) = get_perim(row, col, index);
            perimVec.at(index(row, col) - 1) += get_perim(row, col, index);
            valVec.at(index(row, col) - 1) = data(row, col);
            corners(row, col) = get_corners(row, col, index);
            cornerVec.at(index(row, col) - 1) += get_corners(row, col, index);
        }
    }

    int totalScore_1{0};
    int totalScore_2{0};
    for (int i{0}; i < n_max; i++) {
        if (areaVec.at(i) == 0) break;
        std::cout << valVec.at(i) <<
            ":  " << 
            areaVec.at(i) <<
            "   " <<
            cornerVec.at(i) <<
            std::endl;
        totalScore_1 += areaVec.at(i) * perimVec.at(i);
        totalScore_2 += areaVec.at(i) * cornerVec.at(i);
    }

    // data.print(4);
    // std::cout << std::endl;
    // index.print(4);
    // std::cout << std::endl;
    // corners.print(4);
    // std::cout << std::endl;
    std::cout << totalScore_1 << std::endl;
    std::cout << totalScore_2 << std::endl;

    std::cout <<  get_corners(2, 3, index, true);
}

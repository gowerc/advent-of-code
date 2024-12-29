
#include <iostream>
#include <regex>
#include <string>
#include <iterator>
#include <fstream>
#include <array>
#include <CLI/CLI.hpp>


struct Grid {

    std::vector<std::vector<char>> grid;
    int n_col {0};
    int n_row {0};
    int c_col {0};
    int c_row {0};

    void append_char(char c) {
        // If new line character that means terminate current row
        if (c == '\n') {
            this->c_row +=1;
            this->c_col = 0;
            return;
        }
        if (c_col == 0) {
            this->grid.push_back(std::vector<char>{});
        }
        this->grid.at(c_row).push_back(c);
        this->c_col+=1;
        if (c_col > n_col) n_col = c_col;
        if (c_row + 1 > n_row) n_row = c_row + 1;
    }

    char operator()(int row, int col) {
        if ( row < 0) return ' ';
        if ( col < 0) return ' ';
        if ( row > this->n_row - 1) return ' ';
        if ( col > this->n_col - 1) return ' ';
        return this->grid.at(row).at(col);
    }

    enum Dir {L, R, UL, UR, U, D, DL, DR};

    int n_xmas(int row, int col) {
        int result{0};
        if ((*this)(row, col) != 'X') return 0;
        if ( this->has_xmas_dir(row, col, L))  result++;
        if ( this->has_xmas_dir(row, col, R))  result++;
        if ( this->has_xmas_dir(row, col, U))  result++;
        if ( this->has_xmas_dir(row, col, D))  result++;
        if ( this->has_xmas_dir(row, col, UR)) result++;
        if ( this->has_xmas_dir(row, col, UL)) result++;
        if ( this->has_xmas_dir(row, col, DR)) result++;
        if ( this->has_xmas_dir(row, col, DL)) result++;
        return result;
    }

    bool has_xmas_dir(int row, int col, Dir dir) {
        int inc_col{0};
        int inc_row{0};
        switch (dir) {
            case L:  inc_row =  0; inc_col = -1 ; break;
            case R:  inc_row =  0; inc_col =  1 ; break;
            case U:  inc_row = -1; inc_col =  0 ; break;
            case D:  inc_row =  1; inc_col =  0 ; break;
            case UL: inc_row = -1; inc_col = -1 ; break;
            case UR: inc_row = -1; inc_col =  1 ; break;
            case DL: inc_row =  1; inc_col = -1 ; break;
            case DR: inc_row =  1; inc_col =  1 ; break;
        }
        char word[4] = {'X', 'M', 'A', 'S'};
        for (int i{0}; i<4; i++) {
            char c  = (*this)(row, col) ;
            if (c != word[i]) return false;
            col += inc_col;
            row += inc_row;
        }
        return true;
    }


    int n_mas(int row, int col) {
        int result{0};
        if ((*this)(row, col) != 'X') return 0;
        if ( this->has_xmas_dir(row, col, L)) result++;
        if ( this->has_xmas_dir(row, col, R)) result++;
        if ( this->has_xmas_dir(row, col, U)) result++;
        if ( this->has_xmas_dir(row, col, D)) result++;
        if ( this->has_xmas_dir(row, col, UR)) result++;
        if ( this->has_xmas_dir(row, col, UL)) result++;
        if ( this->has_xmas_dir(row, col, DR)) result++;
        if ( this->has_xmas_dir(row, col, DL)) result++;
        return result;
    }

    bool has_mas_dir(int row, int col) {
        if ( row < 1) return false;
        if ( col < 1) return false;
        if ( row > this->n_row-2) return false;
        if ( col > this->n_col-2) return false;
        if ((*this)(row, col) != 'A') return false;
        char UL = (*this)(row - 1, col - 1);
        char BR = (*this)(row + 1, col + 1);
        char BL = (*this)(row - 1, col + 1);
        char UR = (*this)(row + 1, col - 1);
        if ((UL == 'M' && BR == 'S') || (UL == 'S' && BR == 'M')) {
            if ((UR == 'M' && BL == 'S') || (UR == 'S' && BL == 'M')) {
                return true;
            }
        }
        return false;
    }
};


Grid get_data(std::string file) {
    std::ifstream in_file {file};
    if (!in_file) {
        std::cout << "ERROR: Unable to open " + file << std::endl;
        std::exit(101);
    }
    Grid grid{};
    char c;
    while (in_file.get(c)) {
        grid.append_char(c);
    }
    return grid;
}



int main(int argc, char** argv) {

    CLI::App app{"App description"};
    argv = app.ensure_utf8(argv);
    std::string filename = "default";
    app.add_option("-f,--file", filename, "A help string");
    CLI11_PARSE(app, argc, argv);

    Grid grid{get_data(filename)};
    int total {0};
    int total_2 {0};
    for (int row {0}; row < grid.n_row; row ++ ) {
        for (int col {0}; col < grid.n_col; col ++ ) {
            total += grid.n_xmas(row, col);
            if ( grid.has_mas_dir(row, col)) total_2 ++ ;
        }
    }
    std::cout << "Total = " << total << std::endl;
    std::cout << "Total2 = " << total_2 << std::endl;

    return 0;

}

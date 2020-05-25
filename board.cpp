#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <assert.h>

#include "io.h"
#include "board.h"

// Board constructor
Board::Board(int nn,
             std::vector<std::vector<int>> *row,
             std::vector<std::vector<int>> *column
            ) :
    board (std::vector<std::vector<board_state>>(nn, std::vector<board_state>(nn, UNKNOWN))),
    row_vector(row),
    column_vector(column)
{
    // initialize row/column occupied fields
    row_occupied    = std::vector<int>(row_vector->size());
    column_occupied = std::vector<int>(column_vector->size());

    for (size_t ii = 0; ii < row_vector->size(); ii++) {
        int row_num    = (*row_vector)[ii].size() - 1;
        int column_num = (*column_vector)[ii].size() - 1;

        for (size_t jj = 0; jj < (*row_vector)[ii].size(); jj++)
            row_num += (*row_vector)[ii][jj];
        for (size_t jj = 0; jj < (*column_vector)[ii].size(); jj++)
            column_num += (*column_vector)[ii][jj];

        row_occupied[ii] = row_num;
        column_occupied[ii] = column_num;
    }
}



// Board destructor
Board::~Board()
{
    board.clear();
    row_vector->clear();
    column_vector->clear();
    row_occupied.clear();
    column_occupied.clear();
}



// String representation of board member
std::string
Board::render_board()
{
    std::string solution = board_string(&board);
    std::cout << solution << std::endl;
    return solution;
}

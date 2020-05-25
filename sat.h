#ifndef SOLVE_H
#define SOLVE_H

#include <vector>
#include <string>

enum board_state { UNKNOWN, FALSE, TRUE };

class Board {
  private:
    // board[x][y] is state of board at coordinates (x,y)
    std::vector<std::vector<board_state>> board;

    // (*row_vector)[ii] is vector of occupied cells in row ii
    std::vector<std::vector<int>> *row_vector;
    // (*column_vector)[jj] is vector of occupied cells in column jj
    std::vector<std::vector<int>> *column_vector;

    // row_occupied[ii] is minimum length occupied by (*row_vector)[ii]'s elements.
    std::vector<int> row_occupied;
    // column_occupied[jj] is minimum length occupied by (*column_vector)[jj]'s elements.
    std::vector<int> column_occupied;

  public:
    // initialize board to all UNKNOWN of given size,
    // point allocated row/column restriction vectors from main to same fields
    Board(int nn, std::vector<std::vector<int>> *row, std::vector<std::vector<int>> *column);
    ~Board();

    // solution string ("\n" separate rows)
    std::string render_board();

    void initial_restrains(void);
};

#endif

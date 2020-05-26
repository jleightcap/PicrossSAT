#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <string>

enum boardState { UNKNOWN, FALSE, TRUE };

class Board {
    private:
        // board[x][y] is boardState at index {x,y} (Cartesian)
        std::vector<std::vector<boardState>> board;
        // (*row_vector)[ii] is vector of occupied cells in row ii
        std::vector<std::vector<int>> *row_vector;
        // (*column_vector)[jj] is vector of occupied cells in column jj
        std::vector<std::vector<int>> *column_vector;

    public:
        // initialize board to all UNKNOWN of given size
        Board(int nn,
              std::vector<std::vector<int>> *row,
              std::vector<std::vector<int>> *column
             ):
            board(std::vector<std::vector<boardState>>
                    (nn, std::vector<boardState>(nn, UNKNOWN))),
            row_vector(row),
            column_vector(column)
        {}

        ~Board()
        {
            board.clear();
            row_vector->clear();
            column_vector->clear();
        }

        auto getBoard() { return &board; }
        void setBoard(boardState bs, int ii, int jj) { board[ii][jj] = bs; }

        // solution string ("\n" separate rows)
        std::string render_board();
};

#endif

#ifndef BOARD_H
#define BOARD_H

#include <string>
#include <vector>

enum boardState { UNKNOWN, FALSE, TRUE };

class Board {
    private:
        int nn; // dim(x)
        int mm; // dim(y)

        // board[x][y] is boardState at index {x,y} (Cartesian)
        std::vector<std::vector<boardState>> board;
        // (*rowVecs)[ii] is std::vector of occupied cells in row ii
        std::vector<std::vector<int>> *rowVecs;
        // (*colVecs)[jj] is std::vector of occupied cells in column jj
        std::vector<std::vector<int>> *colVecs;

    public:
        // initialize board to all UNKNOWN of given size
        Board(std::vector<std::vector<int>> *row,
              std::vector<std::vector<int>> *column):
            nn(row->size()),
            mm(column->size()),
            board(std::vector<std::vector<boardState>>(nn, std::vector<boardState>(mm, UNKNOWN))),
            rowVecs(row),
            colVecs(column)
        {}

        ~Board()
        {
            board.clear();
            rowVecs->clear();
            colVecs->clear();
        }

        auto getDimX()      { return nn; }
        auto getDimY()      { return mm; }
        auto getBoard()     { return &board; }
        auto getRowVec()    { return rowVecs; }
        auto getColumnVec() { return colVecs; }

        void setBoard(boardState bs, int ii, int jj) { board[ii][jj] = bs; }
};

#endif

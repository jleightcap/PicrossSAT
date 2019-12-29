#ifndef BOARD_H
#define BOARD_H

enum board_state { UNKNOWN, FALSE, TRUE };

class Board {
  private:
  std::vector<std::vector<board_state>> board;
  std::vector<std::vector<int>> *row_vector;
  std::vector<std::vector<int>> *column_vector;

  public:
  Board(int nn, std::vector<std::vector<int>> *row, std::vector<std::vector<int>> *column);
  ~Board();

  std::string render_board();
  void naive();
};

#endif

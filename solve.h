#ifndef BOARD_H
#define BOARD_H

enum board_state { UNKNOWN, FALSE, TRUE };

class Board {
  std::vector<std::vector<board_state>> board;

  public:
  Board(int nn);
  void f();
};

#endif

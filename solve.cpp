#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <assert.h>

#include "io.h"
#include "solve.h"

Board::Board(int nn) {
  board = std::vector<std::vector<board_state>>(nn, std::vector<board_state>(nn, UNKNOWN));
}

Board::~Board() {
  board.clear();
}

void Board::f() {
  std::cout << board[0][0]  << std::endl;
}

std::string Board::render_board() {
  std::string solution = board_string(board);
  std::cout << solution << std::endl;
  return solution;
}

int main() {
  std::string restrict_row;
  std::cout << "Row restriction:\n";
  std::getline(std::cin, restrict_row);

  std::string restrict_column;
  std::cout << "Column restriction:\n";
  std::getline(std::cin, restrict_column);
  
  //assert(restrict_row.size() == restrict_column.size());

  std::vector<std::vector<int>> parsed = parse(restrict_row);
  Board b1(restrict_row.size());
  std::string solution = b1.render_board(); 
  std::ofstream file("solution.txt");
  file << solution;
  file.close();
  
  return 0;
}

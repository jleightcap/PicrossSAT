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

void Board::f() {
  std::cout << board[0][0]  << std::endl;
}

int main() {
  std::string restrict_row;
  std::cout << "Row restriction:\n";
  std::getline(std::cin, restrict_row);
  std::string restrict_column;
  std::cout << "Column restriction:\n";
  std::getline(std::cin, restrict_column);
  assert(restrict_row.size() == restrict_column.size());
  std::vector<std::vector<int>> parsed = parse(restrict_row);
  
  std::string solution = print_board(parsed);
  std::ofstream file("solution.txt");
  file << solution;
  file.close();
  
  return 0;
}

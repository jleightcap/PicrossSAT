#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <assert.h>

#include "io.h"
#include "solve.h"

Board::Board(int nn, std::vector<std::vector<int>> *row, std::vector<std::vector<int>> *column) :
  board        (std::vector<std::vector<board_state>>(nn, std::vector<board_state>(nn, UNKNOWN))),
  row_vector   (row), 
  column_vector(column)
{}

Board::~Board() {
  board.clear();
  row_vector->clear();
  column_vector->clear();
}

std::string Board::render_board() {
  std::string solution = board_string(&board);
  std::cout << solution << std::endl;
  return solution;
}

void Board::naive() {
  for (size_t ii = 0; ii < board.size(); ii++) {
    for (size_t jj = 0; jj < board.size(); jj++) {
      std::cout << (*row_vector)[ii][0] << std::endl;
    }
  }
}

void write_file(std::string text) {
  std::ofstream file("solution.txt");
  file << text;
  file.close();
}

int main() {
  std::string restrict_row = "[1 1 1] [1 1] [1 1 1] [1 1] [1 1 1]";
  //std::cout << "Row restriction:\n";
  //std::getline(std::cin, restrict_row);

  std::string restrict_column = "[1 1 1] [1 1] [1 1 1] [1 1] [1 1 1]";
  //std::cout << "Column restriction:\n";
  //std::getline(std::cin, restrict_column);
  
  assert(restrict_row.size() == restrict_column.size());
  std::vector<std::vector<int>> row_vector    = parse(restrict_row);
  std::vector<std::vector<int>> column_vector = parse(restrict_column);
 
  Board b1(row_vector.size(), &row_vector, &column_vector);
  b1.naive();
  std::string solution = b1.render_board(); 
  write_file(solution);
  return 0;
}

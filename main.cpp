#include <iostream>
#include <string>
#include <list>
#include <assert.h>

#include "io.h"
#include "board.h"
#include "sat.h"

int main() {
  std::string restrict_row = "[1 1 1] [1 1] [1 1 1] [1 1] [1 1 1]";
  //std::cout << "Row restriction:\n";
  //std::getline(std::cin, restrict_row);
  std::vector<std::vector<int>> row_vector = parse(restrict_row);

  std::string restrict_column = "[1 1 1] [1 1] [1 1 1] [1 1] [1 1 1]";
  //std::cout << "Column restriction:\n";
  //std::getline(std::cin, restrict_column);
  std::vector<std::vector<int>> column_vector = parse(restrict_column);

  assert(row_vector.size() == column_vector.size());
  Board b1(row_vector.size(), &row_vector, &column_vector);

  return 0;
}

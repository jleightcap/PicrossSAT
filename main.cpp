#include <iostream>

#include "io.h"
#include "board.h"
#include "sat.h"

int main() {
  auto restrict_row = "[3] [1 3] [2] [2] [2]";
  //std::cout << "Row restriction:\n";
  //std::getline(std::cin, restrict_row);
  auto row_vector = parse(restrict_row);

  auto restrict_column = "[1 2] [2] [2] [3] [3]";
  //std::cout << "Column restriction:\n";
  //std::getline(std::cin, restrict_column);
  auto column_vector = parse(restrict_column);

  Board b1(&row_vector, &column_vector);
  SATExpr s;
  s.solve(&b1);

  return 0;
}

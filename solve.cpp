#include <iostream>
#include <string>
#include <list>

#include "io.h"

int main() {
  std::string restrict_row;
  std::cout << "Row restriction:\n";
  std::getline(std::cin, restrict_row);
  // std::cout << "Column restriction:\n";
  // std::getline(std::cin, restrict_row);
  std::vector<std::vector<int>> parsed = parse(restrict_row);
  print_board(parsed);
  return 0;
}

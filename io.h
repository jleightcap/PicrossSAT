#ifndef IO_H
#define IO_H

#include <string>
#include <list>
#include <vector>

std::vector<std::string> tokenize(std::string raw);
std::vector<std::vector<int>> parse(std::string input);
std::string print_board(std::vector<std::vector<int>> board);

#endif

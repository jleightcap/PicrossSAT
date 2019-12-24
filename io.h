#ifndef IO_H
#define IO_H

#include <string>
#include <list>
#include <vector>

#include "solve.h"

std::vector<std::string> tokenize(std::string raw);
std::vector<std::vector<int>> parse(std::string input);
std::string board_string(std::vector<std::vector<board_state>> board); 

#endif

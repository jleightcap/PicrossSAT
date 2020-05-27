#ifndef IO_H
#define IO_H

#include <string>
#include <list>
#include <vector>

#include "board.h"

std::vector<std::string> tokenize(std::string raw);
std::vector<std::vector<int>> parse(std::string input);
std::string boardString(std::vector<std::vector<boardState>> *board);
void write_file(std::string text);

#endif

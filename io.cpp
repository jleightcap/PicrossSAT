#include <iostream>
#include <string>
#include <vector>

#include "io.h"
#include "board.h"

// tokenize an input string
// "1 [2 3] 4" -> {1, [, 2, 3, ], 4}
std::vector<std::string> tokenize(std::string raw) {
  // iterators might clean this a lot.
  std::vector<std::string> tokens;
  size_t ii = 0;
  while (ii < raw.length()) {
    if (isspace(raw[ii])) {
      ii++;
      continue;
    }
    if (raw[ii] == '[' || raw[ii] == ']') {
      // use string constructor (size, char)
      tokens.push_back(std::string(1, raw[ii]));
      ii++;
      continue;
    }
    int beg = ii;
    while (isdigit(raw[ii])) {
      ii++;
    }
    tokens.push_back(raw.substr(beg, ii - beg));
  }
  return tokens;
}

// Parse user input string into array.
std::vector<std::vector<int>> parse(std::string raw) {
  // tokenizing and parsing /could/ be combined into one,
  // monsterous loop.
  std::vector<std::string> tokens = tokenize(raw);
  std::vector<std::vector<int>> parsed;
  size_t ii = 0;
  std::vector<int> sub;
  while (ii < tokens.size()) {
    if (tokens[ii] == "[") {
      sub.clear();
      ii++;
      continue;
    }
    if (tokens[ii] == "]") {
      parsed.push_back(sub);
      ii++;
      continue;
    }
    sub.push_back(std::stoi(tokens[ii]));
    ii++;
  }
  return parsed;
}

void print_board(std::vector<std::vector<int>> board) {
  for (size_t ii = 0; ii < board.size(); ii++) {
    for (size_t jj = 0; jj < board.size(); jj++) {
      switch(board[ii][jj]) {
        case UNKNOWN:
          std::cout << " ";
          break;
        case FALSE:
          std::cout << "x";
          break;
        case TRUE:
          std::cout << "█";
          break;
      }
    }
    std::cout << std::endl;
  }
}

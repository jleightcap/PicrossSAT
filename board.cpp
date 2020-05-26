#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <assert.h>

#include "io.h"
#include "board.h"

// String representation of board member
std::string
Board::render_board()
{
    std::string solution = board_string(&board);
    std::cout << solution << std::endl;
    return solution;
}

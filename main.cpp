#include <iostream>
#include <fstream>

#include "io.h"
#include "board.h"
#include "sat.h"

int main(int argc, char* argv[]) {
    std::string restrictRow;
    std::string restrictCol;

    // file input
    if (argc == 2) {
        std::ifstream input(argv[1]);
        if (input.is_open()) {
            std::getline(input, restrictRow);
            std::getline(input, restrictCol);
        }
        else {
            std::cerr << "Could not open file: " << argv[1] << std::endl;
            return -1;
        }
        input.close();
    }

    // stdin input
    else if (argc == 3) {
        restrictRow = argv[1];
        restrictCol = argv[2];
    }

    else {
        std::cerr << "Usage: ./picrosssat [FILE]; ./picrosssat [ROW] [COL]\n";
        return -1;
    }

    auto rowVec = parse(restrictRow);
    auto colVec = parse(restrictCol);

    Board b1(&rowVec, &colVec);
    SATExpr s(&b1);
    s.cnf();
    s.solve();
    std::clog << b1.boardString();

    return 0;
}

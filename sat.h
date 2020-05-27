#ifndef SAT_H
#define SAT_H

#include <minisat/core/Solver.h>

#include "board.h"

class SATExpr {
    private:
        std::vector<std::vector<Minisat::Lit>> dnfVec;
        std::vector<std::vector<Minisat::Lit>> cnfVec;

    public:
        // convert a Board into the corresponding DNF vector
        void dnf(Board* b);

        // convert a DNF vector to a CNF vector
        void cnf();

        // solve CNF vector
        void solve(Board* b);
};

#endif

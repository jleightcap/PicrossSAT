#ifndef SAT_H
#define SAT_H

#include <minisat/core/Solver.h>
#include "board.h"

class SATExpr {
    private:
        // Variable mapping uses row-major ordering,
        // board[ii][jj] => Var(ii + [jj * board.dimX])
        std::vector<std::vector<Minisat::Lit>> dnfVec;
        std::vector<std::vector<Minisat::Lit>> cnfVec;
        std::vector<Minisat::Lit> lits;

    public:
        // convert a Board into the corresponding DNF vector
        void dnf(Board* b);

        // convert a DNF vector to a CNF vector
        void cnf();

        // solve CNF vector
        void solve(Board* b);

        auto getDNF() { return dnfVec; }
        auto getCNF() { return cnfVec; }
};

std::vector<std::vector<int>> sumPermute(int n, int w, int h);

#endif

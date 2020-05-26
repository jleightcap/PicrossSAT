#include <minisat/core/Solver.h>
#include <iostream>

#include "board.h"

void
dnf(Board* b, Minisat::Solver* s, Minisat::vec<Minisat::Lit>* lits)
{
    auto A = s->newVar();
    lits->push(Minisat::mkLit(A));
}



void
solve(Board* b)
{
    using Minisat::mkLit;
    using Minisat::lbool;

    Minisat::Solver solver;
    Minisat::vec<Minisat::Lit> lits;

    // create DNF literals
    dnf(b, &solver, &lits);

    // Create variables
    auto A = solver.newVar();
    auto B = solver.newVar();
    auto C = solver.newVar();

    // Create the clauses
    solver.addClause( mkLit(A), ~mkLit(A));

    // Check for solution and retrieve model if found
    auto sat = solver.solve();
    if (sat) {
        std::clog << "SAT\n"
                  << "Model found:\n";
        std::clog << "A := " << (solver.modelValue(A) == l_True) << '\n';
        std::clog << "B := " << (solver.modelValue(B) == l_True) << '\n';
        std::clog << "C := " << (solver.modelValue(C) == l_True) << '\n';
    } else {
        std::clog << "UNSAT\n";
    }
}

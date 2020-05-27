#include <minisat/core/Solver.h>
#include <iostream>

#include "board.h"
#include "sat.h"

void
SATExpr::dnf(Board* b)
{
}



void
SATExpr::cnf()
{
}



void
SATExpr::solve(Board* b)
{
    using Minisat::mkLit;
    using Minisat::lbool;

    dnf(b); // generate DNF vector for given board
    cnf();  // convert DNF vector to CNF vector

    Minisat::Solver solver;
    Minisat::vec<Minisat::Lit> lits;

    // create DNF literals
    // auto vec = dnf(b, &solver, &lits);

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

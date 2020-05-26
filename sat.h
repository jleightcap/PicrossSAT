#ifndef SAT_H
#define SAT_H

#include <minisat/core/Solver.h>

#include "board.h"

auto dnf(Board* b, Minisat::Solver* s, Minisat::vec<Minisat::Lit>* lits);

void solve(Board* board);


#endif

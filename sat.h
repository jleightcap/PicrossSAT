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
        SATExpr(Board* b);
        ~SATExpr();

        // convert a Board into the corresponding DNF vector
        void dnf();

        // convert a DNF vector to a CNF vector
        void cnf();

        // solve CNF vector
        void solve(Board* b);

        auto getDNF() { return dnfVec; }
        auto getCNF() { return cnfVec; }
};



// all sets of max size w of numbers [1,h] that add up to n
// populated in strictly increasing order
std::vector<std::vector<int>> sumPermute(int n, int h, int w);



// prepend subvectors with zeros to given size
// ex (w=3): {{0}, {1,1}, {1,2,3}} -> {{0,0,0}, {0,1,1}, {1,2,3}}
// used for creating permutations of constant size
template<class T>
void zeroPad(std::vector<std::vector<T>>* v, int w);



// given a vector of vectors, return vector of all permutations of elements of subvectors
// ex: {{0,1}, {3,5}} -> {{0,1}, {1,0}, {3,5}, {5,3}}
template<class T>
std::vector<std::vector<T>> permute(std::vector<std::vector<T>>* v);



// filter out invalid whitespace vectors, for a vector B with |B|=n:
// - B_0 >= 0
// - B_n >= 0
// - B_1 .. B_{n-1} > 1
// where v is a vector of B.
void filterWhiteSpace(std::vector<std::vector<int>>* v);

#endif

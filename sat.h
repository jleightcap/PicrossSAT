#ifndef SAT_H
#define SAT_H

#include <minisat/core/Solver.h>
#include "board.h"

class SATExpr {
    private:
        // board dimensions
        int dimX;
        int dimY;

        // store pointer to board
        Board* board;

        // Variable mapping uses row-major ordering,
        // board[ii][jj] => Var(ii + jj*dimX)

        // vector of DNF expressions
        // outermost vector:                                  ]
        //   AND expressions                                  ]
        // middle vector:     ]                               ]
        //   OR expressions   ]                               ]--- permutations of board
        //                    ]--- permutations of row/column ]
        // innermost vector:  ]                               ]
        //   AND expressions  ]                               ]
        Minisat::vec<Minisat::vec<Minisat::vec<Minisat::Lit>>> dnfVec;

        // vector of CNF expressions
        Minisat::vec<Minisat::vec<Minisat::Lit>> cnfVec;
    public:
        SATExpr(Board* b);
        ~SATExpr();

        // convert DNF vector to CNF vector
        void cnf();

        // solve CNF vector
        void solve();

        auto getDNF() { return &dnfVec; }
        auto getCNF() { return &cnfVec; }

        void printDNF();
        void printCNF();
};



// parse restriction vectors into whitespace vectors
std::vector<std::vector<int>> restrictParse(std::vector<int> v, int dim);



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

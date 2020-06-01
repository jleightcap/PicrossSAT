#include <minisat/core/Solver.h>
#include <iostream>
#include <vector>

#include "board.h"
#include "sat.h"

using Minisat::mkLit;
using Minisat::lbool;
using std::vector;

template<class T>
void printArray(vector<vector<T>> v)
{
    for (auto& ii : v) {
        for (auto& jj : ii)
            std::clog << jj << " ";
        std::clog << std::endl;
    }
}



vector<vector<int>>
sumPermute(int n, int h, int w)
{
    vector<int> inner;
    vector<vector<int>> result;

    // hacky integer division ceiling: ceil(x/y) = x/y + (x%y != 0)
    for (int ii = (n/w + (n % w != 0)); ii <= h ; ii++) {
        inner.clear();
        inner.push_back(ii);
        if (n - ii == 0) {
            result.push_back(inner);
            return result;
        }
        vector<vector<int>> recur = sumPermute(n -ii, ii, w - 1);
        for (auto& nn : recur) {
            vector<int> sum;
            sum.reserve(inner.size() + nn.size());
            sum.insert(sum.end(), inner.begin(), inner.end());
            sum.insert(sum.end(), nn.begin(), nn.end());
            result.push_back(sum);
        }
    }
    return result;
}



void
SATExpr::dnf(Board* b)
{
    auto result = sumPermute(4,3,4);
    std::clog << "\n===RESULT===\n";
    printArray<int>(result);
    // the number of whitespace cells eps in a slice X with restriction R:
    // eps = len(X) - sum(R)
    //
    // state of slice, as vector of whitespace cells B and occupied R:
    // { b_0, r_0, b_1, r_1, ... , r_n, b_{n+1} }
    // where:
    //       - b_0, b_{n+1} >= 0,
    //       - b_1 .. b_n > 0,
    //       - sum(b) = eps
    //
    // example: X=5, R={1,1} -- some combinations:
    //   { 1, 0, 1, 0, 0 }   =>   B = { 0, 1, 2 }
    //   { 0, 1, 0, 1, 0 }   =>   B = { 1, 1, 1 }
    //   { 1, 0, 0, 0, 1 }   =>   B = { 0, 3, 0 }
    // for all combinations,
    //        - b_0 >= 0, b_2 >= 0
    //        - b_2 > 0
    //        - sum(B) = 3 = X - sum(R)

    // see header file for variable encoding, requires use of indexed for loops

    int dimX = b->getDimX();
    int dimY = b->getDimY();

    // column expressions
    for (int ii = 0; ii < dimX; ii++) {
        auto colVec = (*b->getColumnVec())[ii];
        // eps for X=colVec[ii]
        int eps = dimX;
        for (auto& nn : colVec) eps -= nn;
    }


    // row expressions
    for (int ii = 0; ii < dimY; ii++) {
        auto rowVec = (*b->getRowVec())[ii];
        // eps for X=rowVec[jj]
        int eps = dimY + 1 - rowVec.size();
        for (auto& nn : rowVec) eps -= nn;

        int h = 4;
        int n = 5;
        int w = 3;
        for (int ii = n; ii >= h/w; ii--) {
        }
    }
}



void
SATExpr::cnf()
{
}



void
SATExpr::solve(Board* b)
{
    dnf(b); // generate DNF vector for given board
    cnf();  // convert DNF vector to CNF vector

    /*
    Minisat::Solver solver;
    Minisat::vec<Minisat::Lit> lits;

    // create DNF literals
    // auto vec = dnf(b, &solver, &lits);

    // Create variables
    auto A = solver.newVar();
    auto B = solver.newVar();
    auto C = solver.newVar();
    auto D = solver.newVar();

    // Create the clauses
    solver.addClause( mkLit(A));
    solver.addClause( mkLit(B));
    solver.addClause( mkLit(C),  mkLit(D));
    solver.addClause(~mkLit(C), ~mkLit(D));
    solver.addClause( mkLit(A));
    solver.addClause( mkLit(C));
    solver.addClause( mkLit(B),  mkLit(D));
    solver.addClause(~mkLit(B), ~mkLit(D));

    // Check for solution and retrieve model if found
    auto sat = solver.solve();
    if (sat) {
        std::clog << "SAT" << std::endl << "Model found:\n";
        std::clog << "A := " << (solver.modelValue(A) == l_True) << '\n';
        std::clog << "B := " << (solver.modelValue(B) == l_True) << '\n';
        std::clog << "C := " << (solver.modelValue(C) == l_True) << '\n';
        std::clog << "D := " << (solver.modelValue(D) == l_True) << '\n';
    } else {
        std::clog << "UNSAT\n";
    }
    */
}

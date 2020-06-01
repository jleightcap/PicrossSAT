#include <minisat/core/Solver.h>
#include <iostream>
#include <vector>

#include "board.h"
#include "sat.h"

using Minisat::mkLit;
using Minisat::lbool;
using std::vector;



template<class T>
void printArray(const vector<vector<T>>* v)
{
    for (auto& ii : *v) {
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
            // append each element of recur to inner, add to results
            vector<int> sum;
            sum.reserve(inner.size() + nn.size());
            sum.insert(sum.end(), nn.begin(), nn.end());
            sum.insert(sum.end(), inner.begin(), inner.end());
            result.push_back(sum);
        }
    }
    return result;
}



template<class T>
void
zeroPad(vector<vector<T>>* v)
{
    // maximum size (probably better way... lambdas?)
    // alternately, this would be more effecient to do in sumPermute
    // this seems more modular & testable, but test overhead
    size_t max = 0;
    for(auto& vv : *v) max = (vv.size() > max) ? vv.size() : max;

    for(auto& vv : *v) {
        vector<int> padding(max - vv.size(), 0);
        vv.insert(vv.begin(), padding.begin(), padding.end());
    }
}



template<class T>
vector<vector<T>>
permute(vector<vector<T>>* v)
{
    vector<vector<T>> permutes;
    for (auto& vv : *v) {
        do {
            permutes.push_back(vv);
        } while(std::next_permutation(vv.begin(), vv.end()));
    }
    return permutes;
}



void
filterWhiteSpace(vector<vector<int>>* perms)
{
    perms->erase(
        // LAMBDA TIME!
        std::remove_if(perms->begin(), perms->end(),
            [](const vector<int>& ws) {
                // elements strictly >= 0, don't check B_0 and B_n (always valid)
                // checking B_1 .. B_{n-1},
                for(size_t ii = 1; ii < ws.size() - 1; ii++)
                    if(ws[ii] < 1) return true;
                return false;
            }),
        perms->end()
    );
}



void
SATExpr::dnf(Board* b)
{
    auto v = sumPermute(3,2,3);
    zeroPad<int>(&v);
    printArray(&v);
    std::clog << std::endl;
    auto permutes = permute(&v);
    printArray(&permutes);
    std::clog << std::endl;

    filterWhiteSpace(&permutes);
    printArray(&permutes);
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

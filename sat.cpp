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



SATExpr::SATExpr(Board* b)
{
    auto dimX = b->getDimX();
    auto dimY = b->getDimY();
    auto rowRestricts = *b->getRowVec();
    auto colRestricts = *b->getColumnVec();

    for (auto& rowRestrict : rowRestricts) {
        auto permutes = restrictParse(rowRestrict, dimX);

        // actual board states
        for (auto& nn : permutes) {
            Minisat::vec<Minisat::Lit> inner;
            int idx = 0; // index into vector, needed for variable encoding
            
            for (size_t ii = 0; ii < nn.size(); ii++) {
                for (int jj = 0; jj < nn[ii]; jj++) {
                    std::clog << "0";
                    idx++;
                }
                for (int jj = 0; jj < rowRestrict[ii]; jj++) {
                    std::clog << "1";
                    idx++;
                }
            }
            std::clog << std::endl;
        }
        std::clog << std::endl;
    }

    for (auto& colRestrict : colRestricts) {
        auto permutes = restrictParse(colRestrict, dimY);

        // actual board states
        /*
        for (auto& nn : permutes) {
            for (size_t ii = 0; ii < nn.size(); ii++) {
                for (int jj = 0; jj < nn[ii]; jj++) std::clog << "0";
                for (int jj = 0; jj < colRestrict[ii]; jj++) std::clog << "1";
            }
            std::clog << std::endl;
        }
        std::clog << std::endl;
        */
    }
}



vector<vector<int>>
restrictParse(std::vector<int> v, int dim)
{
    int sum = 0;
    for (auto& nn : v) sum += nn;

    int n = dim - sum;
    int h = n;
    int w = v.size() + 1;

    auto sumVec = sumPermute(n,h,w);
    zeroPad<int>(&sumVec, w);
    auto sumPermute = permute(&sumVec);
    filterWhiteSpace(&sumPermute);

    return sumPermute;
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
zeroPad(vector<vector<T>>* v, int w)
{
    for(auto& vv : *v) {
        vector<int> padding(w - vv.size(), 0);
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
SATExpr::solve()
{
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
}

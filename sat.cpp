#include <minisat/core/Solver.h>
#include <iostream>
#include <vector>

#include "board.h"
#include "sat.h"

using Minisat::mkLit;
using Minisat::lbool;
using std::vector;



SATExpr::~SATExpr()
{
    dnfVec.clear();
    cnfVec.clear();
}



SATExpr::SATExpr(Board* b)
{
    dimX = b->getDimX();
    dimY = b->getDimY();
    auto rowRestricts = *b->getRowVec();
    auto colRestricts = *b->getColumnVec();

    // iterate over rows and columns
    // try to abstract these: almost entirely the same procedure,
    // except with swapped ordering for variable encoding

    for (size_t yy = 0; yy < rowRestricts.size(); yy++) {
        auto permutes = restrictParse(rowRestricts[yy], dimX);
        Minisat::vec<Minisat::vec<Minisat::Lit>> permuteDNF;

        // convert row permutations to CNF expression
        for (auto& permute : permutes) {
            Minisat::vec<Minisat::Lit> inner;
            int xx = 0; // index into row, needed for variable encoding
            
            for (size_t ii = 0; ii < permute.size(); ii++) {
                for (int jj = 0; jj < permute[ii]; jj++) {
                    inner.push( ~mkLit(xx + yy*dimX) );
                    xx++;
                }
                for (int jj = 0; jj < rowRestricts[yy][ii]; jj++) {
                    inner.push(  mkLit(xx + yy*dimX) );
                    xx++;
                }
            }
            // convoluted 'push_back' using MiniSat's Vec wrapper
            permuteDNF.growTo(permuteDNF.size() + 1);
            inner.moveTo(permuteDNF.last());
        }
        // convoluted 'push_back' using MiniSat's Vec wrapper
        dnfVec.growTo(dnfVec.size() + 1);
        permuteDNF.moveTo(dnfVec.last());
    }

    // convert column permutations to CNF expression
    for (size_t xx = 0; xx < colRestricts.size(); xx++) {
        auto permutes = restrictParse(colRestricts[xx], dimY);
        Minisat::vec<Minisat::vec<Minisat::Lit>> permuteDNF;

        for (auto& permute : permutes) {
            Minisat::vec<Minisat::Lit> inner;
            int yy = 0; // index into column, need for variable encoding

            for (size_t ii = 0; ii < permute.size(); ii++) {
                for (int jj = 0; jj < permute[ii]; jj++) {
                    inner.push( ~mkLit(xx + yy*dimX) );
                    yy++;
                }
                for (int jj = 0; jj < colRestricts[xx][ii]; jj++) {
                    inner.push(  mkLit(xx + yy*dimX) );
                    yy++;
                }
            }

            // convoluted 'push_back' using MiniSat's Vec wrapper
            permuteDNF.growTo(permuteDNF.size() + 1);
            inner.moveTo(permuteDNF.last());
        }
        // convoluted 'push_back' using MiniSat's Vec wrapper
        dnfVec.growTo(dnfVec.size() + 1);
        permuteDNF.moveTo(dnfVec.last());
    }

    /*
    for (int ii = 0; ii < dnfVec.size(); ii++) {
        for (int jj = 0; jj < dnfVec[ii].size(); jj++) {
            for (int kk = 0; kk < dnfVec[ii][jj].size(); kk++) 
                std::clog << dnfVec[ii][jj][kk].x << " ";
            std::clog << std::endl;
        }
        std::clog << std::endl;
    }
    */
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
SATExpr::cnf()
{
    // each element of DNF vector is valid DNF expression of form sum(prod(x))
    // transforming each element sum(prod(x)) -> {prod(sum(x))} gives valid CNF vector
    std::clog << "frick\n";
    return;
}



void
SATExpr::solve()
{
    Minisat::Solver solver;

    // initialize solver variables, dimX*dimY total variables
    for (int ii = 0; ii < dimX * dimY; ii++)
        solver.newVar();

    // add expressions
    // (just DNF for right now, completely meaningless)
    for (auto& nn : dnfVec)
        solver.addClause(*nn);

    auto sat = solver.solve();
    if (sat) {
        std::clog << " SAT \n=====\n";
        for (int ii = 0; ii < dimX; ii++) {
            for (int jj = 0; jj < dimY; jj++)
                std::clog << (solver.modelValue(ii + dimX*jj) == l_True);
            std::clog << std::endl;
        }
    } else {
        std::clog << "UNSAT\n";
    }
}

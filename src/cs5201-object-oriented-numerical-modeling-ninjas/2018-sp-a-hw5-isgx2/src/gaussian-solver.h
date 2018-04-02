//
//  gaussian-solver.h
//  src
//
//  Illya Starikov, Section 1A, 18183141
//  cs5211 – Object Oriented Numerical Modeling
//

#ifndef gaussian_solver_h
#define gaussian_solver_h

#include "lib/vector.h"
#include "lib/square-matrix.h"
#include "exceptions/gaussian-exception.h"

/** @class LinearSystemSolver
 *
 *  @brief Functor to solve the linear equation Ax = b.
 *
 **/
template <class T>
class LinearSystemSolver {
private:
    unsigned findNewPivot(const SquareMatrix<T>& A, const unsigned column);
    void swapRows(SquareMatrix<T>& A, Vector<T>& b, const unsigned rowOne, const unsigned rowTwo);
    void rowReduce(SquareMatrix<T>& A, Vector<T>& b, const unsigned column);
    Vector<T> backSubstitute(SquareMatrix<T>& A, Vector<T>& b);

public:
    Vector<T> operator()(SquareMatrix<T> A, Vector<T> b);
};

#include "gaussian-solver.hpp"

#endif /* gaussian-solver_h */


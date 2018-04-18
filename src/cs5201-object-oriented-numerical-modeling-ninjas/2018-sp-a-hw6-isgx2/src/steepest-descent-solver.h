//
//  steepest-descent-solver.h
//  src
//
//  Created by Illya Starikov on 04/16/18.
//  Copyright 2018. Illya Starikov. All rights reserved.
//

#ifndef steepest_descent_solver_h
#define steepest_descent_solver_h

#include "../lib/eigen.h"
#include "exceptions/steepest-descent-exception.h"

/** @class SteepestDescentSolver
 *
 *  @brief Functor to solve the linear equation Ax = b.
 *
 **/
template <class T>
class SteepestDescentSolver {
public:
    const unsigned MAX_ITERATIONS = 10000;
    const T EPSILON = 0.00000001;

    Vector<T> operator()(const SymmetricMatrix<T>& A, const Vector<T> b);
};

#include "steepest-descent-solver.hpp"

#endif /* steepest-descent-solver_h */


//
//  steepest-descent-solver.h
//  src
//
//  Created by Illya Starikov on 04/16/18.
//  Copyright 2018. Illya Starikov. All rights reserved.
//

/**
 *  @brief  Solve a system where A is symmetric and diagonally dominant.
 *
 *  @param  A The coefficient matrix.
 *  @param  b The solution vector to the coefficient matrix @p A.
 *
 *  @throws NonDiagonallyDominantMatrixError If @p A is not diagonally dominant, an error object gets thrown.
 *
 *  @return  The solution vector `x`.
 *
 *  @pre    See `throws`.
 *  @post   See `return`.
 **/

template <typename T>
Vector<T> SteepestDescentSolver<T>::operator()(const SymmetricMatrix<T>& A, const Vector<T> b) {

    auto x = b; // initial guess is the b vector, cause why not
    auto alpha = T();

    unsigned i = 0;
    auto residual = b - (A * x); // if A is the identity matrix, then A * x should be b.

    if (!isDiagonallyDominant(A)) {
        throw NonDiagonallyDominantMatrixError();
    }

    while (norm(residual) > EPSILON && i++ < MAX_ITERATIONS) {
        residual = b - (A * x);
        alpha = (residual * residual) /  ((A * residual) * residual);
        x += alpha * residual;
    }

    return x;
}
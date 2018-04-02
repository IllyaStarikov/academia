//
//  gaussian-solver.h
//  src
//
//  Illya Starikov, Section 1A, 18183141
//  cs5211 – Object Oriented Numerical Modeling
//

#ifndef gaussian_solver_hpp
#define gaussian_solver_hpp

/**
 *  @brief  Find the new pivot row for partial pivoting. Does so by
 *          finding the maximal (absolute) element in @p column.
 *
 *  @param  A The Coefficient matrix for the linear system.
 *  @param  column The column in which to the find the new pivot row.
 *
 *  @return The column row that should be the new pivot row.
 *
 *  @post   None.
 *  @post   See `return`.
 **/
template <typename T>
unsigned LinearSystemSolver<T>::findNewPivot(const SquareMatrix<T>& A, const unsigned column) {
    auto maxElement = fabs(A(column, column));

    auto size = A.columns();
    auto maxRow = column;

    for (unsigned i = column + 1; i < size; i++) {
        if (maxElement < fabs(A(i, column))) {
            maxElement = fabs(A(i, column));
            maxRow = i;
        }
    }

    return maxRow;
}

/**
 *  @brief  Swap two rows in @p A and @p b.
 *
 *  @param  A The Coefficient matrix for the linear system.
 *  @param  b The solution vector to the coefficient matrix @p A.
 *  @param  rowOne The first row to swap.
 *  @param  rowTwo The second row to swap.
 *
 *  @pre    None.
 *  @post   See `brief`.
 **/
template <typename T>
void LinearSystemSolver<T>::swapRows(SquareMatrix<T>& A, Vector<T>& b, const unsigned rowOne, const unsigned rowTwo) {
    auto size = A.columns();

    for (unsigned i = 0; i < size; i++) {
        std::swap(A(rowOne, i), A(rowTwo, i));
    }

    std::swap(b[rowOne], b[rowTwo]);
}

/**
 *  @brief  Make all the rows underneath @p row zero.
 *
 *  @param  A The Coefficient matrix for the linear system.
 *  @param  b The solution vector to the coefficient matrix @p A.
 *  @param  row The row to which make all zeros underneath.
 *
 *  @throws SingularMatrixError If the augmented Matrix [A|b] is inconsistent,
 *          a, SingularMatrixError will be thrown.
 *
 *  @pre    None.
 *  @post   See `brief`.
 **/ template <typename T>
void LinearSystemSolver<T>::rowReduce(SquareMatrix<T>& A, Vector<T>& b, const unsigned row) {
    auto rows = A.rows(), columns = A.columns();

    for (unsigned i = row + 1; i < columns; i++) {
        if (A(row, row) == 0) { throw SingularMatrixError(); }
        T multiplier = -A(i, row) / A(row, row);

        for (unsigned j = row; j < rows; j++) {
            if (row == j) {
                A(i, j) = 0;
            } else {
                A(i, j) += multiplier * A(row, j);
            }
        }

        b[i] += multiplier * b[row];
    }
}

/**
 *  @brief  Back substitute from the echelon form into a solution vector.
 *
 *  @param  A The Coefficient matrix for the linear system (upper triangular form).
 *  @param  b The solution vector to the coefficient matrix @p A.
 *
 *  @throws SingularMatrixError If the augmented Matrix [A|b] is inconsistent,
 *          a, SingularMatrixError will be thrown.
 *
 *  @return The solution to the original equation [A|b].
 *
 *  @warning @p A must be in echelon form.
 *
 *  @pre    See `warning`.
 *  @post   See `return`.
 **/
template <typename T>
Vector<T> LinearSystemSolver<T>::backSubstitute(SquareMatrix<T>& A, Vector<T>& b) {
    auto size = A.rows();
    auto result = Vector<T>(A.rows());

    for (int i = size - 1; i >= 0; i--) {
        if (A(i, i) == 0) { throw SingularMatrixError(); }

        result[i] = b[i] / A(i, i);
        for (int j = i - 1; j >= 0; j--) {
            b[j] -= A(j, i) * result[i];
        }
    }

    return result;
}

/**
 *  @brief  Solve for the linear system @p A x = @p b, returning the solution `Vector` x.
 *
 *  @param  A The Coefficient matrix for the linear system.
 *  @param  b The solution vector to the coefficient matrix @p A.
 *
 *  @throws SingularMatrixError If the augmented Matrix [A|b] is inconsistent or has infinitely many solutions,
 *          a SingularMatrixError will be thrown.
 *
 *  @return The solution to @p A x = @p b.
 *
 *  @pre    See `throws`.
 *  @post   See `return`.
 **/
template <typename T>
Vector<T> LinearSystemSolver<T>::operator()(SquareMatrix<T> A, Vector<T> b) {
    auto size = b.size();

    for (unsigned i = 0; i < size; i++) {
        auto pivotRow = findNewPivot(A, i);
        swapRows(A, b, i, pivotRow);
        rowReduce(A, b, i);
    }

    return backSubstitute(A, b);
}


#endif /* gaussian-solver_h */


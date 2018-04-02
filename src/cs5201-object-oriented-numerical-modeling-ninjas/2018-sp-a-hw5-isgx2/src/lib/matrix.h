//
//  matrix.h
//  lib
//
//  Illya Starikov, Section 1A, 18183141
//  cs5211 – Object Oriented Numerical Modeling
//

#ifndef matrix_h
#define matrix_h

#include "vector.h"

/** @class Matrix
 *
 *  @brief An interface for a Matrix.
 *
 *  @tparam T The type of the elements the matrix stores.
 **/
template <class T>
class Matrix {
public:
    // MARK: Functions
    virtual void resize(const size_t rows) = 0;
    virtual void resize(const size_t rows, const size_t columns) = 0;

    // MARK: Operators
    virtual T& operator()(const int row, const int column) = 0;
    virtual const T& operator()(const int row, const int column) const = 0;

    // MARK: Properties
    virtual T zero() const noexcept = 0;
    virtual size_t rows() const noexcept = 0;
    virtual size_t columns() const noexcept = 0;
};


#endif /* matrix_h */


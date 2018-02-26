//
//  lower-triangular-matrix.h
//  lib
//
//  Illya Starikov, Section 1A, 18083141
//  cs5201 – Object Oriented Numerical Modeling
//

#ifndef lower_triangular_matrix_h
#define lower_triangular_matrix_h

#include "a-matrix.h"
#include "vector.h"

#include <initializer_list>
#include <iostream>

/** @class LowerTriangularMatrix
 *
 *  @brief A LowerTraingularMatrix class that is comprised of a column vector
 *         of row vectors.
 *
 *  @tparam T must have the following operations defined:
 *  - Addition (`+`)
 *  - Subtraction (`-`)
 *  - Multiplication (`*`)
 *  - Division (`/`)
 *  - Equal To (`==`)
 *  - Negation (`-T`)
 **/

template<class T>
class LowerTriangularMatrix: public SquareMatrix<T> {
public:
    // MARK: Constructors
    LowerTriangularMatrix();
    LowerTriangularMatrix(const int size);
    LowerTriangularMatrix(const int size, const T& initialValue);
    LowerTriangularMatrix(const std::initializer_list<std::initializer_list<T>> list);
    LowerTriangularMatrix(const LowerTriangularMatrix& other);

    // MARK: Destructors
    ~LowerTriangularMatrix();

    // MARK: Operators
    LowerTriangularMatrix<T>& operator=(const LowerTriangularMatrix<T>& other);
    LowerTriangularMatrix<T>& operator=(const LowerTriangularMatrix<T>&& other);

    virtual Vector<T>& operator[](const int index);
    virtual const Vector<T>& operator[](const int& index) const;
};


#include "lower-triangular-matrix.hpp"

#endif /* lower-triangular-matrix_h */

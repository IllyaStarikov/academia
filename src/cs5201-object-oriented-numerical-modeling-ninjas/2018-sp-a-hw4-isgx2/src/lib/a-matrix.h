//
//  a-matrix.h
//  lib
//
//  Illya Starikov, Section 1A, 18083141
//  cs5201 – Object Oriented Numerical Modeling
//

#ifndef a_matrix_h
#define a_matrix_h

#include <iostream>
#include "Vector.h"

/** @class SquareMatrix
 *
 *  @brief A Square Matrix class that is comprised of a column vector
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
class SquareMatrix {
protected:
    Vector<Vector<T>> data;
    int size;

public:
    // MARK: Operators
    virtual Vector<T>& operator[](int index) = 0;
    virtual const Vector<T>& operator[](const int& index) const = 0;

    // Mark: Generic Functions
    const Vector<T> mainDiagonal();

    // MARK: Getters/Setters
    int magnitude() const noexcept { return size; }

    // MARK: Friend Functions
    template <typename S>
    friend std::ostream& operator<<(std::ostream& os, const SquareMatrix<S>& other);
};

#include "a-matrix.hpp"

#endif /* a_matrix_h */


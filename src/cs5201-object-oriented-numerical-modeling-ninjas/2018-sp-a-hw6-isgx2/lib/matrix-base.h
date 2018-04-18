//
//  matrix-base.h
//  lib
//
//  Created by Illya Starikov on 04/11/18.
//  Copyright 2018. Illya Starikov. All rights reserved.
//

#ifndef matrix_base_h
#define matrix_base_h

#include "matrix.h"

// Forward Declaration For RectangularMatrix
template <class T>
class RectangularMatrix;

/** @class BaseMatrix
 *
 *  @brief A base that defines default behavior for a matrix.
 *
 *  @tparam T must have the following operations defined:
 *  - Addition (`+`)
 *  - Subtraction (`-`)
 *  - Multiplication (`*`)
 *  - Equal To (`==`)
 *  - Less Than (`<`)
 *  - Greater Than (`>`)
 *  - Negation (`-T`)
 **/
template <class T>
class BaseMatrix : virtual public Matrix<T> {
    static T _zero;

public:
    template <class S> friend bool operator==(const BaseMatrix<S>& leftHandSide, const BaseMatrix<S>& rightHandSide);
    template <class S> friend bool operator!=(const BaseMatrix<S>& leftHandSide, const BaseMatrix<S>& rightHandSide);

    template <class S> friend RectangularMatrix<S> operator*(const BaseMatrix<S>& leftHandSide, const BaseMatrix<S>& rightHandSide);
    template <class S> friend RectangularMatrix<S> operator+(const BaseMatrix<S>& leftHandSide, const BaseMatrix<S>& rightHandSide);
    template <class S> friend RectangularMatrix<S> operator-(const BaseMatrix<S>& leftHandSide, const BaseMatrix<S>& rightHandSide);

    template <class S> friend RectangularMatrix<S> operator*(const S& leftHandSide, const Matrix<S>& rightHandSide);

    template <class S> friend Vector<S> operator*(const Matrix<S>& leftHandSide, const Vector<S>& rightHandSide);
    template <class S> friend RectangularMatrix<S> operator-(const BaseMatrix<S>& leftHandSide);
    template <class S> friend RectangularMatrix<S> transpose(const BaseMatrix<S>& leftHandSide);
    template <class S> friend bool isDiagonallyDominant(const BaseMatrix<S>& leftHandSide);

    virtual T& zero() const noexcept override;

    template <class S> friend std::ostream& operator<<(std::ostream& os, const Matrix<S>& other);
};

#include "matrix-base.hpp"

#endif /* matrix-base_h */


//
//  symmetric-matrix.h
//  lib
//
//  Created by Illya Starikov on 04/16/18.
//  Copyright 2018. Illya Starikov. All rights reserved.
//

#ifndef symmetric_matrix_h
#define symmetric_matrix_h

#include "matrix-base.h"

/** @class RectangularMatrix
 *
 *  @brief A representation of a symmetric matrix.
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
template <typename T>
class SymmetricMatrix : public BaseMatrix<T> {
protected:
    std::unique_ptr<Vector<T>[]> data;
    size_t dimension;

public:
    SymmetricMatrix();
    SymmetricMatrix(const size_t rows, const size_t columns);
    SymmetricMatrix(SymmetricMatrix<T>&& other);
    SymmetricMatrix(const SymmetricMatrix<T>& other);
    SymmetricMatrix(const std::initializer_list<std::initializer_list<T>> list);

    virtual SymmetricMatrix<T>& operator=(SymmetricMatrix<T>& other);
    virtual SymmetricMatrix<T>& operator=(SymmetricMatrix<T>&& other);

    void operator+=(const SymmetricMatrix<T>& rightHandSide);
    void operator-=(const SymmetricMatrix<T>& rightHandSide);

    template <class S> friend SymmetricMatrix<S> operator+(const SymmetricMatrix<S>& leftHandSide, const SymmetricMatrix<S>& rightHandSide);
    template <class S> friend SymmetricMatrix<S> operator-(const SymmetricMatrix<S>& leftHandSide, const SymmetricMatrix<S>& rightHandSide);

    template <class S> friend SymmetricMatrix<S> operator-(const SymmetricMatrix<S>& leftHandSide);
    template <class S> friend SymmetricMatrix<S> transpose(const SymmetricMatrix<S>& leftHandSide);

    virtual T& operator()(const int row, const int column) override;
    virtual const T& operator()(const int row, const int column) const override;

    virtual void resize(const size_t rows, const size_t columns) override;

    virtual size_t rows() const noexcept override { return dimension; }
    virtual size_t columns() const noexcept override { return dimension; }
};

#include "symmetric-matrix.hpp"

#endif /* symmetric-matrix_h */


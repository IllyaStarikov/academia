//
//  diagonal-matrix.h
//  lib
//
//  Created by Illya Starikov on 04/15/18.
//  Copyright 2018. Illya Starikov. All rights reserved.
//

#ifndef diagonal_matrix_h
#define diagonal_matrix_h

#include "matrix-base.h"

/** @class DiagonalMatrix
 *
 *  @brief A representation of a diagonal matrix.
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
class DiagonalMatrix : public BaseMatrix<T> {
protected:
    Vector<T> data;
    size_t _rows, _columns;

public:
    DiagonalMatrix();
    DiagonalMatrix(const size_t rows, const size_t columns);
    DiagonalMatrix(DiagonalMatrix<T>&& other);
    DiagonalMatrix(const DiagonalMatrix<T>& other);
    DiagonalMatrix(const std::initializer_list<std::initializer_list<T>> list);

    virtual DiagonalMatrix<T>& operator=(DiagonalMatrix<T>& other);
    virtual DiagonalMatrix<T>& operator=(DiagonalMatrix<T>&& other);

    void operator*=(const DiagonalMatrix<T>& rightHandSide);
    void operator+=(const DiagonalMatrix<T>& rightHandSide);
    void operator-=(const DiagonalMatrix<T>& rightHandSide);

    template <class S> friend DiagonalMatrix<S> operator*(const DiagonalMatrix<S>& leftHandSide, const DiagonalMatrix<S>& rightHandSide);
    template <class S> friend DiagonalMatrix<S> operator+(const DiagonalMatrix<S>& leftHandSide, const DiagonalMatrix<S>& rightHandSide);
    template <class S> friend DiagonalMatrix<S> operator-(const DiagonalMatrix<S>& leftHandSide, const DiagonalMatrix<S>& rightHandSide);

    template <class S> friend DiagonalMatrix<S> operator*(const S& leftHandSide, const DiagonalMatrix<S>& rightHandSide);
    template <class S> friend DiagonalMatrix<S> operator-(const DiagonalMatrix<S>& leftHandSide);
    template <class S> friend DiagonalMatrix<S> transpose(const DiagonalMatrix<S>& leftHandSide);

    virtual void resize(const size_t rows, const size_t columns) override;

    virtual T& operator()(const int row, const int column) override;
    virtual const T& operator()(const int row, const int column) const override;

    virtual size_t rows() const noexcept override { return _rows; }
    virtual size_t columns() const noexcept override { return _columns; }

};

#include "diagonal-matrix.hpp"

#endif /* diagonal-matrix_h */


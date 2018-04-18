//
//  banded-matrix.h
//  lib
//
//  Created by Illya Starikov on 04/15/18.
//  Copyright 2018. Illya Starikov. All rights reserved.
//

#ifndef banded_matrix_h
#define banded_matrix_h

#include "matrix-base.h"

/** @class BandedMatrix
 *
 *  @brief A representation of a banded matrix.
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
class BandedMatrix : public BaseMatrix<T> {
protected:
    Vector<T> upperBand, middleBand, lowerBand;
    size_t _rows, _columns;

public:
    BandedMatrix();
    BandedMatrix(const size_t rows, const size_t columns);
    BandedMatrix(BandedMatrix<T>&& other);
    BandedMatrix(const BandedMatrix<T>& other);
    BandedMatrix(const std::initializer_list<std::initializer_list<T>> list);

    virtual BandedMatrix<T>& operator=(BandedMatrix<T>& other);
    virtual BandedMatrix<T>& operator=(BandedMatrix<T>&& other);

    void operator+=(const BandedMatrix<T>& rightHandSide);
    void operator-=(const BandedMatrix<T>& rightHandSide);

    template <class S> friend BandedMatrix<S> operator+(const BandedMatrix<S>& leftHandSide, const BandedMatrix<S>& rightHandSide);
    template <class S> friend BandedMatrix<S> operator-(const BandedMatrix<S>& leftHandSide, const BandedMatrix<S>& rightHandSide);

    template <class S> friend BandedMatrix<S> operator-(const BandedMatrix<S>& leftHandSide);
    template <class S> friend BandedMatrix<S> transpose(const BandedMatrix<S>& leftHandSide);

    virtual void resize(const size_t rows, const size_t columns) override;

    virtual T& operator()(const int row, const int column) override;
    virtual const T& operator()(const int row, const int column) const override;

    virtual size_t rows() const noexcept override { return _rows; }
    virtual size_t columns() const noexcept override { return _columns; }
};

#include "banded-matrix.hpp"

#endif /* banded-matrix_h */
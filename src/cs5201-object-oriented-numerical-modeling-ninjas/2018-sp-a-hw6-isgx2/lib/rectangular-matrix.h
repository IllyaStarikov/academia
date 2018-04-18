//
//  square-matrix.h
//  lib
//
//  Illya Starikov, Section 1A, 18183141
//  cs5211 – Object Oriented Numerical Modeling
//

#ifndef rectangular_matrix_hpp
#define rectangular_matrix_hpp

#include "exceptions/exceptions.h"
#include "matrix-base.h"

#include <iostream>
#include <iomanip>
#include <initializer_list>
#include <memory>
#include <limits>


/** @class RectangularMatrix
 *
 *  @brief A representation of an M x N matrix.
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
class RectangularMatrix : public BaseMatrix<T> {
protected:
    std::unique_ptr<Vector<T>[]> data;
    size_t _rows, _columns;

public:
    RectangularMatrix();
    RectangularMatrix(const size_t rows, const size_t columns);
    RectangularMatrix(RectangularMatrix<T>&& other);
    RectangularMatrix(const RectangularMatrix<T>& other);
    RectangularMatrix(const std::initializer_list<std::initializer_list<T>> list);

    virtual RectangularMatrix<T>& operator=(RectangularMatrix<T>& other);
    virtual RectangularMatrix<T>& operator=(RectangularMatrix<T>&& other);

    void operator*=(const RectangularMatrix<T>& rightHandSide);
    void operator+=(const RectangularMatrix<T>& rightHandSide);
    void operator-=(const RectangularMatrix<T>& rightHandSide);

    template <class S> friend RectangularMatrix<S> operator*(const S& leftHandSide, const RectangularMatrix<S>& rightHandSide);
    template <class S> friend RectangularMatrix<S> operator*(const RectangularMatrix<S>& leftHandSide, const RectangularMatrix<S>& rightHandSide);

    virtual void resize(const size_t rows, const size_t columns) override;

    virtual T& operator()(const int row, const int column) override;
    virtual const T& operator()(const int row, const int column) const override;

    virtual size_t rows() const noexcept override { return _rows; }
    virtual size_t columns() const noexcept override { return _columns; }
};

#include "rectangular-matrix.hpp"

#endif /* square_matrix_h */


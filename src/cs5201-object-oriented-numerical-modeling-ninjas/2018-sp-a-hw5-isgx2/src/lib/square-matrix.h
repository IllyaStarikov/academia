//
//  square-matrix.h
//  lib
//
//  Illya Starikov, Section 1A, 18183141
//  cs5211 – Object Oriented Numerical Modeling
//

#ifndef square_matrix_h
#define square_matrix_h

#include "../exceptions/matrix-exception.h"
#include "matrix.h"

#include <iostream>
#include <iomanip>
#include <initializer_list>
#include <memory>
#include <limits>


/** @class SquareMatrix
 *
 *  @brief A representation of an N x N matrix.
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
class SquareMatrix : public Matrix<T> {
    T zeroElement;

    std::unique_ptr<Vector<T>[]> data;
    size_t dimension;

    int precision = 8;
public:
    SquareMatrix(const T zero=T());
    SquareMatrix(const SquareMatrix<T>& other);
    SquareMatrix(const size_t size, const T zero=T());
    SquareMatrix(const std::initializer_list<std::initializer_list<T>> list, const T zero=T());
    SquareMatrix(SquareMatrix<T>&& other);

    virtual void resize(const size_t rows) override;
    virtual void resize(const size_t rows, const size_t columns) override;

    virtual SquareMatrix<T>& operator=(SquareMatrix<T>& other);
    virtual SquareMatrix<T>& operator=(SquareMatrix<T>&& other);

    template <class S> friend SquareMatrix<S> operator-(const SquareMatrix<S>& leftHandSide);
    template <class S> friend SquareMatrix<S> transpose(const SquareMatrix<S>& leftHandSide);

    template <class S> friend bool operator==(const SquareMatrix<S>& leftHandSide, const SquareMatrix<S>& rightHandSide);
    template <class S> friend bool operator!=(const SquareMatrix<T>& leftHandSide, const SquareMatrix<T>& rightHandSide);

    template <class S, class P> friend SquareMatrix<S> operator*(const SquareMatrix<S>& leftHandSide, const SquareMatrix<S>& rightHandSide);
    template <class S, class P> friend SquareMatrix<S> operator+(const SquareMatrix<S>& leftHandSide, const SquareMatrix<P>& rightHandSide);
    template <class S, class P> friend SquareMatrix<S> operator-(const SquareMatrix<S>& leftHandSide, const SquareMatrix<P>& rightHandSide);

    template <class S, class P> friend void operator*=(SquareMatrix<S>& leftHandSide, const SquareMatrix<P>& rightHandSide);
    template <class S, class P> friend void operator+=(SquareMatrix<S>& leftHandSide, const SquareMatrix<P>& rightHandSide);
    template <class S, class P> friend void operator-=(SquareMatrix<S>& leftHandSide, const SquareMatrix<P>& rightHandSide);

    template <class S, class P> friend SquareMatrix<S> operator*(const S leftHandSide, const SquareMatrix<P>& rightHandSide);
    template <class S, class P> friend Vector<S> operator*(const SquareMatrix<S> leftHandSide, const Vector<P>& rightHandSide);

    virtual T& operator()(const int row, const int column) override;
    virtual const T& operator()(const int row, const int column) const override;

    virtual T zero() const noexcept override { return this -> zeroElement; }

    virtual size_t rows() const noexcept override { return dimension; }
    virtual size_t columns() const noexcept override { return dimension; }

    // MARK: Friend Functions
    template <class S> friend std::ostream& operator<<(std::ostream& os, const SquareMatrix<S>& other);
};


#include "square-matrix.hpp"

#endif /* square_matrix_h */


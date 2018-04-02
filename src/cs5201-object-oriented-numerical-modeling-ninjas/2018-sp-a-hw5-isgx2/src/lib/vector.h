//
//  vector.h
//  lib
//
//  Illya Starikov, Section 1A, 18083141
//  cs5201 – Object Oriented Numerical Modeling
//

#ifndef vector_h
#define vector_h

#include <iostream>
#include <iomanip>
#include <initializer_list>
#include <memory>

#include "../exceptions/vector-exception.h"

/** @class Vector
 *
 *  @brief A representation of a column vector.
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
class Vector {
    std::unique_ptr<T[]> data;
    size_t _size;

    int precision = 8;

public:
    // MARK: Constructors
    Vector();
    Vector(const size_t size);
    Vector(const size_t size, const T& initialValue);
    Vector(const std::initializer_list<T> list);
    Vector(const Vector<T>& other);
    Vector(Vector&& other);

    // MARK: Destructor
    ~Vector();

    // MARK: Operators
    Vector<T>& operator=(Vector<T>&& other);
    Vector<T>& operator=(const Vector<T>& other);

    // MARK: Friend Operators
    template <class S> friend Vector<S> operator-(const Vector<S>& leftHandSide);

    template <class S> friend bool operator==(const Vector<S>& leftHandSide, const Vector<S>& rightHandSide);
    template <class S> friend bool operator!=(const Vector<S>& leftHandSide, const Vector<S>& rightHandSide);

    template <class S> friend Vector<S> operator*(const Vector<S>& leftHandSide, const Vector<S>& rightHandSide);
    template <class S> friend Vector<S> operator+(const Vector<S>& leftHandSide, const Vector<S>& rightHandSide);
    template <class S> friend Vector<S> operator-(const Vector<S>& leftHandSide, const Vector<S>& rightHandSide);

    template <class S> friend void operator*=(Vector<S>& leftHandSide, const Vector<S>& rightHandSide);
    template <class S> friend void operator+=(Vector<S>& leftHandSide, const Vector<S>& rightHandSide);
    template <class S> friend void operator-=(Vector<S>& leftHandSide, const Vector<S>& rightHandSide);

    template <class S> friend Vector<S> operator*(const S& scalar, const Vector<S>& vector);
    template <class S> friend void operator*=(Vector<S>& vector, const S& scalar);

    T& operator[](int index);
    const T& operator[](const int index) const;

    // MARK: Getters/Setters
    size_t size() const noexcept { return this -> _size; }

    T* begin() const { return this -> data.get(); }
    T* end() const { return this -> data.get() + this -> _size;  }

    template <class S> friend S* begin(const Vector<S> vector);
    template <class S> friend S* end(const Vector<S> vector);

    // MARK: Friend Functions
    template <class S> friend std::ostream& operator<<(std::ostream& os, const Vector<S>& other);
};

#include "vector.hpp"

#endif /* vector_h */

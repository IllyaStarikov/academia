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
 *  @brief A Vector class that is comprised of a column vector
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

template <typename T>
class Vector {
    std::unique_ptr<T[]> data;
    int size;

    int precision;

public:
    // MARK: Constructors
    Vector();
    Vector(const int size);
    Vector(const int size, const T& initialValue);
    Vector(const std::initializer_list<T> list);
    Vector(const Vector<T>& other);
    Vector(Vector&& other);

    // MARK: Destructor
    ~Vector();

    // MARK: Operators
    Vector<T>& operator=(Vector<T>&& other);
    Vector<T>& operator=(const Vector<T>& other);

    T& operator[](int index);
    const T& operator[](const int index) const;

    // MARK: Getters/Setters
    int magnitude() const noexcept { return this -> size; }

    // MARK: Friend Functions
    template <typename T_Friend>
    friend std::ostream& operator<<(std::ostream& os, const Vector<T_Friend>& other);
};

#include "vector.hpp"

#endif /* vector_h */


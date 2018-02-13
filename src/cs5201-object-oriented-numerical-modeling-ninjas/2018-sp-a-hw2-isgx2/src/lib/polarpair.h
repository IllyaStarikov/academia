//
//  polarpair.h
//  lib
//
//  Created by Illya Starikov on 01/31/18.
//  Copyright 2018. Illya Starikov. All rights reserved.
//

/** @class PolarPair
 *
 *  @brief A class to store Polar Coordinates and subsequent operation.
 *
 *  @tparam R The modulus type. Must be able to promoted to @p Theta or
 *          @p Theta must be able to be promoted to @p R. I.e., a `double`
 *          and a `float` would work or an `int` and a `double`, but a
 *          `char*` and an `int` would not. Must also be able to support all of the
 *          following operations:
 *  - Addition (`+`)
 *  - Subtraction (`-`)
 *  - Multiplication (`*`)
 *  - Division (`/`)
 *  - Less Than (`<`)
 *  - Greater Than (`>`)
 *  - Equal To (`==`)
 *  - Negation (`-R`)
 *
 *  @tparam Theta The argument type. Must be able to promoted to @p R or
 *          @p $ must be able to be promoted to @p Theta. I.e., a `double`
 *          and a `float` would work or an `int` and a `double`, but a
 *          `char*` and an `int` would not. Must also be able to support all of the
 *          following operations:
 *  - Addition (`+`)
 *  - Subtraction (`-`)
 *  - Multiplication (`*`)
 *  - Division (`/`)
 *  - Less Than (`<`)
 *  - Greater Than (`>`)
 *  - Equal To (`==`)
 *  - Negation (`-Theta`) */

#ifndef polarpair_h
#define polarpair_h

#include <iostream>
#include <cmath>
#include <iomanip>


const int DEFAULT_PRECISION = 8;


template <class R, class Theta>
class PolarPair {
private:
    R modulus;
    Theta argument;

    int precision;

    R modulusAbsolute() const noexcept;

public:
    // MARK: Constructors
    PolarPair();
    PolarPair(const R modulus, const Theta argument);
    PolarPair(const PolarPair<R, Theta>& other);

    // MARK: Overloaded Operators
    R operator~() const noexcept;
    PolarPair<R, Theta> operator-() const noexcept;
    PolarPair<R, Theta> operator!() const noexcept;

    Theta operator[](const int index) const;

    PolarPair<R, Theta> operator=(const PolarPair<R, Theta>& rightHandSide);
    PolarPair<R, Theta> operator*(const PolarPair<R, Theta>& rightHandSide) const noexcept;
    PolarPair<R, Theta> operator/(const PolarPair<R, Theta>& rightHandSide) const;

    bool operator>(const PolarPair<R, Theta>& rightHandSide) const noexcept;
    bool operator<(const PolarPair<R, Theta>& rightHandSide) const noexcept;
    bool operator==(const PolarPair<R, Theta>& rightHandSide) const noexcept;
    bool operator!=(const PolarPair<R, Theta>& rightHandSide) const noexcept;

    // MARK: Getters
    R getModulus() const noexcept { return modulus; }
    Theta getArgument() const noexcept { return argument; }
    int getPrecision() const noexcept { return precision; }

    // MARK: Setters
    void setModulus(const R modulus) noexcept { this -> modulus = modulus; }
    void setArgument(const Theta argument) noexcept { this -> argument = argument; }
    void setPrecision(const int precision) noexcept { this -> precision = precision; }

    // MARK: Friend Functions
    template <class R_Friend, class Theta_Friend>
    friend std::ostream& operator<<(std::ostream& os, const PolarPair<R_Friend, Theta_Friend>& object);
};

#include "polarpair.hpp"

#endif /* polarpair_h */

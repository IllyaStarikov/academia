//
//  polarpair.hpp
//  lib
//
//  Created by Illya Starikov on 01/31/18.
//  Copyright 2018. Illya Starikov. All rights reserved.
//


/** @brief Calculate the absolute value of the modulus.
 *
 *  @return The absolute value, but negated if is negative.
 *
 *  @pre None.
 *  @post See `return`. */
template<class R, class Theta>
R PolarPair<R, Theta>::modulusAbsolute() const noexcept {
    return modulus < 0 ? -modulus : modulus;
}

// MARK: Constructors
/** @brief A default contructor that'll set the polar coordinates to the
 *         origin.
 *
 *  @pre None.
 *  @post None. */
template<class R, class Theta>
PolarPair<R, Theta>::PolarPair() {
    this -> modulus = 0;
    this -> argument = 0;

    this -> precision = DEFAULT_PRECISION;
}

/** @brief A constructor that sets the Modulus and Argument accordingly.
 *
 *  @param modulus The modulus to be set within the class.
 *  @param argument The argument to be set within the class.
 *
 *  @pre None.
 *  @post None. */
template<class R, class Theta>
PolarPair<R, Theta>::PolarPair(const R modulus, const Theta argument) {
    this -> modulus = modulus;
    this -> argument = argument;

    this -> precision = DEFAULT_PRECISION;
}


/** @brief A copy constructor that copies the modulus and
 *         argument from other `PolarPair`.
 *
 *  @param other The `PolarPair` to copy the argument and
 *         precision from.
 *
 *  @pre None.
 *  @post None. */
template<class R, class Theta>
PolarPair<R, Theta>::PolarPair(const PolarPair<R, Theta>& other) {
    this -> modulus = other.getModulus();
    this -> argument = other.getArgument();

    this -> precision = other.getPrecision();
}


// MARK: Overloaded Operator
/** @brief Calculates the magnitude of the calling object.
 *
 *  @return The absolute value of the modulus.
 *
 *  @pre None.
 *  @post See `return`. */
template<class R, class Theta>
R PolarPair<R, Theta>::operator~() const noexcept {
    return modulusAbsolute();
}

/** @brief Calculates the negation of the calling object.
 *
 *  @return A polar pair who's modulus is the negation of the calling object.
 *
 *  @pre None.
 *  @post See `return`. */
template<class R, class Theta>
PolarPair<R, Theta> PolarPair<R, Theta>::operator-() const noexcept {
    return PolarPair(-modulus, argument);
}

/** @brief Calculate the conjugate of the calling object.
 *
 *  @return A polar pair who's argument is the negation of the calling object.
 *
 *  @pre None.
 *  @post See `return`. */
template<class R, class Theta>
PolarPair<R, Theta> PolarPair<R, Theta>::operator!() const noexcept {
    return PolarPair(modulus, -argument);
}

/** @brief An accessor for the modulus and argument.
 *
 *  @param The index to which parameter to returns, where
 *  - 0: modulus
 *  - 1: argument
 *
 *  @return The modulus or the argument, depending on the value of `index`.
 *
 *  @note  The value of `index` must be as follows: 0 <= index <= 1.
 *
 *  @note Because it is assumed Theta will have the higher precision, the
 *        return type is of `Theta`.
 *  @pre See `note`.
 *  @post See `return`. */
template<class R, class Theta>
Theta PolarPair<R, Theta>::operator[](const int index) const {
    if (index > 1 or index < 0) {
        throw std::out_of_range("Polar pair index out of range (0 <= x <= 1) ");
    }

    return index == 0 ? modulus : argument;
}

/** @brief Assign the calling object to a different polar pair.
 *
 *  @param rightHandSide The object from which to copy the modulus, argument,
 *         and precision from.
 *
 *  @return The calling object.
 *
 *  @pre None.
 *  @post `brief`. */
template<class R, class Theta>
PolarPair<R, Theta> PolarPair<R, Theta>::operator=(const PolarPair<R, Theta>& rightHandSide) {
    if (this != &rightHandSide) {
        this -> modulus = rightHandSide.getModulus();
        this -> argument = rightHandSide.getArgument();

        this -> precision = rightHandSide.getPrecision();
    }

    return *this;
}

/** @brief Multliply two polar pairs together and return the result.
 *
 *  @param rightHandSide The other object to multiply the calling object
 *         with to return.
 *
 *  @return A new polar pair with the modulus the product of the
 *          calling object's modulus and @p rightHandSide's modulus
 *          and the sum of the calling object's argument and
 *          the @p rightHandSide's argument.
 *
 *  @pre None.
 *  @post See `return`. */
template<class R, class Theta>
PolarPair<R, Theta> PolarPair<R, Theta>::operator*(const PolarPair<R, Theta>& rightHandSide) const noexcept {
    return PolarPair(this -> modulus * rightHandSide.getModulus(), this -> argument + rightHandSide.getArgument());
}

/** @brief Divide two polar pairs together and return the result.
 *
 *  @param rightHandSide The other object to divide the calling object
 *         with to return.
 *
 *  @return A new polar pair with the modulus the division of the
 *          calling object's modulus and @p rightHandSide's modulus
 *          and the difference of the calling object's argument and
 *          the @p rightHandSide's argument.
 *
 *  @pre None.
 *  @post See `return`. */
template<class R, class Theta>
PolarPair<R, Theta> PolarPair<R, Theta>::operator/(const PolarPair<R, Theta>& rightHandSide) const {
    if (rightHandSide.getModulus() == 0) {
        throw std::logic_error("Operator / called with 0 modulus");
    }

    return PolarPair(this -> modulus / rightHandSide.getModulus(), this -> argument - rightHandSide.getArgument());
}


/** @brief Compares the calling object to a different polar pair.
 *
 *  @param rightHandSide The object to compare with.
 *
 *  @return True if the absolute value of the modulus is greater than
 *          the @p rightHandSide's absolute value of the modulus.
 *
 *  @pre None.
 *  @post See `return`. */
template<class R, class Theta>
bool PolarPair<R, Theta>::operator>(const PolarPair<R, Theta>& rightHandSide) const noexcept {
    return this -> modulusAbsolute() > (rightHandSide.modulusAbsolute());
}

/** @brief Compares the calling object to a different polar pair.
 *
 *  @param rightHandSide The object to compare with.
 *
 *  @return True if the absolute value of the modulus is less than
 *          the @p rightHandSide's absolute value of the modulus.
 *
 *  @pre None.
 *  @post See `return`. */
template<class R, class Theta>
bool PolarPair<R, Theta>::operator<(const PolarPair<R, Theta>& rightHandSide) const noexcept {
    return this -> modulusAbsolute() < (rightHandSide.modulusAbsolute());
}

/** @brief Determine if two polar pairs are identical.
 *
 *  @param rightHandSide The polar pair to compare to.
 *
 *  @return True if the polar pairs are identical, false otherwise.
 *
 *  @note  There are several ways for polar pairs to be identical.
 *         Therefore, two polar pairs (`r`, `theta`) and (`s`, `omega`)
 *         are identical iff:
 *  - `r == s` and `theta == omega`, or
 *  - `r = -s` and `theta == omega + (2n + 1)*PI` or
 *  - `r == s` and `theta == omega + 2n*PI`
 *
 *  @pre None.
 *  @post See `return`. */
template<class R, class Theta>
bool PolarPair<R, Theta>::operator==(const PolarPair<R, Theta>& rightHandSide) const noexcept {
    const Theta pi = M_PI;
    const double EPSILON = pow(0.1, this -> precision);

    return (std::fabs(this -> getModulus() - rightHandSide.getModulus()) < EPSILON && std::fabs(this -> getArgument() - rightHandSide.getArgument()) < EPSILON) ||
    (std::fabs(this -> getModulus() - rightHandSide.getModulus()) < EPSILON && std::fabs(std::fmod(this -> getArgument(), 2.0*pi) - std::fmod(rightHandSide.getArgument(), 2.0*pi)) < EPSILON) ||
    (std::fabs(this -> getModulus() + rightHandSide.getModulus()) < EPSILON && std::fabs(std::fmod(this -> getArgument(), 2.0*pi) - std::fmod(pi + rightHandSide.getArgument(), 2.0*pi)) < EPSILON);
}

/** @brief Determine if two polar pairs are *not* identical.
 *
 *  @param rightHandSide The polar pair to compare to.
 *
 *  @return True if the polar pairs are *not* identical, false if they are.
 *
 *  @pre None.
 *  @post See `return`. */
template<class R, class Theta>
bool PolarPair<R, Theta>::operator!=(const PolarPair<R, Theta>& rightHandSide) const noexcept {
    return !(*this == rightHandSide);
}

// MARK: Friend Functions
/** @brief Insert a string description of a polar pair object into a stream.
 *
 *  @param os The stream to put a string description of the polar
 *         pair into.
 *
 *  @param object The polar pair to generate a string description from.
 *
 *  @return The stream with the string description of the @p object in it.
 *
 *  @pre None.
 *  @post See `return. */
template<class R, class Theta>
std::ostream& operator<<(std::ostream& os, const PolarPair<R, Theta>& object) {
    os << "(" << std::setprecision(object.precision) << std::fixed << object.getModulus() << ", " << object.getArgument() << ")";

    return os;
}


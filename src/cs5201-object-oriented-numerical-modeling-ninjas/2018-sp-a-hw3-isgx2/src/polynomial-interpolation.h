//
//  polynomial-interpolation.h
//  src
//
//  Illya Starikov, Section 1A, 18083141
//  cs5201 – Object Oriented Numerical Modeling
//

#ifndef polynomial_interpolation_h
#define polynomial_interpolation_h

#include <utility>
#include <vector>
#include <map>
#include <functional>

#include "lib/lower-triangular-matrix.h"
#include "exceptions/interpolation-exception.h"
#include "lib/vector.h"

/** @class PolynomialInterpolation
 *
 *  @brief A functor that calculates Polynomial Interpolations and their
 *         associated properties.
 *
 *  @tparam T must have the following operations defined:
 *  - Addition (`+`)
 *  - Subtraction (`-`)
 *  - Multiplication (`*`)
 *  - Division (`/`)
 *  - Equal To (`==`)
 *  - Negation (`-T`)
 **/


template <class T>
class PolynomialInterpolation {
private:
    using InterpolationFunction = std::function<T(T x)>;

    std::vector<std::pair<T, T>> points;
    std::unique_ptr<LowerTriangularMatrix<T>> dividedDifferenceTable;
    std::unique_ptr<InterpolationFunction> newtonInterpolation;

    void calculateDividedDifferenceTable();
    void calculateNewtonInterpolation();
    void checkIfPointsAreValid();

public:
    // MARK: Constructors
    PolynomialInterpolation(const std::vector<std::pair<T, T>>& points);
    PolynomialInterpolation<T>& operator=(const PolynomialInterpolation<T>& other);
    PolynomialInterpolation<T>& operator=(const PolynomialInterpolation<T>&& other);
    T operator()(const T x);

    // MARK: Interpolation Schtuff
    T absoluteError(const T x, const T actual);
    T relativeError(const T x, const T actual);

    // Mark Getters/Setters
    Vector<T> coefficients();
    std::function<T(T x)> function();
    std::vector<std::pair<T, T>> dataPoints();

    // MARK: Deleted Functions
    PolynomialInterpolation() = delete;
    PolynomialInterpolation(const PolynomialInterpolation& other) = delete;
    PolynomialInterpolation(const PolynomialInterpolation&& other) = delete;
};

#include "polynomial-interpolation.hpp"

#endif /* polynomial_interpolation_h */


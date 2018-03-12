//
//  polynomial-interpolation.hpp
//  src
//
//  Illya Starikov, Section 1A, 18083141
//  cs5201 – Object Oriented Numerical Modeling
//

#ifndef polynomial_interpolation_hpp
#define polynomial_interpolation_hpp

/**
 *  @brief  Explicit constructor.
 *
 *  @param  points A `std::vector` of `std::pair`s of points
 *          where the first value (`point.first`) corresponds to the `x` values
 *          and the second value (`point.second`) corresponds to the `y` values.
 *
 *  @warning If the points are not valid, the function will throw. The `points`
 *           are not valid if:
 *           - There are no points.
 *           - There are two `x` values (even if the correspond `y` values
 *           are the same.
 *
 *  @pre    See `warning`.
 *  @post   See `brief`.
 **/
template <typename T>
PolynomialInterpolation<T>::PolynomialInterpolation(const std::vector<std::pair<T, T>>& points) {
    this -> dividedDifferenceTable = nullptr;
    this -> newtonInterpolation = nullptr;
    this -> points = points;

    checkIfPointsAreValid();
}

/**
 *  @brief  Assignment operator that returns an PolynomialInterpolation object.
 *
 *  @param  other Another polynomial interpolation.
 *
 *  @pre    None.
 *  @post   See `brief`.
 **/
template <typename T>
PolynomialInterpolation<T>& PolynomialInterpolation<T>::operator=(const PolynomialInterpolation<T>& other) {
    if (this != &other) {
        this -> dividedDifferenceTable = nullptr;
        this -> newtonInterpolation = nullptr;
        this -> points = other.points;

        checkIfPointsAreValid();
    }

    return *this;
}

/**
 *  @brief  Move assignment operator that returns an PolynomialInterpolation object.
 *
 *  @param  other Another polynomial interpolation.
 *
 *  @pre    None.
 *  @post   See `brief`.
 **/
template <typename T>
PolynomialInterpolation<T>& PolynomialInterpolation<T>::operator=(const PolynomialInterpolation<T>&& other) {
    if (this != &other) {
        this -> dividedDifferenceTable = nullptr;
        this -> newtonInterpolation = nullptr;
        this -> points = std::move(other.points);

        checkIfPointsAreValid();
    }

    return *this;
}

/**
 *  @brief  Calculates the difference table and sets `this -> dividedDifferenceTable`
 *          to the difference table.
 *
 *  @pre    None.
 *  @post   See `brief`.
 **/
template <typename T>
void PolynomialInterpolation<T>::calculateDividedDifferenceTable() {
    if (this -> dividedDifferenceTable != nullptr) {
        return;
    }

    auto size = static_cast<int>(points.size()) - 1;
    dividedDifferenceTable = std::make_unique<LowerTriangularMatrix<T>>(LowerTriangularMatrix<T>(size));

    T x_1, x_2, y_1, y_2;

    for (int row = 0; row < size; row++) {
        for (int column = 0; column <= row; column++) {
            if (column == 0) {
                x_1 = points[row].first;
                x_2 = points[row + 1].first;

                y_1 = points[row].second;
                y_2 = points[row + 1].second;
            } else {
                y_1 = (*dividedDifferenceTable)[row - 1][column - 1];
                y_2 = (*dividedDifferenceTable)[row][column - 1];

                x_1 = points[row - column].first;
                x_2 = points[row + 1].first;
            }

            (*dividedDifferenceTable)[row][column] = (y_2 - y_1) / (x_2 - x_1);
        }
    }
}

/**
 *  @brief  Calculates the Newton Interpolation and sets
 *          `this -> dividedDifferenceTable` to the interpolation.
 *
 *  @pre   None.
 *  @post  See `brief`.
 **/
template <typename T>
void PolynomialInterpolation<T>::calculateNewtonInterpolation() {
    if (newtonInterpolation != nullptr) {
        return;
    }

    auto lambda = [&](const T x) {
        calculateDividedDifferenceTable();

        auto mainDiagonal = (*dividedDifferenceTable).mainDiagonal();
        auto total = points[0].second;

        for (int i = 0; i < (*dividedDifferenceTable).magnitude(); i++) {
            auto accumulator = mainDiagonal[i];

            for (int j = 0; j <= i; j++) {
                accumulator *= x - points[j].first;
            }

            total += accumulator;
        }

        return total;
    };

    newtonInterpolation = std::make_unique<InterpolationFunction<T>>(InterpolationFunction<T>(lambda));
}

/**
 *  @brief  Checks to see if `this -> points` is valid. It does so by
 *          by checking the following:
 *          - If there is data in the dataset.
 *          - If there are two `x` values inside the dataset.
 *
 * @warning If the dataset *is not* valid, an `ImproperDatset` exception will
 *          be thrown.
 * @throws  ImproperDataset If the number of points are less than 1 or if an 
 *          an x value appears twice.
 *
 *  @pre   None.
 *  @post  See `warning`.
 **/
template <typename T>
void PolynomialInterpolation<T>::checkIfPointsAreValid() {
    auto allPoints = std::map<T, T>();

    if (points.size() < 1) {
        throw ImproperDataset("Data contains no points");
    }

    for (const auto& point : points) {
        if (allPoints.find(point.first) != allPoints.end()) {
            throw ImproperDataset("Data contains an x value twice");
        }

        allPoints[point.first] = point.second;
    }
}

/**
 *  @brief  Calculate the Newton Interpolation at a value @p x.
 *
 *  @param  x Where to calculate the interpolation value at.
 *
 *  @return The Newton Interpolation at the value @p x.
 *
 *  @pre    None.
 *  @post   See `return`.
 **/
template <typename T>
T PolynomialInterpolation<T>::operator()(const T x) {
    calculateNewtonInterpolation();
    return (*newtonInterpolation)(x);
}

/**
 *  @brief  Calculates the absolute error at a particular value.
 *
 *  @param  x The point (x_0) where to calculate the absolute error.
 *  @param  actual The true value (x) at x.
 *
 *  @return The absolute error at @p x.
 *
 *  @pre   None.
 *  @post  See `return`.
 **/
template <typename T>
T PolynomialInterpolation<T>::absoluteError(const T x, const T actual) {
    calculateNewtonInterpolation();
    return (actual - (*newtonInterpolation)(x));
}

/**
 *  @brief  Calculates the relative error at a particular value.
 *
 *  @param  x The point (x_0) where to calculate the relative error.
 *  @param  actual The true value (x) at x.
 *
 *  @return The relative error at @p x.
 *
 *  @pre   None.
 *  @post  See `return`.
 **/
template <typename T>
T PolynomialInterpolation<T>::relativeError(const T x, const T actual) {
    // If the actual value is zero, then there would division by zero.
    // And it'd be terrible to not calculate a difference because division by zero.
    // So we take an arbitrarily small delta.
    const T delta = 1;
    T shift = actual == 0 ? delta : 0;

    return static_cast<T>(100.0) * absoluteError(x, actual) / (actual + shift);
}

/**
 *  @brief  Generate and return a coefficient vector.
 *
 *  @return The coefficient vector.
 *
 * @pre None.
 * @post See `return`.
 */
template <typename T>
Vector<T> PolynomialInterpolation<T>::coefficients() {
    calculateDividedDifferenceTable();

    auto size = (*dividedDifferenceTable).magnitude() + 1;
    auto diagonal = (*dividedDifferenceTable).mainDiagonal();
    auto newtonCoefficients = Vector<T>(size);

    newtonCoefficients[0] = points[0].second;

    for (int i = 0; i < size - 1; i++) {
        newtonCoefficients[i + 1] = diagonal[i];
    }

    auto centers = Vector<T>(size);
    for (int i = 0; i < size; i++) {
        centers[i] = points[i].first;
    }

    return newtonFormToPowerForm(newtonCoefficients, centers);
}


/**
 *  @brief Transform the newton coefficients (i.e., a + b(x - x_0)(x - x_1) + c(x - x_0)(x - x_1)(x - x_2))
 *         into the power coefficients (a + bx + cx^2).
 *
 *  @param coefficients The coefficient of the newton form.
 *
 *  @param centers The `x` values from the data set.
 *
 *  @return A vector of the power coefficients.
 *
 *  @pre None.
 *  @post See `return`.
 **/
template <typename T>
Vector<T> PolynomialInterpolation<T>::newtonFormToPowerForm(Vector<T> coefficients, Vector<T> centers) {
    auto coefficientSize = coefficients.magnitude() - 1;

    for (int i = 0; i < centers.magnitude(); i++) {
        for (int j = coefficientSize - 1; j >= 0; j--) {
            coefficients[j] = coefficients[j] - coefficients[j + 1] * centers[j];
        }

        for (int j = centers.magnitude() - 1; j > 0 ; j--) {
            centers[j] = centers[j - 1];
        }

        centers[0] = 0;
    }

    return coefficients;
}

/**
 *   @brief  Generate a lambda function to represent the interpolation.
 *
 *   @return A lambda function that takes in an `x` value and returns
 *           the interpolation at `x`.
 *
 *   @pre None.
 *   @post See `return`.
 **/
template <typename T>
InterpolationFunction<T> PolynomialInterpolation<T>::function() {
    calculateNewtonInterpolation();
    return (*newtonInterpolation);
}


/**
 *   @brief  A getter for the points of the interpolation.
 *
 *   @return An `std::vector` of `std::pair`s of the form (x, y).
 *
 *   @pre None.
 *   @post See `return`.
 **/
template <typename T>
std::vector<std::pair<T, T>> PolynomialInterpolation<T>::dataPoints() {
    return points;
}

/**
 *  @brief Insert a string description of a Polynomial Interpolation into a stream.
 *
 *  @param os The stream to put a string description of the Polynomial Interpolation into.
 *
 *  @param object The Polynomial Interpolation to generate a string description from.
 *
 *  @return The stream with the string description of the @p object in it.
 *
 *  @pre None.
 *  @post See `return`.
 **/
template<typename S>
std::ostream& operator<<(std::ostream& os, const PolynomialInterpolation<S>& object) {
    (void)object; // prevent unused parameter warning by doing something random with the object
    os << "PolynomialInterpolation(x)";

    return os;
}

#endif /* polynomial_interpolation_hpp */

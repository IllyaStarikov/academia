//
//  main.cpp
//  cs5201 - Numerical Modeling
//
//  Illya Starikov, Section 1A, 18083141
//  cs5201 – Object Oriented Numerical Modeling
//

#include <iostream>
#include <iomanip>
#include <typeinfo>
#include <cmath>

#include "functions.h"
#include "lib/lower-triangular-matrix.h"
#include "polynomial-interpolation.h"

const auto start = 0.0;
const auto stop = 1.0;
const auto increment = 0.1;

const auto precision = 8;

int main(int argc, const char *argv[]) {
    ensureEnoughArguments(argc);

    const auto function = [](const double x) { return 1 / (1 + 12 * x*x); };

    auto filename = argv[1];
    auto fileContents = readInputFile(filename);

    auto points = parseFileContents(fileContents);
    auto interpolation = PolynomialInterpolation(points);
    auto coefficients = interpolation.coefficients();

    std::cout << std::fixed << std::setprecision(precision) << "# Data Points\n";
    for (const auto& point : points) {
        std::cout << point.first << " " << point.second << "\n";
    }

    std::cout << "\n# Coefficients\n";
    for (int i = 0; i < coefficients.magnitude(); i++) {
        std::cout << coefficients[i] << "\n";
    }

    std::cout << "\n# Interpolation Values\n";
    for (auto i = start; i < stop; i += increment) {
        std::cout << i << ": " << interpolation(i) << "\n";
    }

    std::cout << "\n# Function Values\n";
    for (auto i = start; i < stop; i += increment) {
        std::cout << i << ": " << function(i) << "\n";
    }

    std::cout << "\n# Absolute Error\n";
    for (auto i = start; i < stop; i += increment) {
        std::cout << i << ": " << fabs(interpolation.absoluteError(i, function(i))) << "\n";
    }

    std::cout << "\n# Relative Error\n";
    for (auto i = start; i < stop; i += increment) {
        std::cout << i << ": " << fabs(interpolation.relativeError(i, function(i))) << "\n";
    }
}

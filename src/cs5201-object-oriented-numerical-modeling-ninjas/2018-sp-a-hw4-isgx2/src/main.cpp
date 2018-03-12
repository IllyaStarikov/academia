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
#include "chebyshev-node-generator.h"

const auto start = 0.1;
const auto stop = 0.9;
const auto increment = 0.2;

const auto precision = 8;

int main(int argc, const char *argv[]) {
    ensureEnoughArguments(argc);

    const auto function = [](const double x) { return 1 / (1 + 12 * x*x); };

    int numberOfPoints;
    std::string filename;

    try {
        numberOfPoints = stringToInt(argv[1]);
        filename = argv[2];
    } catch (...) {
        displayErrorAndQuit("usage: ./driver number-of-points filepath-to-points");
    }

    std::string fileContents;
    std::vector<std::pair<double, double>> equallySpacedPoints;

    try {
        fileContents = readInputFile(filename);
        equallySpacedPoints = parseFileContents(fileContents);

        if (numberOfPoints < 1) {
            throw ImproperDataset("Not enough data points.");
        }
    } catch(const std::logic_error error) {
        std::cerr << "Data is not in proper format. Terminating.\n";
        return -1;
    } catch (const ImproperDataset error) {
        std::cerr << "Not enough data points.\n";
        return -1;
    }

    try {
        auto chebyshevNodeGenerator = ChebyshevNodeGenerator<double>();
        auto points = chebyshevNodeGenerator(numberOfPoints, function);
        auto interpolation = PolynomialInterpolation(points), equallySpacedInterpolation = PolynomialInterpolation(equallySpacedPoints);
        auto coefficients = interpolation.coefficients();

        std::cout << std::fixed << std::setprecision(precision) << "# 1. Data Points\n";
        for (const auto& point : points) {
            std::cout << point.first << " " << point.second << "\n";
        }

        std::cout << "\n# 2. Coefficients\n";
        for (int i = 0; i < coefficients.magnitude(); i++) {
            std::cout << coefficients[i] << "\n";
        }

        std::cout << "\n# 3. Interpolation Values\n";
        for (auto i = start; i < stop; i += increment) {
            std::cout << i << ": " << interpolation(i) << "\n";
        }

        std::cout << "\n# 4. Function Values\n";
        for (auto i = start; i < stop; i += increment) {
            std::cout << i << ": " << function(i) << "\n";
        }

        std::cout << "\n# 5. Absolute Error\n";
        for (auto i = start; i < stop; i += increment) {
            std::cout << i << ": " << fabs(interpolation.absoluteError(i, function(i))) << "\n";
        }

        std::cout << "\n# 6. Relative Error\n";
        for (auto i = start; i < stop; i += increment) {
            std::cout << i << ": " << fabs(interpolation.relativeError(i, function(i))) << "\n";
        }

        std::cout << "\n# 7. Equally-Chebyshev Relative Error\n";
        for (auto i = start; i < stop; i += increment) {
            std::cout << i << ": " << fabs(interpolation.relativeError(i, equallySpacedInterpolation(i))) << "\n";
        }
    } catch (const ImproperDataset error) {
        //displayErrorAndQuit("Improper Dataset");
        displayErrorAndQuit(error.what());
    } catch (...) {
        displayErrorAndQuit("Something *really* went wrong");
    }

}

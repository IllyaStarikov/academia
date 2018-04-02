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
#include "gaussian-solver.h"

int main(int argc, const char *argv[]) {
    ensureEnoughArguments(argc);

    auto filename = argv[1];

    auto solver = LinearSystemSolver<double>();

    auto A = SquareMatrix<double>();
    auto b = Vector<double>();

    try {
        auto fileContents = readInputFile(filename);
        auto matrixVector = parseFileContents(fileContents);

        A = matrixVector.first;
        b = matrixVector.second;

        if (A.rows() != b.size()) {
            throw MistmatchedDimensionsError();
        }
    } catch(...) {
        std::cerr << "Data is not in proper format. Terminating.\n";
        return -1;
    }

    try {
        auto x = solver(A, b);

        std::cout << A * transpose(A) << "\n";
        std::cout << x << "\n";
        std::cout << A * x << "\n";
    } catch ( SingularMatrixError) {
        std::cout << "System is either inconsistent or has infinitely many solutions.\n";
    }

}

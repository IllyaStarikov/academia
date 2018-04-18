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
#include "steepest-descent-solver.h"
#include "./exceptions/steepest-descent-exception.h"

#include "../lib/eigen.h"

using T = double;

int main(int argc, const char *argv[]) {
    ensureEnoughArguments(argc);

    auto filename = argv[1];

    auto A = SymmetricMatrix<T>();
    auto b = Vector<T>();

    auto solver = SteepestDescentSolver<T>();

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
        auto solution = solver(A, b);
        std::cout << solution;
    } catch (NonDiagonallyDominantMatrixError) {
        std::cout << "Non diagonally dominant matrix. Terminating.\n";
    }
}

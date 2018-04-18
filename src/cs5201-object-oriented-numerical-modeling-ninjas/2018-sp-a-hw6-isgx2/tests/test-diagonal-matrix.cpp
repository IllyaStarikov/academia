//
//  test-diagonal-matrix.cpp
//  tests
//
//  Created by Illya Starikov on 04/15/18.
//  Copyright 2018. Illya Starikov. All rights reserved.
//

#include "catch.hpp"

#include "../lib/eigen.h"

TEST_CASE("Diagonal Matrix Tester", "[DiagonalMatrix]") {
    using T = double;


    SECTION("Default Constructor") {
        DiagonalMatrix<T> defaultMatrix;
    }

    SECTION("Regular Constructor") {
        DiagonalMatrix<T> matrix = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
        DiagonalMatrix<T> expected = {{1, 0, 0}, {0, 5, 0}, {0, 0, 9}};

        REQUIRE(matrix == expected);
    }

    SECTION("Move Operator =") {
        DiagonalMatrix<T> oneRows = {{1}};
        DiagonalMatrix<T> twoRows = {{1, 2}, {3, 4}};
        DiagonalMatrix<T> threeRows = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};

        DiagonalMatrix<T> oneRowsClone = {{1}};
        DiagonalMatrix<T> twoRowsClone = {{1, 2}, {3, 4}};
        DiagonalMatrix<T> threeRowsClone = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};

        DiagonalMatrix<T> assigned;

        assigned = std::move(oneRowsClone);
        REQUIRE(assigned == oneRows);

        assigned = std::move(threeRowsClone);
        REQUIRE(assigned == threeRows);

        assigned = std::move(twoRowsClone);
        REQUIRE(assigned == twoRows);
    }

    SECTION("Operator =") {
        DiagonalMatrix<T> oneRows = {{1}};
        DiagonalMatrix<T> twoRows = {{1, 2}, {3, 4}};
        DiagonalMatrix<T> threeRows = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};

        DiagonalMatrix<T> assigned;

        assigned = oneRows;
        REQUIRE(assigned == oneRows);
        REQUIRE(assigned != twoRows);
        REQUIRE(assigned != threeRows);

        assigned = threeRows;
        REQUIRE(assigned != oneRows);
        REQUIRE(assigned != twoRows);
        REQUIRE(assigned == threeRows);

        assigned = twoRows;
        REQUIRE(assigned != oneRows);
        REQUIRE(assigned == twoRows);
        REQUIRE(assigned != threeRows);
    }

    SECTION("Matrix/Vector/Scalar Operator */ *=") {
        DiagonalMatrix<T> improperMatrix = {{1, 2}, {3, 4}};

        T scalar = 2;
        Vector<T> vector = {{1, 2, 3}};

        DiagonalMatrix<T> matrix1 = {{1, 0, 0}, {0, 2, 0}, {0, 0, 3}};
        DiagonalMatrix<T> matrix2 = {{4, 0, 0, 0}, {0, 5, 0, 0} ,{0, 0, 6, 0}};

        DiagonalMatrix<T> expectedDiagonalMatrix = {{4, 0, 0, 0}, {0, 10, 0, 0}, {0, 0, 18, 0}};
        DiagonalMatrix<T> expectedScalarMatrix = {{2, 0, 0}, {0, 4, 0}, {0, 0, 6}};
        Vector<T> expectedVector = {{1}, {4}, {9}};

        REQUIRE_THROWS(improperMatrix * matrix1);

        REQUIRE(expectedDiagonalMatrix == matrix1 * matrix2);
        REQUIRE(expectedScalarMatrix == scalar * matrix1);
        REQUIRE(expectedVector == matrix1 * vector);

        matrix1 *= matrix2;
        REQUIRE(expectedDiagonalMatrix == matrix1);
    }

    SECTION("Operator +") {
        DiagonalMatrix<T> improperMatrix = {{1, 2}, {3, 4}};

        DiagonalMatrix<T> matrix1 = {{1, 0, 0}, {0, 2, 0}, {0, 0, 3}};
        DiagonalMatrix<T> matrix2 = {{4, 0, 0}, {0, 5, 0} ,{0, 0, 6}};
        DiagonalMatrix<T> expected = {{5, 0, 0}, {0, 7, 0}, {0, 0, 9}};

        REQUIRE_THROWS(improperMatrix + matrix1);
        REQUIRE(expected == matrix1 + matrix2);

        matrix1 += matrix2;
        REQUIRE(expected == matrix1);
    }

    SECTION("Operator -") {
        DiagonalMatrix<T> improperMatrix = {{1, 2}, {3, 4}};

        DiagonalMatrix<T> matrix1 = {{4, 0, 0}, {0, 5, 0} ,{0, 0, 6}};
        DiagonalMatrix<T> matrix2 = {{1, 0, 0}, {0, 2, 0}, {0, 0, 3}};
        DiagonalMatrix<T> expected = {{3, 0, 0}, {0, 3, 0}, {0, 0, 3}};

        REQUIRE_THROWS(improperMatrix - matrix1);
        REQUIRE(expected == matrix1 - matrix2);

        matrix1 -= matrix2;
        REQUIRE(expected == matrix1);
    }

    SECTION("Negation Operator -") {
        DiagonalMatrix<T> matrix =  {{1, 0, 0, 0}, {0, 2, 0, 0}, {0, 0, 3, 0}};
        DiagonalMatrix<T> expected = {{-1, 0, 0, 0}, {0, -2, 0, 0}, {0, 0, -3, 0}};

        REQUIRE(expected == -matrix);
    }

    SECTION("Transpose Operator") {
        DiagonalMatrix<T> matrix =  {{1, 0, 0, 0}, {0, 2, 0, 0}, {0, 0, 3, 0}};
        DiagonalMatrix<T> expected = {{1, 0, 0}, {0, 2, 0}, {0, 0, 3}, {0, 0, 0}};

        REQUIRE(expected == transpose(matrix));
    }

    SECTION("<<") {
        DiagonalMatrix<T> matrix = {{1, 0, 0}, {0, 5, 0}, {0, 0, 9}};
        std::cout << "Diagonal Matrix << Operator\n";
        std::cout << matrix << "\n";
    }
}

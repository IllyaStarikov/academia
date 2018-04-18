//
//  test-rectangular-matrix.cpp
//  tests
//
//  Created by Illya Starikov on 03/27/18.
//  Copyright 2018. Illya Starikov. All rights reserved.
//

#include "catch.hpp"

#include "../lib/eigen.h"

TEST_CASE("Rectangular Matrix Tester", "[RectangularMatrix]") {
    using T = double;

    SECTION("Default Constructor") {
        RectangularMatrix<T> defaultMatrix;
    }

    SECTION("Move Operator =") {
        RectangularMatrix<T> oneRows = {{1}};
        RectangularMatrix<T> twoRows = {{1, 2}, {3, 4}};
        RectangularMatrix<T> threeRows = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};

        RectangularMatrix<T> oneRowsClone = {{1}};
        RectangularMatrix<T> twoRowsClone = {{1, 2}, {3, 4}};
        RectangularMatrix<T> threeRowsClone = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};

        RectangularMatrix<T> assigned;

        assigned = std::move(oneRowsClone);
        REQUIRE(assigned == oneRows);

        assigned = std::move(threeRowsClone);
        REQUIRE(assigned == threeRows);

        assigned = std::move(twoRowsClone);
        REQUIRE(assigned == twoRows);
    }

    SECTION("Operator =") {
        RectangularMatrix<T> oneRows = {{1}};
        RectangularMatrix<T> twoRows = {{1, 2}, {3, 4}};
        RectangularMatrix<T> threeRows = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};

        RectangularMatrix<T> assigned;

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

    SECTION("Matrix/Vector/Scalar Operator */*=") {
        RectangularMatrix<T> improperMatrix = {{1, 2}, {3, 4}};

        T scalar = 2;
        Vector<T> vector = {{1, 2, 3}};

        RectangularMatrix<T> matrix1 = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {10, 11, 12}};
        RectangularMatrix<T> matrix2 = {{13, 14, 15, 16}, {17, 18, 19, 20}, {21, 22, 23, 24}};

        RectangularMatrix<T> expectedRectangularMatrix = {{110, 116, 122, 128}, {263, 278, 293, 308}, {416, 440, 464, 488}, {569, 602, 635, 668}};
        RectangularMatrix<T> expectedScalarMatrix = {{2, 4, 6}, {8, 10, 12}, {14, 16, 18}, {20, 22, 24}};
        Vector<T> expectedVector = {{14}, {32}, {50}, {68}};

        REQUIRE_THROWS(improperMatrix * matrix1);

        REQUIRE(expectedRectangularMatrix == matrix1 * matrix2);
        REQUIRE(expectedScalarMatrix == scalar * matrix1);
        REQUIRE(expectedVector == matrix1 * vector);

        matrix1 *= matrix2;
        REQUIRE(expectedRectangularMatrix == matrix1);
    }

    SECTION("Operator +") {
        RectangularMatrix<T> improperMatrix = {{1, 2}, {3, 4}};

        RectangularMatrix<T> matrix1 = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {10, 11, 12}};
        RectangularMatrix<T> matrix2 = {{13, 14, 15}, {16, 17, 18}, {19, 20, 21}, {22, 23, 24}};
        RectangularMatrix<T> expected = {{14, 16, 18}, {20, 22, 24}, {26, 28, 30}, {32, 34, 36}};

        REQUIRE_THROWS(improperMatrix + matrix1);
        REQUIRE(expected == matrix1 + matrix2);

        matrix1 += matrix2;
        REQUIRE(expected == matrix1);
    }

    SECTION("Operator -") {
        RectangularMatrix<T> improperMatrix = {{1, 2}, {3, 4}};
        RectangularMatrix<T> matrix1 = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {10, 11, 12}};
        RectangularMatrix<T> matrix2 = {{13, 14, 15}, {16, 17, 18}, {19, 20, 21}, {22, 23, 24}};
        RectangularMatrix<T> expected = {{-12, -12, -12}, {-12, -12, -12}, {-12, -12, -12}, {-12, -12, -12}};

        REQUIRE_THROWS(improperMatrix - matrix1);
        REQUIRE(expected == matrix1 - matrix2);

        matrix1 -= matrix2;
        REQUIRE(expected == matrix1);
    }

    SECTION("Negation Operator -") {
        RectangularMatrix<T> matrix = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {10, 11, 12}};
        RectangularMatrix<T> expected = {{-1, -2, -3}, {-4, -5, -6}, {-7, -8, -9}, {-10, -11, -12}};

        REQUIRE(expected == -matrix);
    }

    SECTION("Transpose Operator") {
        RectangularMatrix<T> matrix = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {10, 11, 12}};
        RectangularMatrix<T> expected =  {{1, 4, 7, 10}, {2, 5, 8, 11}, {3, 6, 9, 12}};

        REQUIRE(expected == transpose(matrix));
    }


    SECTION("<<") {
        RectangularMatrix<T> matrix = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
        std::cout << "Matrix << Operator\n";
        std::cout << matrix << "\n";
    }
}


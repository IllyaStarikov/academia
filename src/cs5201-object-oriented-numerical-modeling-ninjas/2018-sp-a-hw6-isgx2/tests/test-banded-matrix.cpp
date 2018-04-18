//
//  test-banded-matrix.cpp
//  tests
//
//  Created by Illya Starikov on 04/15/18.
//  Copyright 2018. Illya Starikov. All rights reserved.
//

#include "catch.hpp"

#include "../lib/eigen.h"

TEST_CASE("Banded Matrix Tester", "[BandedMatrix]") {
    using T = float;

    SECTION("Default Constructor") {
        BandedMatrix<T> defaultMatrix;
    }

    SECTION("Regular Constructor") {
        BandedMatrix<T> matrix = {{1, 2, 3, 4, 5}, {6, 7, 8, 9, 10}, {11, 12, 13, 14, 15}, {16, 17, 18, 19, 20}, {21, 22, 23, 24, 25}};
        BandedMatrix<T> expected = {{1, 2, 0, 0, 0}, {6, 7, 8, 0, 0}, {0, 12, 13, 14, 0}, {0, 0, 18, 19, 20}, {0, 0, 0, 24, 25}};

        REQUIRE(matrix == expected);
    }

    SECTION("Move Operator =") {
        BandedMatrix<T> matrix = {{1, 2, 0}, {0, 5, 6}, {0, 0, 9}};
        BandedMatrix<T> matrixClone = {{1, 2, 0}, {0, 5, 6}, {0, 0, 9}};
        BandedMatrix<T> assigned;

        assigned = std::move(matrix);
        REQUIRE(assigned == matrixClone);

    }

    SECTION("Operator =") {
        BandedMatrix<T> matrix1 = {{1, 2, 0, 0, 0}, {6, 7, 8, 0, 0}, {0, 12, 13, 14, 9}, {0, 0, 18, 19, 20}, {0, 0, 0, 24, 25}};
        BandedMatrix<T> matrix2 = {{1, 2, 0}, {0, 5, 6}, {0, 0, 9}};
        BandedMatrix<T> assigned;

        assigned = matrix1;
        REQUIRE(assigned == matrix1);
        REQUIRE(assigned != matrix2);

        assigned = matrix2;
        REQUIRE(assigned != matrix1);
        REQUIRE(assigned == matrix2);
    }

    SECTION("Matrix/Vector/Scalar Operator */ *=") {
        BandedMatrix<T> improperMatrix = {{1, 2, 0, 0, 0}, {6, 7, 8, 0, 0}, {0, 12, 13, 14, 0}, {0, 0, 18, 19, 20}, {0, 0, 0, 24, 25}};

        T scalar = 2;
        Vector<T> vector = {{1, 2, 3}};

        BandedMatrix<T> matrix1 = {{1, 2, 0}, {0, 5, 6}, {0, 0, 9}};
        BandedMatrix<T> matrix2 =  {{1, 2, 0, 0}, {3, 4, 5, 0}, {0, 6, 7, 8}};

        RectangularMatrix<T> expectedMatrix = {{7, 10, 10, 0}, {15, 56, 67, 48}, {0, 54, 63, 72}};

        BandedMatrix<T> expectedScalarMatrix = {{2, 4, 0}, {0, 10, 12}, {0, 0, 18}};
        Vector<T> expectedVector = {{5}, {28}, {27}};

        REQUIRE_THROWS(improperMatrix * matrix1);

        REQUIRE(expectedMatrix == matrix1 * matrix2);
        REQUIRE(expectedScalarMatrix == scalar * matrix1);
        REQUIRE(expectedVector == matrix1 * vector);
    }

    SECTION("Operator +") {
        BandedMatrix<T> improperMatrix = {{1, 2, 0, 0, 0}, {6, 7, 8, 0, 0}, {0, 12, 13, 14, 0}, {0, 0, 18, 19, 20}, {0, 0, 0, 24, 25}};

        BandedMatrix<T> matrix1 = {{1, 2, 0}, {0, 5, 6}, {0, 0, 9}};
        BandedMatrix<T> matrix2 = {{10, 11, 0}, {0, 14, 15} ,{0, 0, 18}};
        BandedMatrix<T> expected = {{11, 13, 0}, {0, 19, 21}, {0, 0, 27}};

        REQUIRE_THROWS(improperMatrix + matrix1);
        REQUIRE(expected == matrix1 + matrix2);

        matrix1 += matrix2;
        REQUIRE(expected == matrix1);
    }

    SECTION("Operator -") {
        BandedMatrix<T> improperMatrix = {{1, 2, 0, 0, 0}, {6, 7, 8, 0, 0}, {0, 12, 13, 14, 0}, {0, 0, 18, 19, 20}, {0, 0, 0, 24, 25}};

        BandedMatrix<T> matrix1 = {{10, 11, 0}, {0, 14, 15} ,{0, 0, 18}};
        BandedMatrix<T> matrix2 = {{1, 2, 0}, {0, 5, 6}, {0, 0, 9}};
        BandedMatrix<T> expected = {{9, 9, 0}, {0, 9, 9}, {0, 0, 9}};

        REQUIRE_THROWS(improperMatrix - matrix1);
        REQUIRE(expected == matrix1 - matrix2);

        matrix1 -= matrix2;
        REQUIRE(expected == matrix1);
    }

    SECTION("Negation Operator -") {
        BandedMatrix<T> matrix = {{1, 2, 0, 0, 0}, {6, 7, 8, 0, 0}, {0, 12, 13, 14, 15}, {0, 0, 18, 19, 20}, {0, 0, 0, 24, 25}};
        BandedMatrix<T> expected = {{-1, -2, 0, 0, 0}, {-6, -7, -8, 0, 0}, {0, -12, -13, -14, -15}, {0, 0, -18, -19, -20}, {0, 0, 0, -24, -25}};

        REQUIRE(expected == -matrix);
    }


    SECTION("Transpose Operator") {
        BandedMatrix<T> matrix = {{1, 2, 0, 0, 0}, {6, 7, 8, 0, 0}, {0, 12, 13, 14, 9}, {0, 0, 18, 19, 20}, {0, 0, 0, 24, 25}};
        BandedMatrix<T> expected = {{1, 6, 0, 0, 0}, {2, 7, 12, 0, 0}, {0, 8, 13, 18, 0}, {0, 0, 14, 19, 24}, {0, 0, 9, 20, 25}};

        REQUIRE(expected == transpose(matrix));
    }


    SECTION("<<") {
        BandedMatrix<T> matrix = {{1, 2, 3, 4, 5}, {6, 7, 8, 9, 10}, {11, 12, 13,14, 15}, {16, 17, 18, 19, 20}, {21, 22, 23, 24, 25}};
        std::cout << "Banded Matrix << Operator\n";
        std::cout << matrix << "\n";
    }
}


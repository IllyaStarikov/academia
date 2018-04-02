//
//  test-rectangular-matrix.cpp
//  tests
//
//  Created by Illya Starikov on 03/27/18.
//  Copyright 2018. Illya Starikov. All rights reserved.
//


#include "catch.hpp"

#include "../src/lib/vector.h"
#include "../src/lib/square-matrix.h"

TEST_CASE("Square Matrix Tester", "[SquareMatrix]") {
    using T = int;

    SECTION("Move Operator =") {
        SquareMatrix<T> oneRows = { {1} };
        SquareMatrix<T> twoRows = { {1, 2}, {3, 4} };
        SquareMatrix<T> threeRows = { {1, 2, 3}, {4, 5, 6}, {7, 8, 9} };

        SquareMatrix<T> oneRowsClone = { {1} };
        SquareMatrix<T> twoRowsClone = { {1, 2}, {3, 4} };
        SquareMatrix<T> threeRowsClone = { {1, 2, 3}, {4, 5, 6}, {7, 8, 9} };

        SquareMatrix<T> assigned;

        assigned = std::move(oneRowsClone);
        REQUIRE(assigned == oneRows);

        assigned = std::move(threeRowsClone);
        REQUIRE(assigned == threeRows);

        assigned = std::move(twoRowsClone);
        REQUIRE(assigned == twoRows);
    }

    SECTION("Operator =") {
        SquareMatrix<T> oneRows = { {1} };
        SquareMatrix<T> twoRows = { {1, 2}, {3, 4} };
        SquareMatrix<T> threeRows = { {1, 2, 3}, {4, 5, 6}, {7, 8, 9} };

        SquareMatrix<T> assigned;

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

    SECTION("Negation Operator -") {
        SquareMatrix<T> matrix = { {1, 2, 3}, {4, 5, 6}, {7, 8, 9} };
        SquareMatrix<T> expected = { {-1, -2, -3}, {-4, -5, -6}, {-7, -8, -9} };

        REQUIRE(expected == -matrix);
    }

    SECTION("Transpose Operator") {
        SquareMatrix<T> matrix = { {1, 2, 3}, {4, 5, 6}, {7, 8, 9} };
        SquareMatrix<T> expected = {{1, 4, 7}, {2, 5, 8}, {3, 6, 9}};

        REQUIRE(expected == matrix);

    }

    SECTION("Matrix/Vector/Scalar Operator */*=") {
        SquareMatrix<T> improperMatrix = { {1, 2}, {3, 4} };

        T scalar = 2;
        Vector<T> vector = { {1, 2, 3} };

        SquareMatrix<T> matrix1 = { {1, 2, 3}, {4, 5, 6}, {7, 8, 9} };
        SquareMatrix<T> matrix2 = { {10, 11, 12}, {13, 14, 15}, {16, 17, 18} };

        SquareMatrix<T> expectedSquareMatrix = { {84, 90, 96}, {201, 216, 231}, {318, 342, 366} };
        SquareMatrix<T> expectedScalarMatrix = { {2, 4, 6}, {8, 10, 12}, {14, 16, 18} };
        Vector<T> expectedVector = { {14}, {32}, {50} };

        REQUIRE_THROWS(improperMatrix * matrix1);

        REQUIRE(expectedSquareMatrix == matrix1 * matrix2);
        REQUIRE(expectedScalarMatrix == scalar * matrix1);
        REQUIRE(expectedVector == matrix1 * vector);

        matrix1 *= matrix2;
        REQUIRE(expectedSquareMatrix == matrix1);
    }

    SECTION("Operator +") {
        SquareMatrix<T> improperMatrix = { {1, 2}, {3, 4} };

        SquareMatrix<T> matrix1 = { {1, 2, 3}, {4, 5, 6}, {7, 8, 9} };
        SquareMatrix<T> matrix2 = { {10, 11, 12}, {13, 14, 15}, {16, 17, 18} };
        SquareMatrix<T> expected = { {11, 13, 15}, {17, 19, 21}, {23, 25, 27} };

        REQUIRE_THROWS(improperMatrix + matrix1);
        REQUIRE(expected == matrix1 + matrix2);

        matrix1 += matrix2;
        REQUIRE(expected == matrix1);
    }

    SECTION("Operator -") {
        SquareMatrix<T> improperMatrix = { {1, 2}, {3, 4} };
        SquareMatrix<T> matrix1 = { {1, 2, 3}, {4, 5, 6}, {7, 8, 9} };
        SquareMatrix<T> matrix2 = { {10, 11, 12}, {13, 14, 15}, {16, 17, 18} };
        SquareMatrix<T> expected = { {-9, -9, -9}, {-9, -9, -9}, {-9, -9, -9} };

        REQUIRE_THROWS(improperMatrix - matrix1);
        REQUIRE(expected == matrix1 - matrix2);

        matrix1 -= matrix2;
        REQUIRE(expected == matrix1);
    }

    SECTION("<<") {
        SquareMatrix<T> matrix1 = { {1, 2, 3}, {4, 5, 6}, {7, 8, 9} };
        std::cout << "Matrix << Operator\n";
        std::cout << matrix1 << "\n";
    }
}

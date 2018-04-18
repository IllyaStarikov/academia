//
//  test-symmetric-matrix.cpp
//  tests
//
//  Created by Illya Starikov on 04/16/18.
//  Copyright 2018. Illya Starikov. All rights reserved.
//

#include "catch.hpp"

#include "../lib/eigen.h"

TEST_CASE("Symmetric Matrix Tester", "[SymmetricMatrix]") {
    using T = double;

    SECTION("Default Constructor") {
        SymmetricMatrix<T> defaultMatrix;
    }

    SECTION("Regular Constructor") {
        SymmetricMatrix<T> matrix = {{1, 2, 3}, {2, 1, 3}, {3, 3, 1}};

        REQUIRE_THROWS(matrix = {{1, 2, 3}, {1, 2, 3}, {1, 2, 3}});
    }

    SECTION("Move Operator =") {
        SymmetricMatrix<T> oneRows = {{1}};
        SymmetricMatrix<T> twoRows = {{1, 2}, {2, 1}};
        SymmetricMatrix<T> threeRows = {{1, 2, 3}, {2, 1, 3}, {3, 3, 1}};

        SymmetricMatrix<T> oneRowsClone = {{1}};
        SymmetricMatrix<T> twoRowsClone = {{1, 2}, {2, 1}};
        SymmetricMatrix<T> threeRowsClone = {{1, 2, 3}, {2, 1, 3}, {3, 3, 1}};

        SymmetricMatrix<T> assigned;

        assigned = std::move(oneRowsClone);
        REQUIRE(assigned == oneRows);

        assigned = std::move(threeRowsClone);
        REQUIRE(assigned == threeRows);

        assigned = std::move(twoRowsClone);
        REQUIRE(assigned == twoRows);
    }

    SECTION("Operator =") {
        SymmetricMatrix<T> oneRows = {{1}};
        SymmetricMatrix<T> twoRows = {{1, 2}, {2, 1}};
        SymmetricMatrix<T> threeRows = {{1, 2, 3}, {2, 1, 3}, {3, 3, 1}};

        SymmetricMatrix<T> assigned;

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
        SymmetricMatrix<T> improperMatrix = {{1, 2}, {2, 1}};

        T scalar = 2;
        Vector<T> vector = {{1, 2, 3}};

        SymmetricMatrix<T> matrix1 = {{1, 2, 3}, {2, 1, 3}, {3, 3, 1}};
        SymmetricMatrix<T> matrix2 = {{4, 5, 6}, {5, 4, 6}, {6, 6, 4}};

        RectangularMatrix<T> expectedRectangularMatrix = {{32, 31, 30}, {31, 32, 30}, {33, 33, 40}};
        SymmetricMatrix<T> expectedScalarMatrix = {{2, 4, 6}, {4, 2, 6}, {6, 6, 2}};
        Vector<T> expectedVector = {{14}, {13}, {12}};

        REQUIRE_THROWS(improperMatrix * matrix1);

        REQUIRE(expectedRectangularMatrix == matrix1 * matrix2);
        REQUIRE(expectedScalarMatrix == scalar * matrix1);
        REQUIRE(expectedVector == matrix1 * vector);
    }

    SECTION("Operator +") {
        SymmetricMatrix<T> improperMatrix = {{1, 2}, {2, 1}};

        SymmetricMatrix<T> matrix1 = {{1, 2, 3}, {2, 1, 3}, {3, 3, 1}};
        SymmetricMatrix<T> matrix2 = {{4, 5, 6}, {5, 4, 6}, {6, 6, 4}};
        SymmetricMatrix<T> expected = {{5, 7, 9}, {7, 5, 9}, {9, 9, 5}};

        REQUIRE_THROWS(improperMatrix + matrix1);
        REQUIRE(expected == matrix1 + matrix2);

        matrix1 += matrix2;
        REQUIRE(expected == matrix1);
    }

    SECTION("Operator -") {
        SymmetricMatrix<T> improperMatrix = {{1, 2}, {2, 1}};

        SymmetricMatrix<T> matrix1 = {{4, 5, 6}, {5, 4, 6}, {6, 6, 4}};
        SymmetricMatrix<T> matrix2 = {{1, 2, 3}, {2, 1, 3}, {3, 3, 1}};
        SymmetricMatrix<T> expected = {{3, 3, 3}, {3, 3, 3}, {3, 3, 3}};

        REQUIRE_THROWS(improperMatrix - matrix1);
        REQUIRE(expected == matrix1 - matrix2);

        matrix1 -= matrix2;
        REQUIRE(expected == matrix1);
    }

    SECTION("Negation Operator -") {
        SymmetricMatrix<T> matrix =  {{1, 2, 3}, {2, 1, 3}, {3, 3, 1}};
        SymmetricMatrix<T> expected = {{-1, -2, -3}, {-2, -1, -3}, {-3, -3, -1}};

        REQUIRE(expected == -matrix);
    }

    SECTION("Transpose Operator") {
        SymmetricMatrix<T> matrix = {{1, 2, 3}, {2, 1, 3}, {3, 3, 1}};
        SymmetricMatrix<T> expected = {{1, 2, 3}, {2, 1, 3}, {3, 3, 1}};

        REQUIRE(expected == transpose(matrix));
    }

    SECTION("<<") {
        SymmetricMatrix<T> matrix = {{1, 2, 3}, {2, 1, 3}, {3, 3, 1}};
        std::cout << "Symmetric Matrix << Operator\n";
        std::cout << matrix << "\n";
    }
}

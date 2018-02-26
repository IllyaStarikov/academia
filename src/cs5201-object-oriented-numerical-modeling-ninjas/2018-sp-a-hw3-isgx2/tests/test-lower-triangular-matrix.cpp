//
//  test-polarpair.cpp
//  tests
//
//  Created by Illya Starikov on 01/31/18.
//  Copyright 2018. Illya Starikov. All rights reserved.
//
#include "catch.hpp"
#include "../src/lib/lower-triangular-matrix.h"

#include <iostream>

TEST_CASE("Lower Matrix Tester", "[LowerTriangularMatrix]") {
    using T = double;

    const auto size = 10;
    const T initialValue = -42;

    const auto alternateSize = 5;
    const T alternateInitialValue = 117;

    auto blankMatrix = LowerTriangularMatrix<T>(size);
    auto emptyMatrix= LowerTriangularMatrix<T>();
    auto matrix = LowerTriangularMatrix<T>(size, initialValue);
    auto alternateMatrix = LowerTriangularMatrix<T>(alternateSize, alternateInitialValue);

    LowerTriangularMatrix<T> initilizerListed = {
        {1 },
        {2, 3},
        {3, 4, 5},
        {4, 5, 6, 7}
    };

    SECTION("Valid Default Constructor") {
        REQUIRE(emptyMatrix.magnitude() == 0);
        REQUIRE_THROWS(emptyMatrix[0][0]);
        REQUIRE_THROWS(emptyMatrix[0]);
    }

    SECTION("Explicit Constructor") {
        for (int i = 0; i < size; i++) {
            REQUIRE_NOTHROW(matrix[i]);
            REQUIRE_NOTHROW(blankMatrix[i]);
            REQUIRE_NOTHROW(matrix[i]);

            for (int j = 0; j < size; j++) {
                if (j <= i) {
                    REQUIRE(matrix[i][j] == initialValue);
                } else {
                    REQUIRE_THROWS(matrix[i][j]);
                }
            }
        }

        REQUIRE_THROWS(matrix[size - 1][size]);
        REQUIRE_THROWS(matrix[size]);
        REQUIRE_THROWS(Vector<T>(-size));
    }

    SECTION("Initializer List") {
        const std::initializer_list<std::initializer_list<T>> badList = {
            {1, 2, 3, 4},
            {1, 2, 3, 4},
            {1, 2, 3, 4},
            {1, 2, 3, 4}
        };

        LowerTriangularMatrix<T> someMatrix;
        REQUIRE_THROWS(someMatrix = badList);

        for (int i = 0; i < initilizerListed.magnitude(); i++) {
            for (int j = 0; j <= i; j++) {
                REQUIRE(initilizerListed[i][j] == i + j + 1);
            }
        }
    }

    SECTION("Copy Constructor") {
        const auto offset = 100;

        for (int i = 0; i < size; i++) {
            for (int j = 0; j <= i; j++) {
                matrix[i][j] = i + j;
            }
        }

        auto copy = LowerTriangularMatrix<T>(matrix);

        for (int i = 0; i < size; i++) {
            for (int j = 0; j <= i; j++) {
                REQUIRE(matrix[i][j] == copy[i][j]);
            }
        }

        // Check for shallow copies
        for (int i = 0; i < size; i++) {
            for (int j = 0; j <= i; j++) {
                matrix[i][j] = (offset + i + j);
                REQUIRE(matrix[i][j] != copy[i][j]);
            }
        }
    }

    SECTION("Move Constructor") {
        emptyMatrix = std::move(matrix);

        for (int i = 0; i < size; i++) {
            for (int j = 0; j <= i; j++) {
                REQUIRE(emptyMatrix[i][j] == initialValue);
            }
        }
    }

    SECTION("Operator =") {
        const auto offset = 10;

        for (int i = 0; i < size; i++) {
            for (int j = 0; j <= i; j++) {
                matrix[i][j] = i + j;
            }
        }

        auto copy = matrix;

        for (int i = 0; i < size; i++) {
            for (int j = 0; j <= i; j++) {
                REQUIRE(matrix[i][j] == copy[i][j]);
            }
        }

        // Check for shallow copies
        for (int i = 0; i < size; i++) {
            for (int j = 0; j <= i; j++) {
                matrix[i][j] = (offset + i);
                REQUIRE(matrix[i][j] != copy[i][j]);
            }
        }
    }

    SECTION("Move = Operator") {
        auto equals = std::move(matrix);
        LowerTriangularMatrix<T> newMatrix;
        newMatrix = std::move(blankMatrix);

        for (int i = 0; i < size; i++) {
            for (int j = 0; j <= i; j++) {
                REQUIRE(equals[i][j] == initialValue);
            }
        }
    }

    SECTION("Operator []") {
        REQUIRE_THROWS(matrix[size]);
        REQUIRE_THROWS(matrix[size - 1][size]);
        REQUIRE_THROWS(matrix[-1]);

        REQUIRE_NOTHROW(matrix[size - 1]);

        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (j <= i) {
                    REQUIRE(matrix[i][j] == initialValue);
                } else {
                    REQUIRE_THROWS(matrix[i][j]);
                }
            }
        }
    }

    SECTION("Diagonal Tester") {
        LowerTriangularMatrix<T> diagnolMatrix = {
            {1, },
            {0, 2},
            {0, 0, 3},
            {0, 0, 0, 4}
        };

        for (int i = 0; i < 4; i++) {
            REQUIRE(diagnolMatrix.mainDiagonal()[i] == i + 1);
        }
    }

    SECTION("Operator <<") {
        std::cout << "Matrix Operator <<\n";
        std::cout << matrix << "\n";
    }
}

//
//  test-vector.cpp
//  tests
//
//  Created by Illya Starikov on 02/20/18.
//  Copyright 2018. Illya Starikov. All rights reserved.
//

#include "catch.hpp"
#include "../lib/eigen.h"

TEST_CASE("Vector Tester", "[Vector]") {
    using T = float;

    const auto size = 10;
    const T initialValue = 42;

    const auto alternateSize = 5;
    const T alternateInitialValue = 117;

    auto blankVector = Vector<T>(size);
    auto emptyVector = Vector<T>();
    auto vector = Vector<T>(size, initialValue);
    auto alternateVector = Vector<T>(alternateSize, alternateInitialValue);

    Vector<T> initilizerListed = { 1, 2, 3, 4 };

    SECTION("Default Constructor") {
        REQUIRE(emptyVector.size() == 0);
        REQUIRE_THROWS(emptyVector[0]);
    }

    SECTION("Explicit Constructors") {
        for (int i = 0; i < size; i++) {
            REQUIRE_NOTHROW(vector[i]);
            REQUIRE_NOTHROW(blankVector[i]);
            REQUIRE(vector[i] == initialValue);
        }

        REQUIRE_THROWS(vector[size]);
        REQUIRE_THROWS(Vector<T>(-size));
    }

    SECTION("Initializer List") {
        REQUIRE(initilizerListed.size() > 0);

        for (unsigned i = 0; i < initilizerListed.size(); i++) {
            REQUIRE(initilizerListed[i] == i + 1);
        }

        std::initializer_list<T> blank = {};
        REQUIRE_NOTHROW(Vector<T>(blank));
    }

    SECTION("Copy Constructor") {
        auto blankCopy(blankVector);
        const auto offset = 10;

        for (int i = 0; i < size; i++) {
            vector[i] = i;
        }

        auto copy(vector);

        for (int i = 0; i < size; i++) {
            REQUIRE(vector[i] == copy[i]);
        }

        // Check for shallow copies
        for (int i = 0; i < size; i++) {
            vector[i] = (offset + i); REQUIRE(vector[i] != copy[i]);
        }

        REQUIRE_THROWS(Vector<T>(-size));
    }

    SECTION("Move Constructor") {
        auto copyConstructor = Vector<T>(std::move(vector));

        for (int i = 0; i < size; i++) {
            REQUIRE(copyConstructor[i] == initialValue);
        }
    }

    SECTION("Norm") {
        Vector<T> vector = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        T result = static_cast<T>(19.6214); // This won't work when T is a float unless there's a cast

        auto EPSILON = 0.0001;

        REQUIRE(norm(vector) - result < EPSILON);
    }

    SECTION("Operator -") {
        Vector<T> v1 = {1, 2, 3, 4, 5};
        Vector<T> expected = {-1, -2, -3, -4, -5};

        REQUIRE(expected == -v1);
    }

    SECTION("Operator =") {
        const auto offset = 10;
        Vector<T> newVector;
        newVector = blankVector;

        for (int i = 0; i < size; i++) {
            vector[i] = i;
        }

        auto copy = vector;

        for (int i = 0; i < size; i++) {
            REQUIRE(vector[i] == copy[i]);
        }

        // Check for shallow copies
        for (int i = 0; i < size; i++) {
            vector[i] = (offset + i);
            REQUIRE(vector[i] != copy[i]);
        }

        auto third = copy = alternateVector;

        for (int i = 0; i < alternateSize; i++) {
            REQUIRE(copy[i] == alternateVector[i]);
            REQUIRE(third[i] == alternateVector[i]);
        }
    }

    SECTION("Operator *") {
        Vector<T> v1 = {1, 2, 3, 4, 5};
        Vector<T> v2 = {6, 7, 8, 9, 10};

        auto expected = 130;
        auto result = v1 * v2;

        REQUIRE(expected == result);
    }

    SECTION("Operator +") {
        Vector<T> v1 = {1, 2, 3, 4, 5};
        Vector<T> v2 = {6, 7, 8, 9, 10};

        Vector<T> expected = {7, 9, 11, 13, 15};
        auto result = v1 + v2;

        REQUIRE(expected == result);
    }

    SECTION("Operator -") {
        Vector<T> v1 = {1, 2, 3, 4, 5};
        Vector<T> v2 = {6, 7, 8, 9, 10};

        Vector<T> expected = {-5, -5, -5, -5, -5};
        auto result = v1 - v2;

        REQUIRE(expected == result);
    }


    SECTION("Operator +=") {
        Vector<T> v1 = {1, 2, 3, 4, 5};
        Vector<T> v2 = {6, 7, 8, 9, 10};

        Vector<T> expected = {7, 9, 11, 13, 15};
        v1 += v2;

        REQUIRE(expected == v1);
    }

    SECTION("Operator -=") {
        Vector<T> v1 = {1, 2, 3, 4, 5};
        Vector<T> v2 = {6, 7, 8, 9, 10};

        Vector<T> expected = {-5, -5, -5, -5, -5};
        v1 -= v2;

        REQUIRE(expected == v1);
    }

    SECTION("Scalar Operator *") {
        Vector<T> v1 = {1, 2, 3, 4, 5};
        T scalar = 2;

        Vector<T> expected = {2, 4, 6, 8, 10};
        auto result = scalar * v1;

        REQUIRE(expected == result);
    }

    SECTION("Scalar Operator *=") {
        Vector<T> v1 = {1, 2, 3, 4, 5};
        auto scalar = 2;

        Vector<T> expected = {2, 4, 6, 8, 10};
        v1 *= scalar;

        REQUIRE(expected == v1);
    }

    SECTION("Move = Operator") {
        auto equals = std::move(vector);
        Vector<T> newVector;
        newVector = std::move(blankVector);

        for (int i = 0; i < size; i++) {
            REQUIRE(equals[i] == initialValue);
        }
    }

    SECTION("Operator []") {
        REQUIRE_THROWS(vector[size]);
        REQUIRE_THROWS(vector[-1]);

        REQUIRE_NOTHROW(vector[size - 1]);

        vector[size - 1] = alternateInitialValue;
        REQUIRE(vector[size - 1] == alternateInitialValue);
    }

    SECTION("Operator <<") {
        std::cout << "Vector << Operator\n";
        std::cout << vector << "\n";
    }
}

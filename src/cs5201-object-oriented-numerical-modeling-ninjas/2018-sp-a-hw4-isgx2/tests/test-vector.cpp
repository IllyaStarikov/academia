//
//  test-vector.cpp
//  tests
//
//  Created by Illya Starikov on 02/20/18.
//  Copyright 2018. Illya Starikov. All rights reserved.
//

#define CATCH_CONFIG_MAIN


#include "catch.hpp"
#include "../src/lib/vector.h"

TEST_CASE("Vector Tester", "[Vector]") {
    using T = int;

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
        REQUIRE(emptyVector.magnitude() == 0);
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
        REQUIRE(initilizerListed.magnitude() > 0);

        for (int i = 0; i < initilizerListed.magnitude(); i++) {
            REQUIRE(initilizerListed[i] == i + 1);
        }
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
            vector[i] = (offset + i);
            REQUIRE(vector[i] != copy[i]);
        }

        REQUIRE_THROWS(Vector<T>(-size));
    }

    SECTION("Move Constructor") {
        auto copyConstructor = Vector<T>(std::move(vector));

        for (int i = 0; i < size; i++) {
            REQUIRE(copyConstructor[i] == initialValue);
        }
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

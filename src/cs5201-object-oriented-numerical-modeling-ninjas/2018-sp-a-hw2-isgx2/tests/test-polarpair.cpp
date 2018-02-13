//
//  test-polarpair.cpp
//  tests
//
//  Created by Illya Starikov on 01/31/18.
//  Copyright 2018. Illya Starikov. All rights reserved.
//

#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "../src/lib/polarpair.h"

#include <cmath>
#include <iomanip>
#include <iostream>

TEST_CASE("Polar Pair Testing", "[PolarPair]") {
    using R = double;
    using Theta = double;

    R defaultModulus = -12.0;
    Theta defaultArgument = 45.0;

    R altModulus = 3.0;
    Theta altArgument = 60.0;

    SECTION("Valid Default Constructor") {
        auto polarPair = PolarPair<R, Theta>();

        REQUIRE(polarPair.getArgument() == 0.0);
        REQUIRE(polarPair.getModulus() == 0.0);
    }

    SECTION("Valid Explicit Constructor") {
        auto polarPair = PolarPair<R, Theta>(defaultModulus, defaultArgument);

        REQUIRE(polarPair.getModulus() == defaultModulus);
        REQUIRE(polarPair.getArgument() == defaultArgument);
    }

    SECTION("Valid Copy Constructor") {
        auto polarPair = PolarPair<R, Theta>(defaultModulus, defaultArgument);
        auto copy = polarPair;

        REQUIRE(copy.getModulus() == defaultModulus);
        REQUIRE(copy.getArgument() == defaultArgument);

        REQUIRE(polarPair.getArgument() == defaultArgument);
        REQUIRE(polarPair.getModulus() == defaultModulus);

        copy.setModulus(altModulus);
        copy.setArgument(altArgument);

        REQUIRE(copy.getArgument() == altArgument);
        REQUIRE(copy.getModulus() == altModulus);

        REQUIRE(polarPair.getArgument() == defaultArgument);
        REQUIRE(polarPair.getModulus() == defaultModulus);
    }


    SECTION("Valid - Operator") {
        auto polarPair = PolarPair<R, Theta>(defaultModulus, defaultArgument);
        auto result = -polarPair;

        REQUIRE(result.getModulus() == -polarPair.getModulus());
        REQUIRE(result.getArgument() == polarPair.getArgument());
    }

    SECTION("Valid ~ Operator") {
        auto polarPair = PolarPair<R, Theta>(defaultModulus > 0 ? -defaultModulus : defaultModulus, defaultArgument);
        auto result = ~polarPair;

        REQUIRE(result == (defaultModulus > 0 ? defaultModulus : -defaultModulus));
    }

    SECTION("Valid ! Operator") {
        auto polarPair = PolarPair<R, Theta>(defaultModulus, defaultArgument);
        auto result = !polarPair;

        REQUIRE(result.getModulus() == defaultModulus);
        REQUIRE(result.getArgument() == -defaultArgument);
    }

    SECTION("Valid = Operator") {
        auto result = PolarPair<R, Theta>();
        auto first = PolarPair<R, Theta>(altModulus, altArgument);
        auto second = PolarPair<R, Theta>(defaultModulus, defaultArgument);

        result = first;

        REQUIRE(result.getModulus() == altModulus);
        REQUIRE(result.getArgument() == altArgument);

        result = first = second;

        REQUIRE(result.getModulus() == defaultModulus);
        REQUIRE(result.getArgument() == defaultArgument);
    }

    SECTION("Valid [] Operator") {
        auto polarPair = PolarPair<R, Theta>(defaultModulus, defaultArgument);

        REQUIRE(polarPair[0] == defaultModulus);
        REQUIRE(polarPair[1] == defaultArgument);

        CHECK_THROWS(polarPair[2]);
        CHECK_THROWS(polarPair[-1]);
    }


    SECTION("Valid * Operator") {
        auto resultModulus = defaultModulus * altModulus;
        auto resultArgument = defaultArgument + altArgument;

        auto result = PolarPair<R, Theta>(defaultModulus, defaultArgument) * PolarPair<R, Theta>(altModulus, altArgument);

        REQUIRE(result.getModulus() == resultModulus);
        REQUIRE(result.getArgument() == resultArgument);
    }

    SECTION("Valid / Operator") {
        auto resultModulus = defaultModulus / altModulus;
        auto resultArgument = defaultArgument - altArgument;

        auto result = PolarPair<R, Theta>(defaultModulus, defaultArgument) / PolarPair<R, Theta>(altModulus, altArgument);

        REQUIRE(result.getModulus() == resultModulus);
        REQUIRE(result.getArgument() == resultArgument);

        CHECK_THROWS(PolarPair<R, Theta>(defaultModulus, defaultArgument) / PolarPair<R, Theta>(0, 0));
    }

    SECTION("Valid > Operator") {
        auto polarPair1 = PolarPair<R, Theta>(defaultModulus, defaultArgument);
        auto polarPair2 = PolarPair<R, Theta>(altModulus, altModulus);

        if (abs(defaultModulus) > abs(altModulus)) {
            REQUIRE(polarPair1 > polarPair2);
        } else {
            REQUIRE(polarPair2 > polarPair1);
        }
    }

    SECTION("Valid < Operator") {
        auto polarPair1 = PolarPair<R, Theta>(defaultModulus, defaultArgument);
        auto polarPair2 = PolarPair<R, Theta>(altModulus, altModulus);

        if (abs(defaultModulus) < abs(altModulus)) {
            REQUIRE(polarPair1 < polarPair2);
        } else {
            REQUIRE(polarPair2 < polarPair1);
        }
    }

    SECTION("Valid == Operator") {
        double pi = M_PI;

        std::vector<std::pair<std::pair<R, Theta>, std::pair<R, Theta>>> trues = {
            std::make_pair<std::pair<R, Theta>, std::pair<R, Theta>>(std::make_pair(1, 0), std::make_pair(1, 0)),
            std::make_pair<std::pair<R, Theta>, std::pair<R, Theta>>(std::make_pair(2, 1.0/3.0*pi), std::make_pair(2, 1.0/3.0*pi)),
            std::make_pair<std::pair<R, Theta>, std::pair<R, Theta>>(std::make_pair(3, -pi), std::make_pair(3, -pi)),

            std::make_pair<std::pair<R, Theta>, std::pair<R, Theta>>(std::make_pair(1, pi), std::make_pair(1, 3.0*pi)),
            std::make_pair<std::pair<R, Theta>, std::pair<R, Theta>>(std::make_pair(2, 1.0/3.0*pi), std::make_pair(2, 7.0/3.0*pi)),
            std::make_pair<std::pair<R, Theta>, std::pair<R, Theta>>(std::make_pair(3, -4*pi), std::make_pair(3, 2*pi)),

            std::make_pair<std::pair<R, Theta>, std::pair<R, Theta>>(std::make_pair(1, pi), std::make_pair(-1, 0)),
            std::make_pair<std::pair<R, Theta>, std::pair<R, Theta>>(std::make_pair(2, 1.0/3.0*pi), std::make_pair(-2, 22.0/3.0*pi)),
            std::make_pair<std::pair<R, Theta>, std::pair<R, Theta>>(std::make_pair(3, pi), std::make_pair(-3, 0))
        };

        std::vector<std::pair<std::pair<R, Theta>, std::pair<R, Theta>>> falses = {
            std::make_pair<std::pair<R, Theta>, std::pair<R, Theta>>(std::make_pair(1, 0), std::make_pair(1.5, 0)),
            std::make_pair<std::pair<R, Theta>, std::pair<R, Theta>>(std::make_pair(1, pi), std::make_pair(1, 2.0*pi)),
            std::make_pair<std::pair<R, Theta>, std::pair<R, Theta>>(std::make_pair(3, pi), std::make_pair(-3, -pi))
        };

        for (const auto pair : trues) {
            auto polarPair1 = PolarPair<R, Theta>(pair.first.first, pair.first.second);
            auto polarPair2 = PolarPair<R, Theta>(pair.second.first, pair.second.second);

            REQUIRE(polarPair1 == polarPair2);
            REQUIRE(polarPair2 == polarPair1);
        }

        for (const auto pair : falses) {
            auto polarPair1 = PolarPair<R, Theta>(pair.first.first, pair.first.second);
            auto polarPair2 = PolarPair<R, Theta>(pair.second.first, pair.second.second);

            REQUIRE(!(polarPair1 == polarPair2));
            REQUIRE(!(polarPair2 == polarPair1));
        }
    }

    SECTION("Valid != Operator") {
        auto polarPair1 = PolarPair<R, Theta>(defaultModulus, defaultArgument);
        auto polarPair2 = PolarPair<R, Theta>(altModulus, altModulus);

        REQUIRE(polarPair2 != polarPair1);
    }

    SECTION("Stream Operator") {
        auto polarPair = PolarPair<R, Theta>(defaultModulus, defaultArgument);
        std::stringstream expected, actual;

        polarPair.setPrecision(6);

        expected << std::setprecision(6) << std::fixed << "(" << defaultModulus << ", " << defaultArgument << ")";
        actual << polarPair;

        REQUIRE(expected.str() == actual.str());
    }
}

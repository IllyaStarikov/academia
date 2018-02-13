//
//  test-norm.cpp
//  tests
//
//  Created by Illya Starikov on 02/01/18.
//  Copyright 2018. Illya Starikov. All rights reserved.
//

#include "catch.hpp"

#include "../src/lib/norm.h"
#include "../src/lib/polarpair.h"

TEST_CASE("Polar Pair Norm Testing", "[PolarPairNorm]") {
    using R = double;
    using Theta = double;

    auto norm = PolarPairNorm<R, Theta>();

    std::vector<PolarPair<R, Theta>> pairs = {
        PolarPair<R, Theta>(1.0, 45.0),
        PolarPair<R, Theta>(3.0, 45.0)
    };

    SECTION("Valid Norm Testing") {
        auto result = norm(pairs);

        REQUIRE(result == 4.0);
    }
}

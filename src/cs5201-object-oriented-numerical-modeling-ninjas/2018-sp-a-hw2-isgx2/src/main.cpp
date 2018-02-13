//
//  main.cpp
//  cs5201 - Numerical Modeling
//
//  Created by Illya Starikov on 01/15/18.
//  Copyright 2018. Illya Starikov. All rights reserved.
//

#include <iostream>

#include "functions/functions.h"
#include "lib/norm.h"
#include "lib/polarpair.h"

using R = double;
using Theta = double;

const int LENGTH_OF_OUTPUT = 5;

int main(int argc, const char *argv[]) {
    ensureEnoughArguments(argc);

    auto norm = PolarPairNorm<R, Theta>();

    auto filename = argv[1];
    auto fileContents = readInputFile(filename);
    auto polarPairs = parseFileContents<R, Theta>(fileContents);

    if (polarPairs.size() > LENGTH_OF_OUTPUT - 1) {
        std::cout <<  polarPairs[0] / polarPairs[1] << std::endl;
        std::cout <<  polarPairs[2] * polarPairs[3] << std::endl;
        std::cout << !polarPairs[4]                 << std::endl;

        std::cout << norm(polarPairs)               << std::endl;
    } else {
        displayErrorAndQuit("Not enough PolarPairs in Data Sets. Terminating.");
    }
}

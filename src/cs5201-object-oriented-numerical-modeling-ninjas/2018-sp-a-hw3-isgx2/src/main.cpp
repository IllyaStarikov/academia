//
//  main.cpp
//  cs5201 - Numerical Modeling
//
//  Created by Illya Starikov on 01/15/18.
//  Copyright 2018. Illya Starikov. All rights reserved.
//

#include <iostream>

#include "functions/functions.h"

int main(int argc, const char *argv[]) {
    ensureEnoughArguments(argc);

    auto filename = argv[1];
    auto fileContents = readInputFile(filename);
}

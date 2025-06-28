//
//  main.cpp
//  undergrad-research
//
//  Created by Illya Starikov on 01/02/18.
//  Copyright 2018. Illya Starikov. All rights reserved.
//

#include "functions.h"


int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "Not enough parameters. Terminating.\n";
        exit(-1);
    }

    auto filename = argv[1];
    auto program = getInput(filename);

    auto replacements = {
        replaceWhileLoops,
        replaceForLoops,
        insertInjectionCallsInMain,
        insertHeader
    };

    for (const auto& replacement : replacements) {
        program = replacement(program);
    }

    std::cout << program;
}



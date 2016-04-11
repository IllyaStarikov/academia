//
//  Functions.cpp
//  Random SQL Generator
//
//  Created by Illya Starikov on 4/10/16.
//  Copyright © 2016 Illya Starikov. All rights reserved.
//

#include "Functions.hpp"

std::string importFromFile(const std::string filename, const int lineNumber) {
    std::ifstream readin;
    readin.open(filename.c_str());
    
    std::string toReturn;
    
    for (int i = 0; i < lineNumber; i++) {
        getline(readin, toReturn);
    }
    
    readin.close();
    return toReturn;
}



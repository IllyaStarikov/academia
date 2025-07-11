//
//  main.cpp
//  Source Code
//
//  Created by Illya Starikov on 4/16/16.
//  Copyright © 2016 Illya Starikov. All rights reserved.
//

#include <iostream>

#include "Functions.hpp"
#include "Constants.h"
#include "DegreeDistribution.hpp"
#include "ShortestPath.hpp"
#include "Betweeness.hpp"
#include "CloseCent.hpp"
#include "GraphDiameter.hpp"
#include "CommunityDetection.hpp"


int main(int argc, const char * argv[]){
    auto input = getInput(FILENAME);
    auto map = parseInput(input);

    
    if (PRINT_SOLUTIONS) {
        printHeader(MAP);
        printMap(map);
    }
    
    degreeDistribution(map);
    shortestPaths(map);
    Betweeness(map);
    CommunityDetection(map);
    
}

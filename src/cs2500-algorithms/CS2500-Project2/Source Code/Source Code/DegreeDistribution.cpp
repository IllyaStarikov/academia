//
//  DegreeDistribution.cpp
//  Source Code
//
//  Created by Illya Starikov on 4/20/16.
//  Copyright © 2016 Illya Starikov. All rights reserved.
//

#include "DegreeDistribution.hpp"
const std::string UNWEIGHT_OUT_DEGREE = "Unweighted Out Degree";

void unweightedOutDegree(const AdjacencyMap & map) {
    printHeader(UNWEIGHT_OUT_DEGREE);
    for (const auto &element : map) {
        std::cout << element.first << ": " << element.second.size() << std::endl;
    }
}
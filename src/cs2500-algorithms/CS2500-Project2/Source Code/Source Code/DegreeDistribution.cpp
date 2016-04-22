//
//  DegreeDistribution.cpp
//  Source Code
//
//  Created by Illya Starikov on 4/20/16.
//  Copyright © 2016 Illya Starikov. All rights reserved.
//

#include "DegreeDistribution.hpp"


void degreeDistribution(const AdjacencyMap & map) {
    printHeader(UNWEIGHT_OUT_DEGREE);
    unweightedOutDegree(map);
    
    printHeader(WEIGHT_OUT_DEGREE);
    weightedOutDegree(map);
    
    printHeader(UNWEIGHT_IN_DEGREE);
    inDegree(map, false);
    
    printHeader(WEIGHT_IN_DEGREE);
    inDegree(map, true);

}

void unweightedOutDegree(const AdjacencyMap & map) {
    for (const auto &vector : map) {
        std::cout << vector.first << ": " << vector.second.size() << std::endl;
    }
}

void weightedOutDegree(const AdjacencyMap & map) {
    auto sum = double();
    
    for (const auto &elements : map) {
        sum = 0;
        for (const auto &pair : elements.second) {
            sum += pair.second;
        }
        std::cout << elements.first << ": " << sum << std::endl;
    }
}

void inDegree(const AdjacencyMap & map, const bool weighted) {
    auto weightMap = std::map<int, double>();
    int index;
    
    for (const auto & element : map) {
        for (const auto & pair : element.second) {
            index = pair.first;
            weighted ? weightMap[index] += pair.second : weightMap[index]++;
        }
    }
    
    for (const auto & element : weightMap) {
        std::cout << element.first << ": " << element.second << std::endl;
    }
}
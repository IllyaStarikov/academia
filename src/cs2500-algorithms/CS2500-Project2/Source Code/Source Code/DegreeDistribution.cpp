//
//  DegreeDistribution.cpp
//  Source Code
//
//  Created by Illya Starikov on 4/20/16.
//  Copyright © 2016 Illya Starikov. All rights reserved.
//

#include "DegreeDistribution.hpp"


void degreeDistribution(const AdjacencyMap & map) {
    unweightedOutDegree(map);
    weightedOutDegree(map);
    unweightedInDegree(map);
    weightedOutDegree(map);
}

void unweightedOutDegree(const AdjacencyMap & map) {
    printHeader(UNWEIGHT_OUT_DEGREE);
    for (const auto &vector : map) {
        std::cout << vector.first << ": " << vector.second.size() << std::endl;
    }
}

void weightedOutDegree(const AdjacencyMap & map) {
    printHeader(WEIGHT_OUT_DEGREE);
    auto sum = double();
    
    for (const auto &elements : map) {
        sum = 0;
        for (const auto &pair : elements.second) {
            sum += pair.second;
        }
        std::cout << elements.first << ": " << sum << std::endl;
    }
}

void unweightedInDegree(const AdjacencyMap & map) {
    printHeader(UNWEIGHT_IN_DEGREE);
    auto weightMap = std::map<int, int>();
    int index;
    
    for (const auto & element : map) {
        for (const auto & pair : element.second) {
            index = pair.first;
            weightMap[index]++;
        }
    }

    for (const auto & element : weightMap) {
        std::cout << element.first << ": " << element.second << std::endl;
    }
}

void weightedInDegree(const AdjacencyMap & map) {
    printHeader(WEIGHT_IN_DEGREE);
    auto weightMap = std::map<int, double>();
    int index;
    double total;
    
    for (const auto & element : map) {
        total = 0;
        for (const auto & pair : element.second) {
            index = pair.first;
            weightMap[index] += pair.second;
        }
    }
    
    for (const auto & element : weightMap) {
        std::cout << element.first << ": " << element.second << std::endl;
    }
}
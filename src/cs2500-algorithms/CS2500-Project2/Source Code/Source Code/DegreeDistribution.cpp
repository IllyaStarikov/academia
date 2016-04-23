//
//  DegreeDistribution.cpp
//  Source Code
//
//  Created by Illya Starikov on 4/20/16.
//  Copyright © 2016 Illya Starikov. All rights reserved.
//

#include "DegreeDistribution.hpp"

void degreeDistribution(const AdjacencyMap & map) {
    if (PRINT_SOLUTIONS) { printHeader(UNWEIGHT_OUT_DEGREE); }
    unweightedOutDegree(map);
    
    if (PRINT_SOLUTIONS) { printHeader(WEIGHT_OUT_DEGREE); }
    weightedOutDegree(map);
    
    if (PRINT_SOLUTIONS) { printHeader(UNWEIGHT_IN_DEGREE); }
    inDegree(map, false);
    
    if (PRINT_SOLUTIONS) { printHeader(WEIGHT_IN_DEGREE); }
    inDegree(map, true);
    
}

void unweightedOutDegree(const AdjacencyMap & map) {
    auto degree = std::map<int, int>();
    int index;
    
    for (const auto &element : map) {
//                if (PRINT_SOLUTIONS) { std::cout << element.first << ": " << element.second.size() << std::endl; }
        index = static_cast<int>(element.second.size());
        degree[index]++;
    }
    
    if (PRINT_SOLUTIONS) {
        for (const auto &element : degree) {
            std::cout << element.first << ": " << element.second << std::endl;
        }
    }
}

void weightedOutDegree(const AdjacencyMap & map) {
    auto sum = double();
    auto degree = std::map<int, int>();
    
    for (const auto &elements : map) {
        sum = 0;
        for (const auto &pair : elements.second) {
            sum += pair.second;
        }
        //       if (PRINT_SOLUTIONS) { std::cout << elements.first << ": " << sum << std::endl; }
        degree[sum]++;
    }
    
    if (PRINT_SOLUTIONS) {
        for (const auto &element : degree) {
            std::cout << element.first << ": " << element.second << std::endl;
        }
    }
}

void inDegree(const AdjacencyMap & map, const bool weighted) {
    auto weightMap = std::map<int, double>();
    auto weights = std::map<int, int>();
    int index;
    
    for (const auto & element : map) {
        for (const auto & pair : element.second) {
            index = pair.first;
            weighted ? weightMap[index] += pair.second : weightMap[index]++;
        }
        weights[weightMap[index]]++;
    }
    
    for (const auto & element : weights) {
        if (PRINT_SOLUTIONS) { std::cout << element.first << ": " << element.second << std::endl; }
    }
}
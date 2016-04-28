//
//  DegreeDistribution.cpp
//  Source Code
//
//  Created by Illya Starikov on 4/20/16.
//  Copyright © 2016 Illya Starikov. All rights reserved.
//

#include "DegreeDistribution.hpp"

void degreeDistribution(const AdjacencyMap & map) {
    /*--------------------Unweighted--------------------*/
    if (PRINT_SOLUTIONS) { printHeader(UNWEIGHT_OUT_DEGREE); }
    auto outDegreeMap = unweightedOutDegree(map);
    
    if (PRINT_SOLUTIONS) { printHeader(UNWEIGHT_IN_DEGREE); }
    auto inDegreeMap = inDegree(map, false);
    
    if (PRINT_SOLUTIONS) { printHeader("Unweighted Total Distribution"); }
    auto degrees = make_tuple(inDegreeMap, outDegreeMap);
    totalDistribution(degrees);
    
    
    /*--------------------Weighted--------------------*/
    if (PRINT_SOLUTIONS) { printHeader(WEIGHT_OUT_DEGREE); }
    outDegreeMap = weightedOutDegree(map);
    
    if (PRINT_SOLUTIONS) { printHeader(WEIGHT_IN_DEGREE); }
    inDegreeMap = inDegree(map, true);
    
    if (PRINT_SOLUTIONS) { printHeader("Weighted Total Distribution"); }
    degrees = make_tuple(inDegreeMap, outDegreeMap);
    totalDistribution(degrees);
    
}

std::map<int, double> unweightedOutDegree(const AdjacencyMap & map) {
    auto degree = std::map<int, double>();
    int index;
    
    for (const auto &element : map) {
        index = static_cast<int>(element.second.size());
        degree[index]++;
    }
    
    if (PRINT_SOLUTIONS) {
        for (const auto &element : degree) {
            std::cout << element.first << ": " << element.second << std::endl;
        }
    }
    
    return degree;
}

std::map<int, double> weightedOutDegree(const AdjacencyMap & map) {
    auto sum = double();
    auto degree = std::map<int, double>();
     
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
    
    return degree;
}

std::map<int, double> inDegree(const AdjacencyMap & map, const bool weighted) {
    auto weightMap = std::map<int, double>();
    auto weights = std::map<int, double>();
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
    
    return weights;
}

void totalDistribution(const std::tuple<std::map<int, double>, std::map<int, double>> &maps) {
    auto sum = std::get<0>(maps); // Get the first map. It's arbitrary.
    
    for (const auto & map: std::get<1>(maps)) {
        sum[map.first] += map.second; // Add the tuples from the in or out degree to what you already copied
    }
    
    for (const auto & element : sum) {
        std::cout << element.first << ": " << element.second << std::endl;
    }
}
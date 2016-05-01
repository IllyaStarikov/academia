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
    if (PRINT_SOLUTIONS) { totalDistribution(degrees); }
    
    
    /*--------------------Weighted--------------------*/
    if (PRINT_SOLUTIONS) { printHeader(WEIGHT_OUT_DEGREE); }
    outDegreeMap = weightedOutDegree(map);
    
    if (PRINT_SOLUTIONS) { printHeader(WEIGHT_IN_DEGREE); }
    inDegreeMap = inDegree(map, true);
    
    if (PRINT_SOLUTIONS) { printHeader("Weighted Total Distribution"); }
    degrees = make_tuple(inDegreeMap, outDegreeMap);
    if (PRINT_SOLUTIONS) { totalDistribution(degrees); }
    
    /*--------------------Max In, Out Degree--------------------*/
    maxDistribution(map);
    
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

void maxDistribution(const AdjacencyMap & map) {
    if (!PRINT_SOLUTIONS) { return; }
    
    printHeader("Maximum Distribution");
    auto max = findMaximumUnweightedOutDegree(map);
    printMaximumDistribution(max, false, false);
    
    max = findMaximumWeightedOutDegree(map);
    printMaximumDistribution(max, true, false);
    
    auto maxDouble = findMaximumInDegree(map, false);
    printMaximumDistribution(maxDouble, false, true);
    
    maxDouble = findMaximumInDegree(map, true);
    printMaximumDistribution(maxDouble, true, true);
    
    maxDouble = maxTotalDistribution(map, false);
    printMaximumDistribution(maxDouble, false, true);
    
    maxDouble = maxTotalDistribution(map, true);
    printMaximumDistribution(maxDouble, true, true);
}


std::tuple<int, std::vector<int>> findMaximumUnweightedOutDegree(const AdjacencyMap & map) {
    auto maxOutVertices = std::vector<int>();
    int sizeofMax = 0;
    for (auto const &element : map) {
        if (sizeofMax < element.second.size()) {
            maxOutVertices.clear();
            
            maxOutVertices.push_back(element.first);
            sizeofMax = static_cast<int>(element.second.size());
        } else if (sizeofMax == element.second.size()) {
            maxOutVertices.push_back(element.first);
        }
    }
    
    return std::make_tuple(sizeofMax, maxOutVertices);
}

std::tuple<int, std::vector<int>> findMaximumWeightedOutDegree(const AdjacencyMap & map) {
    auto maxOutVertices = std::vector<int>();
    int sizeofMax = 0, totalWeightOfElement = 0;
    
    for (auto const &element : map) {
        for (auto const &weightTuples : element.second) {
            totalWeightOfElement += weightTuples.second;
        }
        
        if (sizeofMax < totalWeightOfElement) {
            maxOutVertices.clear();
            
            maxOutVertices.push_back(element.first);
            sizeofMax = static_cast<int>(totalWeightOfElement);
        } else if (sizeofMax == totalWeightOfElement) {
            maxOutVertices.push_back(element.first);
        }
        
        totalWeightOfElement = 0;
    }
    
    return std::make_tuple(sizeofMax, maxOutVertices);
    
}

std::tuple<int, std::vector<double>> findMaximumInDegree(const AdjacencyMap & map, bool weighted) {
    double index = 0;
    auto maxOutVertices = std::vector<int>();
    
    auto weightMap = std::map<int, double>();
    auto weights = std::map<int, std::vector<double>>();
    
    for (const auto & element : map) {
        for (const auto & pair : element.second) {
            index = pair.first;
            weighted ? weightMap[index] += pair.second : weightMap[index]++;
        }
        weights[weightMap[index]].push_back(element.first);
    }
    
    auto itr = weights.rbegin();
    return std::make_tuple(itr -> first, itr -> second);
}

std::tuple<int, std::vector<double>> maxTotalDistribution(const AdjacencyMap & map, bool weighted) {
    double index = 0, sum = 0;
    auto maxOutVertices = std::vector<int>();
    
    auto weightMap = std::map<int, double>();
    auto weights = std::map<int, std::vector<double>>();
    auto sumMap = std::map<int, std::vector<double>>();
    
    for (const auto & element : map) {
        for (const auto & pair : element.second) {
            index = pair.first;
            weighted ? weightMap[index] += pair.second : weightMap[index]++;
        }
        weights[weightMap[index]].push_back(element.first);
    }
    
//    for (const auto & weight : weights) {
//        std::cout << weight.first << ": ";
//        for (const auto & cell : weight.second) {
//            std::cout << cell << ",";
//        }
//        std::cout << std::endl;
//    }
//    
    for (const auto & element : weights) {
        for (const auto & vertix : element.second) {
            if (weighted) {
                for (const auto & edge : map.at(vertix)) {
                    sum += edge.second;
            }
                
                index = element.first + sum;
                sumMap[index].push_back(vertix);
                sum = 0;
            } else {
                index = element.first + map.at(vertix).size();
                sumMap[index].push_back(vertix);
            }
        }
    }
    
//    for (const auto & weight : sumMap) {
//        std::cout << weight.first << ": ";
//        for (const auto & cell : weight.second) {
//            std::cout << cell << ",";
//        }
//        std::cout << std::endl;
//    }

    auto itr = sumMap.rbegin();
    return std::make_tuple(itr -> first, itr -> second);
}
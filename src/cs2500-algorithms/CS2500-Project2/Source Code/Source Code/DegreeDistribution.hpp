//
//  DegreeDistribution.hpp
//  Source Code
//
//  Created by Illya Starikov on 4/20/16.
//  Copyright © 2016 Illya Starikov. All rights reserved.
//

#ifndef DegreeDistribution_hpp
#define DegreeDistribution_hpp

#include "Constants.h"
#include "Functions.hpp"

#include <stdio.h>
#include <iostream>
#include <iomanip>

#include <vector>
#include <map>
#include <tuple>

void degreeDistribution(const AdjacencyMap & map);

std::map<int, double> unweightedOutDegree(const AdjacencyMap & map);
std::map<int, double> weightedOutDegree(const AdjacencyMap & map);

std::map<int, double> inDegree(const AdjacencyMap & map, const bool weighted);

void totalDistribution(const std::tuple<std::map<int, double>, std::map<int, double>> &maps);

void maxDistribution(const AdjacencyMap & map);

// All return the max vertice followed by the degree of each
std::tuple<int, std::vector<int>> findMaximumUnweightedOutDegree(const AdjacencyMap & map);
std::tuple<int, std::vector<int>> findMaximumWeightedOutDegree(const AdjacencyMap & map);
std::tuple<int, std::vector<double>> findMaximumInDegree(const AdjacencyMap & map, bool weighted);

template <typename T>
void printMaximumDistribution(const std::tuple<int, std::vector<T>> & distribution) {
    std::cout << "Maximum Out Degree: " << std::get<0>(distribution) << " With Vertices:" << std::endl;
    for (auto const & vertice : std::get<1>(distribution)) {
        std::cout << std::setw(4) << vertice << std::endl;
    }
    std::cout << std::endl;
}

#endif /* DegreeDistribution_hpp */

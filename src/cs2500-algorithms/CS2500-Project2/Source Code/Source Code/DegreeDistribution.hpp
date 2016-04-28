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

#include <vector>
#include <map>
#include <tuple>

void degreeDistribution(const AdjacencyMap & map);

std::map<int, double> unweightedOutDegree(const AdjacencyMap & map);
std::map<int, double> weightedOutDegree(const AdjacencyMap & map);

std::map<int, double> inDegree(const AdjacencyMap & map, const bool weighted);

void totalDistribution(const std::tuple<std::map<int, double>, std::map<int, double>> &maps);

#endif /* DegreeDistribution_hpp */

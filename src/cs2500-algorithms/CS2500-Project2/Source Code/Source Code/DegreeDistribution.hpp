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

void unweightedOutDegree(const AdjacencyMap & map);
void weightedOutDegree(const AdjacencyMap & map);

void inDegree(const AdjacencyMap & map, const bool weighted);

#endif /* DegreeDistribution_hpp */

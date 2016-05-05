//
//  CommunityDetection.hpp
//  Source Code
//
//  Created by Illya Starikov on 4/21/16.
//  Copyright © 2016 Illya Starikov. All rights reserved.
//

#ifndef CommunityDetection_hpp
#define CommunityDetection_hpp

#include <stdio.h>
#include <iostream> 
#include "Functions.hpp"
#include "Constants.h"
#include "GraphDiameter.hpp"
#include "Betweeness.hpp"

using AdjacencyMatrix = std::vector<std::vector<int>>;
using AdjacencyMap = std::map<int, std::vector<std::pair<int, double>>>;

std::pair<int, int> BetweenessEdgeDetection(const AdjacencyMap & map, int (&betweeness) [MAX_VERTEX][MAX_VERTEX]);
void CommunityDetection(AdjacencyMap & map);
void EdgeReconstruction(const AdjacencyMap & map, int (&betweeness)[MAX_VERTEX][MAX_VERTEX], bool Directness, bool Weightness, AdjacencyMatrix & matrix);


#endif /* CommunityDetection_hpp */

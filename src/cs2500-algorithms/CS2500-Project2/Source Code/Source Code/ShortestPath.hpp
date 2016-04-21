//
//  ShortestPath.hpp
//  Source Code
//
//  Created by Illya Starikov on 4/21/16.
//  Copyright © 2016 Illya Starikov. All rights reserved.
//

#ifndef ShortestPath_hpp
#define ShortestPath_hpp

#include <stdio.h>

#include "Constants.h"

void makeUndirected(std::vector<std::vector<int>> & vector, bool deleteSelfLoops = false);
void shortestPath(const AdjacencyMap & map, bool isDirected);
void shortestPaths(const AdjacencyMap & map);

#endif /* ShortestPath_hpp */

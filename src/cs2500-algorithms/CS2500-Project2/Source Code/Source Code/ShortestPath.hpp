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

void shortestPaths(const AdjacencyMap & map, VectArray & UWUDshort, VectArray & UWDshort, VectArray & WUDshort, VectArray & WDshort);

void makeUndirected(std::vector<std::vector<int>> & vector, bool deleteSelfLoops = true);
std::vector<std::vector<int>> shortestPath(const AdjacencyMap & map, const bool _makeUndirected, const bool makeUnweighted);
#endif /* ShortestPath_hpp */

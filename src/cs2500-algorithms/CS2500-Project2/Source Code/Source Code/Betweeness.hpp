//
//
// Betweeness.hpp 
// Source Code 
//
// Claire Trebing 
// April 26, 2016
//

#ifndef Betweeness_hpp
#define Betweeness_hpp

#include "Constants.h"
#include "Functions.hpp"
#include "ShortestPath.hpp"

#include <stdio.h> 
#include <iostream> 
#include <list> 

#include <map> 
#include <vector> 
#include <tuple> 
//N: Max Vertex Size = 99
//U: weight 
//V: target 

void PathReconstruction(const AdjacencyMap & map, int (&betweeness)[MAX_VERTEX], bool Directness, bool Weightness);
void BetweenessVertex(const AdjacencyMap & map);
void BetweenessEdge(const AdjacencyMap & map); 
void Betweeness(const AdjacencyMap & map); 

#endif  /* Betweeness_hpp */

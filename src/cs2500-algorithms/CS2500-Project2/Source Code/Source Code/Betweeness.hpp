//
// Betweeness.hpp 
// Source Code 
//
// Claire Trebing 
// April 26, 2016
//

//
#ifndef Betweeness_hpp
#define Betweeness_hpp

#include "Constants.h"
#include "Functions.hpp"

#include <stdio.h> 
#include <iostream> 

#include <map> 
#include <vector> 
#include <tuple> 
//N: Max Vertex Size = 99
//U: weight 
//V: target 

void PathReconstruction(const AdjacencyMap & map);
void Path(std::pair<int, double> & edge); 
int UndirectedUnWeightedBetweenessVertex(int i);
int UndirectedWeightedBetweenessVertex(int i);
int DirectedUnWeightedBetweenessVertex(int i);
int DirectedWeightedBetweenessVertex(int i); 

int UndirectedBetweenessEdge(const std::vector<std::pair<int, double>>>& edge); 
int DirectedBetweenessEdge(const std::vector<std::pair<int, double>>>& edge); 

#endif /* Betweeness_hpp */
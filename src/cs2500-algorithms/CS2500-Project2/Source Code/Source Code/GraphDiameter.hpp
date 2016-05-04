//
//  GraphDiameter.hpp
//  Source Code
//
//  Created by Claire Trebing on 5/1/16.
//

#ifndef GraphDiameter_hpp
#define GraphDiameter_hpp

#include <stdio.h>
#include <iostream> 

#include "Functions.hpp"
#include "Constants.h"

void GraphDiameter(const AdjacencyMap &map);
void ShortestPath(const AdjacencyMap &map, bool Directed, bool Weightness);
void SimpleDiam(const AdjacencyMatrix & matrix);

#endif /* GraphDiameter_hpp */

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

#include <vector>
#include <map>
#include <tuple>

std::pair<int, int> BetweenessEdgeDetection(const AdjacencyMap & map);
void CommunityDetection(); 


#endif /* CommunityDetection_hpp

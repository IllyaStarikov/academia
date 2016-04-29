//
//  Functions.hpp
//  Source Code
//
//  Created by Illya Starikov on 4/20/16.
//  Copyright © 2016 Illya Starikov. All rights reserved.
//

#ifndef Functions_hpp
#define Functions_hpp

#include <stdio.h>
#include <iostream>
#include <fstream>

#include <vector>
#include <map>
#include <tuple>

#include "Constants.h"


std::vector<std::string> getInput(std::string filename);
AdjacencyMap parseInput(std::vector<std::string> input);
std::string substring(std::string string, std::string delimeter, bool afterDelimeter = false);

void printMap(std::map<int, std::vector<std::pair<int, double>>> map);
void printHeader(std::string title);
void countMatrixOccurence(const AdjacencyMatrix &matrix);

#endif /* Functions_hpp */

//
//  Constants.h
//  Source Code
//
//  Created by Illya Starikov on 4/20/16.
//  Copyright © 2016 Illya Starikov. All rights reserved.
//

#ifndef Constants_h
#define Constants_h

#include <vector>
#include <map>
#include <tuple>

#include <iostream>

const bool PRINT_SOLUTIONS = true;

using AdjacencyMatrix = std::vector<std::vector<int>>;
using AdjacencyMap = std::map<int, std::vector<std::pair<int, double>>>;

const std::string MAP = "Map";

const std::string FILENAME = "Project2.csv";

const std::string UNWEIGHT_OUT_DEGREE = "Unweighted Out Degree";
const std::string WEIGHT_OUT_DEGREE = "Weighted Out Degree";
const std::string UNWEIGHT_IN_DEGREE = "Unweighted In Degree";
const std::string WEIGHT_IN_DEGREE = "Weighted In Degree";

const std::string SHORTEST_PATH_UNWEIGHTED_UNDIRECTED = "Shortest Path, Unweighted Undirected";
const std::string SHORTEST_PATH_WEIGHTED_UNDIRECTED = "Shortest Path, Weighted Undirected";
const std::string SHORTEST_PATH_UNWEIGHTED_DIRECTED = "Shortest Path, Unweighted Directed";
const std::string SHORTEST_PATH_WEIGHTED_DIRECTED = "Shortest Path, Weighted Directed";

const int INFINITY = 999999;
const int DEFAULT_WEIGHT_FOR_PATH = 1;

#endif /* Constants_h */

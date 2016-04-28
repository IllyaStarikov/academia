//
//  ShortestPath.cpp
//  Source Code
//
//  Created by Illya Starikov on 4/21/16.
//  Copyright © 2016 Illya Starikov. All rights reserved.
//

#include "ShortestPath.hpp"
#include "Functions.hpp"

#include <map>
#include <vector>


void shortestPaths(const AdjacencyMap & map, VectArray & UWUDshort, VectArray & UWDshort, VectArray & WUDshort, VectArray & WDshort) {
    if (PRINT_SOLUTIONS) { printHeader(SHORTEST_PATH_UNWEIGHTED_DIRECTED); }
    UWDshort = shortestPath(map, false, true);
    
    if (PRINT_SOLUTIONS) { printHeader(SHORTEST_PATH_WEIGHTED_DIRECTED); }
    WDshort = shortestPath(map, false, false);
    
    if (PRINT_SOLUTIONS) { printHeader(SHORTEST_PATH_WEIGHTED_UNDIRECTED); }
    WUDshort = shortestPath(map, true, false);
    
    if (PRINT_SOLUTIONS) { printHeader(SHORTEST_PATH_UNWEIGHTED_UNDIRECTED); }
    UWUDshort = shortestPath(map, true, true);
}

void makeUndirected(std::vector<std::vector<int>> & vector, bool deleteSelfLoops) {
    if (deleteSelfLoops) {
        for (int i = 0; i < vector.size(); i++) {
            vector[i][i] = 0;
        }
    }
    
    for (int i = 0; i < vector.size() - 1; i++) {
        for (int j = static_cast<int>(vector.size()) - 1; j > i; j--) {
            vector[j][i] = vector[i][j];
        }
    }
}

std::vector<std::vector<int>> shortestPath(const AdjacencyMap & map, const bool _makeUndirected, const bool makeUnweighted) {
    // Floyd - Walsh algorithm
    const int size = static_cast<int>(map.size()) + 2; // One for the index of map, other for index of solution vector
    auto solution = std::vector<std::vector<int>>(size, std::vector<int>(size, INFINITY)); // 2D Adjacency Matrix with size of map and default values of infinity
    // Copy the map to the two dimensional matrix
    for (auto element : map) {
        for (auto pair : element.second) {
            solution[element.first][pair.first] = makeUnweighted ? DEFAULT_WEIGHT_FOR_PATH : pair.second; // Make directed / undirected
        }
    }
    
    if (!_makeUndirected) { makeUndirected(solution); }
    
    // Iterate over entirety of matrices
    // Essentially, a glorified bubble sort
    for (int k = 0; k < size; k++) {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (i == j) {
                    solution[i][j] = 0;
                } else if (solution[i][j] > solution[i][k] + solution[k][j]) {
                    solution[i][j] = solution[i][k] + solution[k][j];
                }
            }
        }
    }
    
    if (PRINT_SOLUTIONS) {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (solution[i][j] != INFINITY) {
                    std::cout << i << " -> " << j << ": " << solution[i][j] << std::endl;
                }
            }
        }
    }
    
    return solution;
}
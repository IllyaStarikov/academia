//
//  ShortestPath.cpp
//  Source Code
//
//  Created by Illya Starikov on 4/21/16.
//  Copyright © 2016 Illya Starikov. All rights reserved.
//

#include "ShortestPath.hpp"
#include <map>
#include <vector>

const int INFINITY = 999999;

void shortestPaths(const AdjacencyMap & map) {
    shortestPath(map, true);
    shortestPath(map, false);
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

void shortestPath(const AdjacencyMap & map, bool isDirected) {
    const int size = static_cast<int>(map.size()) + 2; // One for the index of map, other for index of solution vector
    auto solution = std::vector<std::vector<int>>(size, std::vector<int>(size, INFINITY)); // 2D Adjacency Matrix with size of map and default values of infinity
    // Copy the map to the two dimensional matrix
    for (auto element : map) {
        for (auto pair : element.second) {
            solution[element.first][pair.first] = pair.second;
        }
    }
    
    if (!isDirected) { makeUndirected(solution); }
    
    for (int k = 0; k < size; k++) {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (solution[i][j] > solution[i][k] + solution[k][j]) {
                    solution[i][j] = solution[i][k] + solution[k][j];
                }
            }
        }
    }

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (solution[i][j] != INFINITY) {
                std::cout << i << " -> " << j << ": " << solution[i][j] << std::endl;
            }
        }
    }
}
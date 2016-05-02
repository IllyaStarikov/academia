//
//  GraphDiameter.cpp
//  Source Code
//
//  Created by Claire Trebing on 5/1/2016
//  

#include "Functions.hpp"
#include "GraphDiameter.hpp"
#include "Constants.h"
#include "ShortestPath.hpp"

#include <iostream>

void GraphDiameter(const AdjacencyMap &map){
	//Undirected, unweighted 
	printHeader(GRAPHDIAMETER_UNWEIGHTED_UNDIRECTED); 
	ShortestPath(map, false, false);

	//Directed, unweighted 
	printHeader(GRAPHDIAMETER_UNWEIGHTED_DIRECTED);
	ShortestPath(map, true, false);

	//Undirected, weighted
	printHeader(GRAPHDIAMETER_WEIGHTED_UNDIRECTED);
	ShortestPath(map, false, true); 

	//Directed, weighted
	printHeader(GRAPHDIAMETER_WEIGHTED_DIRECTED);
	ShortestPath(map, true, true); 
}

void ShortestPath(const AdjacencyMap &map, bool Directed, bool Weightness){
	// Floyd - Walsh algorithm
    const int size = static_cast<int>(map.size()) + 2; // One for the index of map, other for index of solution vector
    auto solution = std::vector<std::vector<int>>(size, std::vector<int>(size, INFINITY)); // 2D Adjacency Matrix with size of map and default values of infinity
    // Copy the map to the two dimensional matrix
    for (auto element : map) {
        for (auto pair : element.second) {
            solution[element.first][pair.first] = Weightness ? pair.second : DEFAULT_WEIGHT_FOR_PATH; // Make directed / undirected
        }
    }
    
    if (!Directed) { makeUndirected(solution); }
    
    // Iterate over entirety of matrices
    // Essentially, a glorified bubble sort
    for (int k = 0; k < size; k++) {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (i == j) {
                    solution[i][j] = 0;
                } 
                else if (solution[i][j] > solution[i][k] + solution[k][j]) {
                    solution[i][j] = solution[i][k] + solution[k][j];
                }
            }
        }
    }

    std::vector<std::pair<int, int>> GraphDiameterList;
    //Find the maximum value 
    int max = solution[0][0];
    for(int i = 0; i < MAX_VERTEX; i++){
    	for(int j = 0; j < MAX_VERTEX; j++){
    		if(solution[i][j] > max){
    			max = solution[i][j]; 
    			GraphDiameterList.clear(); 
    			GraphDiameterList.push_back(std::make_pair(i,j)); 	
    		}
    		if(solution[i][j] == max){
    			GraphDiameterList.push_back(std::make_pair(i,j));
    		}
    	}
    }

    if (PRINT_SOLUTIONS) {
        for (const auto &element : GraphDiameterList) {
            std::cout << element.first << ": " << element.second << std::endl;
        }
    }
    
    return; 
}
 


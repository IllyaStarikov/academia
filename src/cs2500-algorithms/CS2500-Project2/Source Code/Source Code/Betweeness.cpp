//
// Betweeness.cpp 
// Source Code 
//
// Claire Trebing 
// April 26, 2016
//
#include "Betweeness.hpp"

void VertexPathReconstruction(const AdjacencyMap & map, int (&betweeness)[MAX_VERTEX], bool Directness, bool Weightness){
	// Floyd - Walsh algorithm
    const int size = static_cast<int>(map.size()) + 2; // One for the index of map, other for index of solution vector
    auto solution = std::vector<std::vector<int>>(size, std::vector<int>(size, INFINITY)); // 2D Adjacency Matrix with size of map and default values of infinity
    // Copy the map to the two dimensional matrix
    for (auto element : map) {
        for (auto pair : element.second) {
            solution[element.first][pair.first] = Weightness ? DEFAULT_WEIGHT_FOR_PATH : pair.second; // Make directed / undirected
        }
    }
    
    if (!Directness) { makeUndirected(solution); }
		
	// Iterate over entirety of matrices
	// Also keeps track of what vertexes are included in the solution
    for (int k = 0; k < size; k++) {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (i == j) {
                    solution[i][j] = 0;
                } else if (solution[i][j] > solution[i][k] + solution[k][j]) {
                    solution[i][j] = solution[i][k] + solution[k][j];
					if(Weightness){
						betweeness[k] += pair.second; 
					}
					else{
						betweeness[k]++; //Since k is involved in the path, up it's betweenness value 
					}
                }
            }
        }
    }
    return; 
}

void EdgePathReconstruction(const AdjacencyMap & map, int (&betweeness)[MAX_VERTEX][MAX_VERTEX], bool Directness, bool Weightness){
		// Floyd - Walsh algorithm
    const int size = static_cast<int>(map.size()) + 2; // One for the index of map, other for index of solution vector
    auto solution = std::vector<std::vector<int>>(size, std::vector<int>(size, INFINITY)); // 2D Adjacency Matrix with size of map and default values of infinity
    // Copy the map to the two dimensional matrix
    for (auto element : map) {
        for (auto pair : element.second) {
            solution[element.first][pair.first] = Weightness ? DEFAULT_WEIGHT_FOR_PATH : pair.second; // Make directed / undirected
        }
    }
    
    if (!Directness) { makeUndirected(solution); }
		
	// Iterate over entirety of matrices
	// Also keeps track of what vertexes are included in the solution
    for (int k = 0; k < size; k++) {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (i == j) {
                    solution[i][j] = 0;
                } else if (solution[i][j] > solution[i][k] + solution[k][j]) {
                    solution[i][j] = solution[i][k] + solution[k][j];
					if(Weightness){
						betweeness[i][k] += pair.second;
					}
					else{
						betweeness[i][k] ++; 
					}
                }
            }
        }
    }
    return; 
}

void BetweenessVertex(const AdjacencyMap & map){
	int betweeness[MAX_VERTEX] = {0};
	
	//Undirected, unweighted
	VertexPathReconstruction(map, betweeness, false, false);
	printHeader(BETWEENESS_VERTEX_UNWEIGHTED_UNDIRECTED); 
	for(int i = 0; i < MAX_VERTEX; ++i){
		std::cout << i << ":" << betweeness[i];
	}
	
	//directed, unweighted
	VertexPathReconstruction(map, betweeness, true, false);
	printHeader(BETWEENESS_VERTEX_UNWEIGHTED_DIRECTED);
	for(int i = 0; i < MAX_VERTEX; ++i){
		std::cout << i << ":" << betweeness[i]; 
	}
	
	//undirected, weighted
	VertexPathReconstruction(map, betweeness, false, true);
	printHeader(BETWEENESS_VERTEX_WEIGHTED_UNDIRECTED);
	for(int i = 0; i < MAX_VERTEX; ++i){
		std::cout << i << ":" << betweeness[i]; 
	}
	
	//directed, weighted 
	VertexPathReconstruction(map, betweeness, true, true);
	printHeader(BETWEENESS_VERTEX_WEIGHTED_DIRECTED);
	for(int i = 0; i < MAX_VERTEX; ++i){
		std::cout << i << ":" << betweeness[i];
	}
	return;	
}

void BetweenessEdge(const AdjacencyMap & map){
	int beweeness[MAX_VERTEX][MAX_VERTEX] = {(0,0)};
	//Undirected, unweighted
	VertexPathReconstruction(map, betweeness, false, false);
	printHeader(BETWEENESS_EDGE_UNWEIGHTED_UNDIRECTED); 
	for(int i = 0; i < MAX_VERTEX; ++i){
		for(int j = 0; j < MAX_VERTEX; ++j){
			std::cout << "(" << i  << "," << j << ")" << ":" << beweeness[i][j] <<std::endl;
		}
	}
	
	//directed, unweighted
	VertexPathReconstruction(map, betweeness, true, false);
	printHeader(BETWEENESS_EDGE_UNWEIGHTED_DIRECTED);
	for(int i = 0; i < MAX_VERTEX; ++i){
		for(int j = 0; j < MAX_VERTEX; ++j){
			std::cout << "(" << i  << "," << j << ")" << ":" << beweeness[i][j] << std::endl;
		} 
	}
	
	//undirected, weighted
	VertexPathReconstruction(map, betweeness, false, true);
	printHeader(BETWEENESS_EDGE_WEIGHTED_UNDIRECTED);
	for(int i = 0; i < MAX_VERTEX; ++i){
		for(int j = 0; j < MAX_VERTEX; ++j){
			std::cout << "(" << i  << "," << j << ")" << ":" << beweeness[i][j] << std::endl;
		} 
	}
	
	//directed, weighted 
	VertexPathReconstruction(map, betweeness, true, true);
	printHeader(BETWEENESS_EDGE_WEIGHTED_DIRECTED);
	for(int i = 0; i < MAX_VERTEX; ++i){
		for(int j = 0; j < MAX_VERTEX; ++j){
			std::cout << "(" << i  << "," << j << ")" << ":" << beweeness[i][j] << std::endl;
		}
	}
	return; 
}

void Betweeness(const AdjacencyMap & map){
	BetweenessVertex(map);
	BetweenessEdge(map); 
	return;
}

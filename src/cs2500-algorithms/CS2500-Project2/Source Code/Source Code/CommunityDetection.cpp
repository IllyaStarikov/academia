//
//  CommunityDetection.cpp
//  Source Code
//
//  Created by Claire Trebing on 5/1/2016
//  

#include "CommunityDetection.hpp"


std::pair<int,int> BetweenessEdgeDetection(std::map<int, std::vector<std::pair<int, double>>> & map, int (&betweeness) [MAX_VERTEX][MAX_VERTEX], AdjacencyMatrix & matrix){
	int max; 
	std::pair<int, int> toRemove;
	//Undirected, unweighted
	EdgeReconstruction(map, betweeness, false, false, matrix); 

	max = betweeness[0][0]; 
	toRemove.first = 0; 
	toRemove.second = 0; 
	for(int i = 0; i < MAX_VERTEX; ++i){
		for(int j = 0; j < MAX_VERTEX; ++j){
			if(betweeness[i][j] > max){
				max = betweeness[i][j];
				toRemove.first = i; 
				toRemove.second = j;   
			}
		}
	}

	return toRemove; 
}

void EdgeReconstruction(const AdjacencyMap & map, int (&betweeness)[MAX_VERTEX][MAX_VERTEX], bool Directness, bool Weightness, AdjacencyMatrix & matrix){
		// Floyd - Walsh algorithm
    const int size = static_cast<int>(map.size()) + 2; // One for the index of map, other for index of solution vector
    matrix = std::vector<std::vector<int>>(size, std::vector<int>(size, INFINITY)); // 2D Adjacency Matrix with size of map and default values of infinity
    // Copy the map to the two dimensional matrix
    for (auto element : map) {
        for (auto pair : element.second) {
            matrix[element.first][pair.first] = Weightness ? DEFAULT_WEIGHT_FOR_PATH : pair.second; // Make directed / undirected
        }
    }
    
    if (!Directness) { makeUndirected(matrix); }
		
	// Iterate over entirety of matrices
	// Also keeps track of what vertexes are included in the solution
    for (int k = 0; k < size; k++) {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (i == j) {
                    matrix[i][j] = 0;
                } else if (matrix[i][j] > matrix[i][k] + matrix[k][j]) {
                    matrix[i][j] = matrix[i][k] + matrix[k][j];
					if(Weightness){
                        for (const auto & pairs : map.at(k)) {
                            betweeness[i][k] += pairs.second;
                        }
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

void CommunityDetection(AdjacencyMap & map){
	
	AdjacencyMatrix matrix; 
    int betweeness[MAX_VERTEX][MAX_VERTEX];
	int x, y;
	auto ToRemove = BetweenessEdgeDetection(map, betweeness, matrix);
	x = ToRemove.first;
	y = ToRemove.second;
//    map[x].erase(map[x].begin());
	for (int i = 0; i < 5; i++){
//		map[x].erase(map[x].begin() + y);
        map.erase(x);
        std::cout << "EDGE: " << x  << ": " << y << std::endl;
		std::cout<<"Betweeness of Edge Removed: "<<betweeness[x][y]<<std::endl;
		ToRemove = BetweenessEdgeDetection(map, betweeness, matrix);
		SimpleDiam(matrix);
		x = ToRemove.first;
		y = ToRemove.second;
	}
  return;
} 

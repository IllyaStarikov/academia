//
//  CommunityDetection.cpp
//  Source Code
//
//  Created by Claire Trebing on 5/1/2016
//  

#include "CommunityDetection.hpp"


std::pair<int,int> BetweenessEdgeDetection(std::map<int, std::vector<std::pair<int, double>>> & map, int (&betweeness) [MAX_VERTEX][MAX_VERTEX]){
	int max; 
	std::pair<int, int> toRemove;
	//Undirected, unweighted
	EdgeReconstruction(map, betweeness, false, false);

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

void EdgeReconstruction(const AdjacencyMap & map, int (&betweeness)[MAX_VERTEX][MAX_VERTEX], bool Directness, bool Weightness){
		// Floyd - Walsh algorithm
    const int size = static_cast<int>(map.size()) + 2; // One for the index of map, other for index of solution vector
    auto solution = std::vector<std::vector<int>>(size, std::vector<int>(size, INFINITY)); // 2D Adjacency Matrix with size of map and default values of infinity
    // Copy the map to the two dimensional matrix
    for (auto element : map) {
        for (auto pair : element.second) {
            solution[element.first][pair.first] = Weightness ? DEFAULT_WEIGHT_FOR_PATH : pair.second; // Make directed / undirected
        }
    }
    
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
void SimpleDiam(const int (&betweeness)[MAX_VERTEX][MAX_VERTEX]){
		std::vector<std::pair<int, int>> GraphDiameterList;
		int max = betweeness[0][0];
    for(int i = 0; i < MAX_VERTEX; i++){
    	for(int j = 0; j < MAX_VERTEX; j++){
    		if(betweeness[i][j] > max){
    			max = betweeness[i][j]; 
    			GraphDiameterList.clear(); 
    			GraphDiameterList.push_back(std::make_pair(i,j)); 	
    		}
    		if(betweeness[i][j] == max){
    			GraphDiameterList.push_back(std::make_pair(i,j));
    		}
    	}
    }
		
		if (PRINT_SOLUTIONS) {
    	std::cout <<"Diameter: "<<max<<std::endl;
        for (const auto &element : GraphDiameterList) {
            std::cout << element.first << ": " << element.second << std::endl;
        }
    }
	return; 
}

void CommunityDetection(AdjacencyMap & map){
	 
    int betweeness[MAX_VERTEX][MAX_VERTEX];
	int x, y;
	auto ToRemove = BetweenessEdgeDetection(map, betweeness);
	x = ToRemove.first;
	y = ToRemove.second;
//    map[x].erase(map[x].begin());
	for (int i = 0; i < 5; i++){
//		map[x].erase(map[x].begin() + y);
        map.erase(x);
        std::cout << "EDGE: " << x  << ": " << y << std::endl;
		std::cout<<"Betweeness of Edge Removed: "<<betweeness[x][y]<<std::endl;
		ToRemove = BetweenessEdgeDetection(map, betweeness);
		SimpleDiam(betweeness);
		x = ToRemove.first;
		y = ToRemove.second;
	}
  return;
} 

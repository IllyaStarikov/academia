//
// Betweeness.cpp 
// Source Code 
//
// Claire Trebing 
// April 26, 2016
//

#include "Betweeness.hpp"
void PathReconstruction(const AdjacencyMap & map){
	int distance[N][N]; //array of minimum distances
	int** next = new (int**)[N]; //2D array of pointers 
	for(int i = 0; i < N; ++i){
		next[i] = new (int*)[N];
	}
	
	for(int i = 0; i < N; ++i){
		for(int j = 0; j < N; ++j){
			next[i][j] = NULL; 
		}
	}
	
	
}
void Path(std::pair<int, double> & edge); 

int UndirectedUnWeightedBetweenessVertex(int i){
	int N = 99; //N is the max vertex  
	int Betweeness = 0; 
	for(int j = 0; j <= N; j++){
		if(i != j){
			for(int k = j+1; k <= N; k++){
				if(i != k){

				}
			}
		}
	}
	return Betweeness; 
}

int DirectedUnWeightedBetweenessVertex(int i){
	return 1;
}
int UndirectedBetweenessEdge(const std::pair<int, double>& edge){
	return 1; 
} 

int DirectedBetweenessEdge(const std::vector<std::pair<int, double>>>& edge){
	return 1; 
}
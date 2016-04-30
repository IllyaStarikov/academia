////
//// Betweeness.cpp 
//// Source Code 
////
//// Claire Trebing 
//// April 26, 2016
////
//
//#include "Betweeness.hpp"
//
//void PathReconstruction(const AdjacencyMap & map, std::list<int>** & path, bool Directness, bool Weightness){
//		// Floyd - Walsh algorithm
//    const int size = static_cast<int>(map.size()) + 2; // One for the index of map, other for index of solution vector
//    auto solution = std::vector<std::vector<int>>(size, std::vector<int>(size, INFINITY)); // 2D Adjacency Matrix with size of map and default values of infinity
//    // Copy the map to the two dimensional matrix
//    for (auto element : map) {
//        for (auto pair : element.second) {
//            solution[element.first][pair.first] = Weightness ? DEFAULT_WEIGHT_FOR_PATH : pair.second; // Make directed / undirected
//        }
//    }
//    
//    if (!Weightness) { makeUndirected(solution); }
//		
//	// Iterate over entirety of matrices
//	// Also keeps track of what vertexes are included in the solution
//    for (int k = 0; k < size; k++) {
//        for (int i = 0; i < size; i++) {
//            for (int j = 0; j < size; j++) {
//                if (i == j) {
//                    solution[i][j] = 0;
//                } else if (solution[i][j] > solution[i][k] + solution[k][j]) {
//                    solution[i][j] = solution[i][k] + solution[k][j];
//					//Add k to the shortest path list
//					path[i][j].push_back(k); 
//					path[i][j].push_back(j); 
//                }
//            }
//        }
//    }
//    return; 
//}
//
//void BetweenessVertex(const AdjacencyMap & map, const AdjacencyMatrix int**& vertex){
//	std::list<int>** path; //This will hold the paths discovered upon reconstruction 
//	path = new std::list<int>* [MAX_VERTEX];
//	Betweeness = new int* [MAX_VERTEX];
//	int* runner = NULL; 
//	for(int i = 0; i < MAX_VERTEX; ++i){
//		path[i] = new std::list<int> [MAX_VERTEX];
//	}
//		
//	for(int i = 0; i < MAX_VERTEX; ++i){
//		for(int j = 0; j < MAX_VERTEX; ++j){
//			path[i][j].push_back(i); 
//			path[i][j].push_back(j);
//		}
//	}
//	//Undirected, unweighted
//	PathReconstruction(map, path, false, false);
//	for(int i = 0; i < MAX_VERTEX; ++i){ // Stating point at i 
//		for(int j = 0; j < MAX_VERTEX; ++j){ //Ending at j 
//			for(std::list<int>::const runner = path[i][j].begin(), end = path[i][j].end(); runner != end; runner++){
//				Betweeness[runner]++;
//			}
//		}
//	}
//	printHeader(Undirected, Unweighted Betweeness); 
//	for(int i = 0; i < MAX_VERTEX; ++i){
//		std::cout << i << ":" << Betweeness[i];
//	}
//	//directed, unweighted
//	PathReconstruction(map, path, true, false);
//	//undirected, weighted
//	PathReconstruction(map, path, false, true);
//	//directed, weighted 
//	PathReconstruction(map, path, true, true);
//	
//	/* for(int i = 0; i < MAX_VERTEX; ++i){
//		for(int j = 0; j < MAX_VERTEX; ++j){
//			path[i][j]
//		}
//	} */
//	return; 
//}
//
//void Betweeness(const AdjacencyMap & map){
//	int** vertex = new int [MAX_VERTEX];
//	for(int i = 0; i < MAX_VERTEX; ++i){
//		vertex[i] = new int [MAX_VERTEX];
//	}
//	
//	BetweenessVertex(map, vertex); 
//	
//	int** edge = new int[MAX_VERTEX];
//	for(int i = 0; i < MAX_VERTEX; ++i){
//		edge[i] = new int [MAX_VERTEX];
//	}
//	std::cout << "Deallocate edge and vertex" endl;
//}
//
//int UndirectedBetweenessEdge(const std::pair<int, double>& edge){
//	return 1; 
//} 
//
//int DirectedBetweenessEdge(const std::vector<std::pair<int, double>>>& edge){
//	return 1; 
//}

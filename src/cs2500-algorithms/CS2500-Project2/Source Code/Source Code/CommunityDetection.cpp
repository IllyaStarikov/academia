//
//  CommunityDetection.cpp
//  Source Code
//
//  Created by Claire Trebing on 5/1/2016
//  

std::pair<int, int> BetweenessEdgeDetection(const AdjacencyMap & map, int (&betweeness) [MAX_VERTEX][MAX_VERTEX], AdjacencyMatrix & matrix){
	int max; 
	std::pair toRemove; 
	//Undirected, unweighted
	matrix = CommunityPathReconstruction(map, betweeness, false, false); 

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

int BetweenessVertexDetection(const AdjacencyMap & map, int (&betweeness) [MAX_VERTEX]){
	int vertexMax; 
	int max; 

	VertexPathReconstruction(map, betweeness, false, false)

	max = betweeness[0];
	vertexMax = 0; 
	for(int i = 0; i < MAX_VERTEX; ++i){
		if(betweeness[i] > max){
			max = betweeness[i]; 
			vertexMax = i; 
		}
	}
	
	return vertexMax; 
}

AdjacencyMap CommunityDetection(AdjacencyMap & map){
	
	AdjacencyMatrix solutions; 
	int beweeness[MAX_VERTEX][MAX_VERTEX] = {(0,0)};
	int x, y;
	auto ToRemove = BetweenessEdgeDetection(map, betweeness, matrix);
	x = ToRemove.first;
	y = ToRemove.second;
	for (int i = 0; i < 5; i++){
		map[x][y].erase();
		std::cout<<"Betweeness of Edge Removed: "<<betweeness[x][y]<<std::endl;
		ToRemove = BetweenessEdgeDetection(map, betweeness, matrix);
		SimpleDiam(matrix);
		x = ToRemove.first;
		y = ToRemove.second;
	}

	
	


} 

//
//  Functions.cpp
//  Source Code
//
//  Created by Illya Starikov on 4/20/16.
//  Copyright © 2016 Illya Starikov. All rights reserved.
//

#include "Functions.hpp"

const std::string CSV_DELIMETER = ",";

std::vector<std::string> getInput(std::string filename) {
    std::ifstream readin;
    readin.open(filename.c_str());
    
    auto strings = std::vector<std::string>();
    auto line = std::string();
    
    getline(readin, line); /* First line is header */
    
    while (readin.eof() == false) {
        getline(readin, line);
        strings.push_back(line);
    }
    
    strings.pop_back(); /* Gets garbage at the end */
    return strings;
}

AdjacencyMap parseInput(std::vector<std::string> input) {
    auto adjacencyMap = AdjacencyMap();
    auto vertexWeight = std::pair<int, double>();
    
    for(auto edge: input) {
        /* Extrapolate data — source, target, weight */
        auto source = std::stoi(substring(edge, CSV_DELIMETER, false));
        edge = substring(edge, CSV_DELIMETER, true);
        
        auto target = std::stoi(substring(edge, CSV_DELIMETER, false));
        edge = substring(edge, CSV_DELIMETER, true);
        
        auto weight = std::stod(substring(edge, CSV_DELIMETER, false));
        edge = substring(edge, CSV_DELIMETER, true);
        
        /* Insert into Map */

        vertexWeight = std::make_pair(target, weight);
        adjacencyMap[source].push_back(vertexWeight);
    }
    
    return adjacencyMap;
}

void printMap(std::map<int, std::vector<std::pair<int, double>>> map) {    
    for (auto const &element : map) { // Iterate over the key and the map's vector, of type vector and pairs
        std::cout << element.first << " "; // Print the key, which is the first part of the map
        for (auto const &pairs : element.second) { // Iterate over all pairs in the vector of pairs
            std::cout << "<" << pairs.first << ", " << pairs.second << ">"; // Print off target (first) and weight (second)
        }
        std::cout << std::endl;
    }
}

std::string substring(std::string string, std::string delimeter, bool afterDelimeter) {
    int position = static_cast<int>(string.find(delimeter));
    std::string substring = afterDelimeter ? string.substr(position + 1) : string.substr(0, position);
    
    return substring;
}

void printHeader(std::string title) {
    std::cout << "/*-------------------- "<< title << "--------------------*/" << std::endl;
}

void countMatrixOccurence(const AdjacencyMatrix &matrix) {
    if (matrix.size() != matrix[0].size()) { std::cerr << "Matrix isn't perfect square"; }
    auto weight = std::map<int, int>();
    
    
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix[i].size(); j++) {
            weight[matrix[i][j]]++;
        }
    }
    
    if (PRINT_SOLUTIONS) {
        for (auto const &element : weight) {
            std::cout << element.first << ": " << element.second << std::endl;
        }
        
        std::cout << std::endl;
    }
}

int maxVertexPossible(const AdjacencyMap& map){
    int 
    return max; 
}
//
//  functions.hpp
//  Source Code
//
//  Created by Illya Starikov on 12/20/16.
//  Copyright © 2016 Illya Starikov. All rights reserved.
//

#include <vector>
#include <tuple>

#ifndef functions_hpp
#define functions_hpp

#include "board.hpp"

bool inBounds(const int x, const int y);
std::tuple<int, int> getPlayerMove(const char player, const Board board);

// Takes a two dimensional array and returns a one dimensional array of the same type
template <typename T>
auto flatten(std::vector<std::vector<T>> toFlatten) {
	auto result = std::vector<T>();
	for (const auto& subarray: toFlatten) {
		result.insert(result.end(), subarray.begin(), subarray.end());
	}
	
	return result;
}

// Take two arrays and 'zips' them, i.e. creates a tuple of the two values 
// The default values are passed in because if one array is smaller than the other, 
// there needs to be a default value
template <typename T, typename S>
auto zip(std::vector<T> vectorT, std::vector<S> vectorS, T defaultT, S defaultS) {
	std::vector<std::tuple<T, S>> result;
   
	for (int i = 0; i < std::max(vectorT.size(), vectorS.size()); i++) {
		// subtract 1 because size is not 0-indexed
		if (vectorS.size() - 1 < i) {
			result.push_back(std::make_tuple(vectorT.at(i), defaultS));
		} else if (vectorT.size() - 1 < i) {
			result.push_back(std::make_tuple(defaultT, vectorS.at(i)));
		} else {
			result.push_back(std::make_tuple(vectorT.at(i), vectorS.at(i)));
		}
	}
   
	return result;
}

#endif

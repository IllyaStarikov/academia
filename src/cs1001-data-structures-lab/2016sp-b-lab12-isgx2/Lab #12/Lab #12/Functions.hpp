//
//  Functions.hpp
//  Lab #12
//
//  Created by Illya Starikov on 4/18/16.
//  Copyright © 2016 Illya Starikov. All rights reserved.
//

#ifndef Functions_hpp
#define Functions_hpp

#include <iostream>
#include <vector>
#include <map>
#include <tuple>

using namespace std;

map<string, tuple<int,int,int>> makePhonebook(const string filename);
std::string substring(std::string string, std::string delimeter, bool afterDelimeter);

#endif /* Functions_hpp */

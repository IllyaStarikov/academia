//
//  functions.h
//  undergrad-research
//
//  Created by Illya Starikov on 01/02/18.
//  Copyright 2018. Illya Starikov. All rights reserved.
//

#ifndef functions_h
#define functions_h

#include <iostream>

#include <fstream>
#include <sstream>

#include <boost/regex.hpp>
#include <boost/algorithm/string/replace.hpp>

#include <regex>

#include <vector>
#include <algorithm>
#include <iterator>


std::string getInput(std::string filename);
std::vector<std::string> split(std::string someString, std::string delimiter);

std::string insertInjectionCallsInMain(std::string program);
std::string insertHeader(std::string program);
std::string insertInjectionCalls(std::string program);
std::string replaceWhileLoops(std::string program);
std::string replaceForLoops(std::string program);

#endif /* functions_h */


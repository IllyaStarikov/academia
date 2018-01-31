//
//  functions.h
//  cs5201 - Numerical Modeling
//
//  Created by Illya Starikov on 01/29/18.
//  Copyright 2018. Illya Starikov. All rights reserved.
//

#ifndef functions_h
#define functions_h

#include <fstream>
#include <iostream>
#include <experimental/filesystem>

namespace filesystem = std::experimental::filesystem;

bool enoughParametersPassed(const int argc);
void displayErrorAndQuit(const std::string output);

std::vector<std::string> split(const std::string someString, const char delimiter);
int stringToInt(const std::string someString);
double stringToDouble(const std::string someString);

std::vector<std::pair<double, double>> parseFileContents(const std::string filename);
bool fileExists(const std::string filename);

std::string readFile(filesystem::path path);


#endif /* functions_h */


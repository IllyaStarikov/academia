//
//  functions.h
//  src
//
//  Illya Starikov, Section 1A, 18183141
//  cs5211 – Object Oriented Numerical Modeling
//

/** @file */

#ifndef functions_h
#define functions_h

#include "../lib/eigen.h"

#include <experimental/filesystem>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <type_traits>
#include <typeinfo>
#include <vector>
#include <algorithm>

namespace filesystem = std::experimental::filesystem;

void ensureEnoughArguments(const int argc);
void displayErrorAndQuit(const std::string& output);

int stringToInt(const std::string& someString);
double stringToDouble(const std::string& someString);

std::vector<std::string> split(const std::string& someString, const char delimiter);
bool fileExists(const std::string& filename);
std::string readFile(const filesystem::path& path);
std::string readInputFile(const std::string& filename);

std::pair<SymmetricMatrix<double>, Vector<double>> parseFileContents(const std::string& fileContents);

#endif /* functions_h */


//
//  Functions.cpp
//  Lab #12
//
//  Created by Illya Starikov on 4/18/16.
//  Copyright © 2016 Illya Starikov. All rights reserved.
//

#include "Functions.hpp"

#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>

using Phonebook = map<string, tuple<int,int,int>>;

Phonebook makePhonebook(const string filename) {
    ifstream readin;
    int number1, number2, number3, i = 0;
    readin.open(filename.c_str());
    
    auto toReturn = map<string, tuple<int,int,int>>();
    
    string line, name = "";
    
    while (!readin.eof()) {
        getline(readin, line);
    
        // Append characters to name until a number is reacher
        while (!isnumber(line[i])) {
            name += line[i++];
        }
        
        name.pop_back(); // I get the space before the number
        line.erase(0, i); // Erase name form original string
        
        // Get relevant data
        number1 = stoi(substring(line, " ", false));
        line = substring(line, " ", true);
        
        number2 = stoi(substring(line, " ", false));
        line = substring(line, " ", true);
        
        number3 = stoi(substring(line, " ", false));
        line = substring(line, " ", true);
        
        toReturn[name] = make_tuple(number1, number2, number3);
        name.clear();
        i = 0;
    }
    
    return toReturn;
}

std::string substring(std::string string, std::string delimeter, bool afterDelimeter) {
    int position = static_cast<int>(string.find(delimeter));
    std::string substring = afterDelimeter ? string.substr(position + 1) : string.substr(0, position);
    
    return substring;
}
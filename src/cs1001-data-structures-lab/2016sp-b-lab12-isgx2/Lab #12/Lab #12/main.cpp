//
//  main.cpp
//  Lab #12
//
//  Created by Illya Starikov on 4/18/16.
//  Copyright © 2016 Illya Starikov. All rights reserved.
//

#include <iostream>
#include "Functions.hpp"

int main(int argc, const char * argv[]) {    
    auto filename = std::string("phonebook.txt");
    auto phonebook = makePhonebook(filename);
    
    if (argc == 1) {
        for (auto const & nameNumber : phonebook) {
            std::cout << nameNumber.first << ": " << get<0>(nameNumber.second) << get<1>(nameNumber.second) << get<2>(nameNumber.second) << std::endl;
        }
    } else {
        auto name = std::string(argv[2]);
        cout << std::get<0>(phonebook[name]) << "-"<< std::get<1>(phonebook[name]) << "-" << std::get<2>(phonebook[name]) << std::endl;
    }
}

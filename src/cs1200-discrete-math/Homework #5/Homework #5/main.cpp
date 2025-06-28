//  COMP SCI 1200 Section B FS2015 Assignment
//
//  main.cpp
//  Homework #5
//
//  Created by Illya Starikov on 11/14/15.
//  Copyright © 2015 Illya Starikov. All rights reserved.
//

#include <iostream>
#include <stdlib.h> // srand, rand
#include <time.h>   // Time

#include "MontyHall.hpp"

int main() {
    srand(static_cast<unsigned>(time(NULL)));

    MontyHallGame theGame;
    theGame.play();
}

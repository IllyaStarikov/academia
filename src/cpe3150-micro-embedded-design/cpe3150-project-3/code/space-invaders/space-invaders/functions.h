//
//  functions.h
//  space-invaders
//
//  Created by Illya Starikov on 11/10/16.
//  Copyright © 2016 Illya Starikov. All rights reserved.
//

#ifndef functions_h
#define functions_h

#include "game.h"
#include "point.h"
#include "constants.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ncurses.h>

// INITS / DEINITS
void printDisk();
void initGame(Game* game);


// DRAWING LOGIC
void createHeader(Game *game, char** headerLine);
void createShooter(const CartesianPoint center, Game *game, char*** shooterAscii);
void createGameboard(Game *game, char*** aliensAndShields, const bool stateOne, const bool updateShot);
void draw(const Game *game, char** header, char*** gameboard, char*** footer);

// GAME LOGIC
void dealloc(const Game* game, char* header, char** gameboard, char** footer);

// GAME MAINTENANCE FUNCTIONS
bool inBoundsOfGame(const Game* game, const CartesianPoint* point);
bool inBounds(const CartesianPoint* point, const unsigned char maxX, const unsigned char maxY);


// MAINTENANCE FUNCTIONS
int power(int base, int exponent);
// It's gonna be legened..
void waitForIt(unsigned char seconds); 
// ..ary! Lengendary.
void numberToCharacter(const unsigned char number, char* string);
char* numberToString(int number, char *string);
unsigned char stringHeight(char** string);

#endif /* functions_h */

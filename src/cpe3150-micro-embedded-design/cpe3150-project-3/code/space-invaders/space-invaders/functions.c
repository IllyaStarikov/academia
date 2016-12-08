//
//  functions.c
//  space-invaders
//
//  Created by Illya Starikov on 11/10/16.
//  Copyright © 2016 Illya Starikov. All rights reserved.
//

#include "functions.h"
#include "constants.h"
#include "game.h"
#include "point.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ncurses.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <time.h>


void printDisk() {
    printw("     ___                     ___          ___                 ___          ___          ___     \n");
    printw("    /\\  \\         ___       /\\  \\        /\\  \\               /\\  \\        /\\__\\        /\\  \\    \n");
    printw("   /::\\  \\       /\\  \\     /::\\  \\      /::\\  \\              \\:\\  \\      /:/ _/_      /::\\  \\   \n");
    printw("  /:/\\:\\  \\      \\:\\  \\   /:/\\ \\  \\    /:/\\:\\  \\              \\:\\  \\    /:/ /\\__\\    /:/\\:\\  \\  \n");
    printw(" /:/  \\:\\__\\     /::\\__\\ _\\:\\~\\ \\  \\  /:/  \\:\\  \\             /::\\  \\  /:/ /:/ _/_  /:/  \\:\\  \\ \n");
    printw("/:/__/ \\:|__| __/:/\\/__//\\ \\:\\ \\ \\__\\/:/__/ \\:\\__\\           /:/\\:\\__\\/:/_/:/ /\\__\\/:/__/ \\:\\__\\\n");
    printw("\\:\\  \\ /:/  //\\/:/  /   \\:\\ \\:\\ \\/__/\\:\\  \\  \\/__/          /:/  \\/__/\\:\\/:/ /:/  /\\:\\  \\ /:/  /\n");
    printw(" \\:\\  /:/  / \\::/__/     \\:\\ \\:\\__\\   \\:\\  \\               /:/  /      \\::/_/:/  /  \\:\\  /:/  / \n");
    printw("  \\:\\/:/  /   \\:\\__\\      \\:\\/:/  /    \\:\\  \\              \\/__/        \\:\\/:/  /    \\:\\/:/  /  \n");
    printw("   \\::/__/     \\/__/       \\::/  /      \\:\\__\\                           \\::/  /      \\::/  /   \n");
    printw("    ~~                      \\/__/        \\/__/                            \\/__/        \\/__/    \n");
    refresh();
}

void initGame(Game* game) {
    getmaxyx(stdscr, game -> height, game -> width);
    
    game -> level = 3;
    game -> lives = 3;
    game -> score = 0;
    
    game -> headerNeedsUpdate = true;
    game -> gunnerNeedsUpdate = true;
    
    game -> shelterNeedsRedraw = true;
    game -> freeSpaceNeedsRedraw = true;
    
    game -> gunner.playerDidShoot = false;
}


void createHeader(Game *game, char** headerLine) {
    unsigned char workingSize = game -> width; // working size is to keep track how much room is left for the header line
    char tempString[2];
    
    if (*headerLine == NULL) {
        *headerLine = (char*)malloc(game -> width * sizeof(char));
    }
    
    // It's not that expensive to update all of these (well, relatively)
    // So we can just reinstatiate the entire header from scratch
    if (game -> headerNeedsUpdate) {
        if (workingSize > strlen(NAME)) {
            strcpy(*headerLine, NAME);
            workingSize -= strlen(NAME);
        }
        
        
        if (workingSize > strlen(LIVES) + sizeof(tempString)) {
            strcat(*headerLine, LIVES);
            strcat(*headerLine, numberToString(game -> lives, tempString));
            workingSize -= strlen(NAME);
        }
        
        if (workingSize > strlen(SCORE) + sizeof(tempString)) {
            strcat(*headerLine, SCORE);
            strcat(*headerLine, numberToString(game -> score, tempString));
            workingSize -= strlen(NAME);
        }
        
        game -> headerNeedsUpdate = false;
    }
}

// Note: the center actually ignores height. ¯\_(ツ)_/¯
void createShooter(const CartesianPoint center, Game *game, char*** shooterAscii) {
    const unsigned char width = sizeof(*gunner);
    const unsigned char height = sizeof(gunner) / width; //works like stringHeight, but can't use it because incompatible pointers
    
    int i, j, shooterCounter;
    
    if (*shooterAscii == NULL) {
        *shooterAscii = (char**)malloc(height * sizeof(char*));
        for (i = 0; i < height; i++) {
            (*shooterAscii)[i] = (char*)malloc(game -> width * sizeof(char));
        }
    }
    
    if (game -> gunnerNeedsUpdate) {
        
        for (j = 0; j < height; j++) {
            shooterCounter = 0;
            for (i = 0; i < game -> width - 1; i++) {
                
                // the if determines if the shooter should be drawn, and it works like so:
                // if it's in the range of 1/2width on either side of the center, then it's a match
                // -1 because used sizeof for width calculation and that includes terminating character
                if (i + strlen(*gunner)/2.0 >= center.x && i - strlen(*gunner)/2.0 <= center.x ) {
                    (*shooterAscii)[j][i] = gunner[j][shooterCounter];
                    shooterCounter++;
                } else {
                    (*shooterAscii)[j][i] = ' ';
                }
            }
            (*shooterAscii)[j][i] = '\0';
        }
        
        game -> gunnerNeedsUpdate = false;
    }
}

void createGameboard(Game *game, char*** aliensAndShields, const bool stateOne, const bool updateShot) {
    unsigned char numberOfAliens;
    const unsigned char shelterHeight = sizeof(shelter)/sizeof(*shelter);
    const unsigned char height = game -> height - 1 - sizeof(gunner)/sizeof(*gunner); // read string height to figure out how this works
    // we subtract 1 for the header string and the gunner height becuase this is this the "working canvas"
    static const unsigned char heightOfAverageAlien = sizeof(smallInvaderOne)/sizeof(smallInvaderOne[0]); // static because we assume height to never change
    unsigned char i, j, correctionFactor;
    static int alienDeleteCount = 1;
    
    unsigned char leftBounds = game -> gunner.alienHitLocation.x - game -> gunner.alienHitLocation.x % strlen(*smallInvaderOne) + 1, rightBounds =  game -> gunner.alienHitLocation.x - game -> gunner.alienHitLocation.x % strlen(*smallInvaderOne) + strlen(*smallInvaderOne) - 1;
    unsigned char bottomBound = game -> gunner.alienHitLocation.y - 1;
    unsigned char topBound = bottomBound + heightOfAverageAlien;
    
    
    
    if (game -> currentNumberOfAliens == 0) {
        game -> currentNumberOfAliens = game -> level;
        numberOfAliens = game -> level;
    } else {
        numberOfAliens = game -> currentNumberOfAliens;
    }
    
    if (*aliensAndShields == NULL) {
        *aliensAndShields = (char**)malloc(height * sizeof(char*));
        for (i = 0; i < height; i++) {
            (*aliensAndShields)[i] = (char*)malloc(game -> width * sizeof(char));
        }
    }
    
    if (game ->  shelterNeedsRedraw) {
        // Draw Sheilds First
        // i = row, j = column
        // We start at the lowermost part of the gameboard to start drawing the shields (i.e. height -1)
        // And continue until we get to the top of where the shelter be, i.e. the previous height - shetler height
        for (i = height - 1; i > height - shelterHeight - 1; i--) {
            // We subtracted game -> width % shelter because we don't want to draw half a shelter
            for (j = 0; j < game -> width - 1 - (game -> width % strlen(*shelter)); j++) {
                // The second accessor (i.e. shelter[i][x]) just mods the shelter length so we can repitively
                // draw shelters
                (*aliensAndShields)[i][j] = shelter[(i - height + shelterHeight)][j % strlen(*shelter)];
            }
            (*aliensAndShields)[i][j] = '\0';
        }
        game -> shelterNeedsRedraw = false;
    }
    
    // Now the aliens
    
    // We start at the height and draw the same row of aliens as there are rows
    // However, the aliens are typically 2 rows, so have to multiply that by the alien height
    // We assume all alien heights to be the same
    
    // However, the widths don't have to be the same, but we use a heuristic of the small invaders
    // to truncate the aliens
    for (i = 0; i < game -> level * heightOfAverageAlien; i++) {
        for (j = 0; j < game -> width - 1 - (game -> width % strlen(*smallInvaderOne)); j++) {
            // We need to draw different rows of aliens
            // Now, we need to draw different aliens, depedending on the rows
            // So, we basically 'undo' the stretching we did above (on i), then shift (because we can't divide by 0 and dividing by 1 would always return true)
            // Then we mode by 3 because that's the number aliens, and we compare to a number I put there because the returned numbers baffle me.
            if (j + 1 < game -> width - 1 && (*aliensAndShields)[i][j] == ' ') {
                (*aliensAndShields)[i][j] = ' ';
            } else if (game -> gunner.playerHitAlien == true && j >= leftBounds && j <= rightBounds && i <= topBound && i >= bottomBound) {
                if (alienDeleteCount++ % 250 % 500 == 0) {
                (*aliensAndShields)[i][j] = ' ';
                if (j > rightBounds && i > heightOfAverageAlien) {
                    game -> gunner.playerHitAlien = false;
                    i = 0;
                }
                }
            } else {
                if ((i/heightOfAverageAlien + 2) % 3  == 2) {
                    (*aliensAndShields)[i][j] =  stateOne ? smallInvaderOne[i % heightOfAverageAlien][j % strlen(*smallInvaderOne)] : smallInvaderTwo[i % heightOfAverageAlien][j % strlen(*smallInvaderTwo)];
                } else if ((i/heightOfAverageAlien + 2) % 3 == 0) {
                    (*aliensAndShields)[i][j] =  stateOne ? mediumInvaderOne[i % heightOfAverageAlien][j % strlen(*mediumInvaderOne)] : mediumInvaderTwo[i % heightOfAverageAlien][j % strlen(*mediumInvaderTwo)];
                } else {
                    (*aliensAndShields)[i][j] =  stateOne ? largeInvaderOne[i % heightOfAverageAlien][j % strlen(*largeInvaderOne)] : largeInvaderTwo[i % heightOfAverageAlien][j % strlen(*largeInvaderTwo)];
                }
            }
            
        }
        (*aliensAndShields)[i][j] = '\0';
        
    }
    
    
    // This is just to draw fill in the rest of the pace
    if (game -> freeSpaceNeedsRedraw) {
        for (i = game -> level * heightOfAverageAlien; i < height - shelterHeight; i++) {
            for (j = 0; j < game -> width - 1; j++) {
                (*aliensAndShields)[i][j] = ' ';
            }
            (*aliensAndShields)[i][j] = '\0';
        }
        
        game -> freeSpaceNeedsRedraw = false;
    }
    
    
    // Next we check to see if the player did shoot and if he did, we draw accordingly
    if (game -> gunner.playerDidShoot) {
        if (!inBounds(&game -> gunner.playerShot, game -> width, height + 1 ) || game -> gunner.playerShot.y == 0) {
            // First to check to see if we're in bounds
            game -> gunner.playerDidShoot = false;
        } else if (game -> gunner.playerShot.y >= height - shelterHeight - 1 && (*aliensAndShields)[game -> gunner.playerShot.y - 1][game -> gunner.playerShot.x] != ' ' && (*aliensAndShields)[game -> gunner.playerShot.y - 1][game -> gunner.playerShot.x] != SHOT) {
            // Next check to see if we hit shelter. If we did,r stop the shooting at this spot and remove shelter
            game -> gunner.playerDidShoot = false;
            // Undo what we did, meaning we replace the shot with the ' ' character and proceed to place it higher
            // We have to check to make sure this is still in bounds (this only really matter for the initial shot)
            if (inBounds(&game -> gunner.playerShot, game -> width, height)) {
                (*aliensAndShields)[game -> gunner.playerShot.y][game -> gunner.playerShot.x] = ' ';
            }
            (*aliensAndShields)[game -> gunner.playerShot.y - 1][game -> gunner.playerShot.x] = ' ';
        } else if ((*aliensAndShields)[game -> gunner.playerShot.y - 1][game -> gunner.playerShot.x] != ' ' && (*aliensAndShields)[game -> gunner.playerShot.y - 1][game -> gunner.playerShot.x] != SHOT) {
            // Check to see if the alien is hit. If it is, we set the flag that there is a shot that hit
            game -> gunner.playerHitAlien = true;
            // We update the score based on where the shot hit (for the score) and that it needs to be updated
            // Along with some other flags
            game -> score += 50;
            game -> gunner.alienCounter = 1;
            game -> headerNeedsUpdate = true;
            game -> gunner.playerDidShoot = false;
            game -> gunner.alienHitLocation.y = game -> gunner.playerShot.y - 1;
            game -> gunner.alienHitLocation.x = game -> gunner.playerShot.x;
            
            alienDeleteCount++;
            
            // Undo what we did
            if (inBounds(&game -> gunner.playerShot, game -> width, height)) {
                (*aliensAndShields)[game -> gunner.playerShot.y][game -> gunner.playerShot.x] = ' ';
            }
            
            // finally redraw alien
            if ((*aliensAndShields)[game -> gunner.playerShot.y][game -> gunner.alienHitLocation.x - 1] != ' ' || (*aliensAndShields)[game -> gunner.playerShot.y][game -> gunner.alienHitLocation.x + 1] != ' ') {
                correctionFactor = 1;
            } else {
                correctionFactor = 2;
            }
            
            for (i = 0; i < strlen(*smallInvaderOne); i++) {
                for (j = 0; j < heightOfAverageAlien; j++) {
                    (*aliensAndShields)[game -> gunner.playerShot.y + j - correctionFactor][game -> gunner.alienHitLocation.x - game -> gunner.alienHitLocation.x % strlen(*smallInvaderOne) + i] = alienExplode[j][i];
                }
            }
        } else {
            // exact reasoning as the above statement
            if (inBounds(&game -> gunner.playerShot, game -> width, height)) {
                (*aliensAndShields)[game -> gunner.playerShot.y][game -> gunner.playerShot.x] = ' ';
            }
            (*aliensAndShields)[game -> gunner.playerShot.y - 1][game -> gunner.playerShot.x] = SHOT;
        }
        
        // because we have already drawn the player's shot, we need to update it for the next frame
        // We subtract because (0,0 is the top left)
        if (updateShot) {
            (game -> gunner.playerShot.y)--;
        }
    }
    
    
}

void draw(const Game *game, char** header, char*** gameboard, char*** footer) {
    unsigned char i;
    clear();
    
    printw("%s\n", *header);
    
    // This is really ugly.. but basically we start with the game height and then subt
    for (i = 0; i < game -> height - 1 - sizeof(gunner)/sizeof(*gunner); i++) {
        printw("%s\n", (*gameboard)[i]);
    }
    
    // no idea why this doesn't return 2, but it doesn't
    // so +1
    for (i = 0; i < sizeof(*footer)/sizeof(*footer[0]) + 1; i++) {
        printw("%s\n", (*footer)[i]);
    }
    
    refresh();
}

void dealloc(const Game* game, char* header, char** gameboard, char** footer) {
    unsigned char i;
    
    free(header);
    
    for (i = 0; i < sizeof(gunner) / sizeof(*gunner); i++) {
        free(footer[i]);
    }
    free(footer);
    
    for (i = 0; i < game -> height - 1 - sizeof(gunner)/sizeof(*gunner); i++) {
        free(gameboard[i]);
    }
    
    free(gameboard);
}

bool inBoundsOfGame(const Game* game, const CartesianPoint* point) {
    return point -> x >= 0 && point -> x < game -> width // the x is in bounds
    && point -> y >= 0 && point -> y < game -> height; // and the y is in bounds
}

bool inBounds(const CartesianPoint* point, const unsigned char maxX, const unsigned char maxY) {
    return point -> x >= 0 && point -> x < maxX // the x is in bounds
    && point -> y >= 0 && point -> y < maxY; // and the y is in bounds
}

int power(int base, int exponent) {
    if (exponent == 0) {
        return 1;
    }
    
    return base * power(base, exponent - 1);
}

void waitForIt(unsigned char seconds) {
    unsigned int retTime = (unsigned int)time(0) + (unsigned int)seconds;
    while (time(0) < retTime);
}

char* numberToString(int number, char *string) {
    if (string == NULL) {
        return NULL;
    }
    
    sprintf(string, "%d", number);
    return string;
}


unsigned char stringHeight(char** string) {
    // so sizeof returns effectively the area
    // and sizeof returns the width
    // area/width = height. Woo!
    if (string == NULL) {
        return 0; // To prevent division by zero
    }
    return sizeof(string)/sizeof(string[0]);
}

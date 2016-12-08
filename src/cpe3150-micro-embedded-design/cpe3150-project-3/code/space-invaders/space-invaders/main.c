//
//  main.c
//  space-invaders
//
//  Created by Illya Starikov on 11/10/16.
//  Copyright © 2016 Illya Starikov. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

#include "functions.h"
#include "game.h"
#include "constants.h"
#include "point.h"

static const unsigned int STATE_CHANGE_SHOT_MULTIPLIER = 950;

int main(int argc, const char * argv[]) {
    Game game;
    
    char* header = NULL;
    char** footer = NULL, **gameboard = NULL;
    unsigned int i = 0;
    bool stateOfAliens = false, stateOfShot = false;
    
    initscr();
    nodelay(stdscr, TRUE);
    noecho();
    cbreak();
    
    keypad(stdscr, TRUE);
    
    initGame(&game);
    
    game.gunner.center.x = game.width / 2;
    game.gunner.center.y = game.height - 1;
    
//    printDisk();
//    while (getch() != 's');
    
    do {
        switch (getch()) {
            case KEY_LEFT:
                if (inBoundsOfGame(&game, &game.gunner.center)) {
                    game.gunner.center.x--;
                    game.gunnerNeedsUpdate = true;
                }
                break;
                
            case KEY_RIGHT:
                if (inBoundsOfGame(&game, &game.gunner.center)) {
                    game.gunner.center.x++;
                    game.gunnerNeedsUpdate = true;
                }
                break;
                
            case ' ':
                if (!game.gunner.playerDidShoot) {
                    game.gunner.playerDidShoot = true;
                    game.gunner.playerShot = game.gunner.center;
                    game.gunner.playerShot.y -= 2; // we subtract four because zero indexed based and the height of the gunner ship
                }
                break;
                
            case 'q':
                endwin();
                dealloc(&game, header, gameboard, footer);
                exit(0);
                break;
                
                
            default:
                createHeader(&game, &header);
                createShooter(game.gunner.center, &game, &footer);
                createGameboard(&game, &gameboard, stateOfAliens, stateOfShot);
                
                draw(&game, &header, &gameboard, &footer);
                
                break;
        }
        
        
        i++;
        
        // For the state of the aliens, we want to alternate with equal iterations
        if (i % STATE_CHANGE_ALIENS == 0) {
            // You would think the compilment would work (~), but it doesn't
            stateOfAliens = stateOfAliens ? false : true;
        }
        
        // For the state of the shot, we only want to update ~every someodd iterations
        if (i % 40 == 0) {
            stateOfShot = true;
        } else {
            stateOfShot = false;
        }
        
        

    } while (true);
    
    
}

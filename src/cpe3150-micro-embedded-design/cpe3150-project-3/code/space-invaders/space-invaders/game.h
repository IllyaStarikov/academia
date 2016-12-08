 //
//  game.h
//  space-invaders
//
//  Created by Illya Starikov on 11/10/16.
//  Copyright © 2016 Illya Starikov. All rights reserved.
//

#ifndef game_h
#define game_h

#include "point.h"
#include "constants.h"

typedef struct Shooter {
    _Bool playerDidShoot;
    _Bool playerHitAlien;
    
    unsigned char alienCounter;
    
    CartesianPoint alienHitLocation;
    CartesianPoint playerShot;
    CartesianPoint center;
} Shooter;

typedef struct Game {
    Shooter gunner;
    
    unsigned char lives, level, currentNumberOfAliens;
    int width, height, score;
    
    _Bool headerNeedsUpdate, gunnerNeedsUpdate;
    _Bool shelterNeedsRedraw, freeSpaceNeedsRedraw;
} Game;


#endif /* game_h */

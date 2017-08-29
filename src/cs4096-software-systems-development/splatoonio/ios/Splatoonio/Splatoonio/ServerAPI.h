//
//  ServerAPI.h
//  Splatoonio
//
//  Created by Adam Evans on 8/24/17.
//  Copyright © 2017 Kijug Software. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "GameMap.h"
#import "Game.h"


#define SERVER_DEFAULT_LOBBY		-1


@interface ServerAPI : NSObject

// GET
+ (GameMap*)currentMap;
+ (GameMap*)mapForLocation:(CLLocation*)location;
+ (Game*)currentGame;
+ (Player*)addPlayerToGame:(Game*)game;
+ (Player*)addPlayerToGame:(Game*)game fromLobby:(int)lobby;

// POST
+ (void)updateLocation:(PathPoint*)point inGame:(Game*)game;

@end

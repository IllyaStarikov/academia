//
//  Game.h
//  Splatoonio
//
//  Created by Adam Evans on 8/24/17.
//  Copyright © 2017 Kijug Software. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "GameMap.h"
#import "Player.h"
#import "Item.h"


@interface Game : NSObject

@property (readwrite) int gameID;
@property (readwrite) int numPlayers;
@property (readwrite) Player* me;
@property (readwrite) GameMap* map;
@property (readwrite) NSMutableArray<Player*>* players;
@property (readwrite) NSMutableArray<Item*>* items;

@end

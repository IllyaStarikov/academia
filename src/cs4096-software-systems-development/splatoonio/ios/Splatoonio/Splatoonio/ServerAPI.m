//
//  ServerAPI.m
//  Splatoonio
//
//  Created by Adam Evans on 8/24/17.
//  Copyright © 2017 Kijug Software. All rights reserved.
//

#import "ServerAPI.h"


@implementation ServerAPI


// =================================================================================
#pragma mark -						Information Retrieval
// =================================================================================

+ (GameMap*)currentMap
{
	// TODO: do actual server stuff
	GameMap* map = [[GameMap alloc] init];
	map.boundingRegion = MKCoordinateRegionMakeWithDistance(CLLocationCoordinate2DMake(37.953265, -91.77260), 100, 70);
	
	return map;
}

// =================================================================================

+ (GameMap*)mapForLocation:(CLLocation*)location
{
	// TODO: do actual server stuff
	GameMap* map = [ServerAPI currentMap];
	return map;
}

// =================================================================================

+ (Game*)currentGame
{
	// TODO: do actual server stuff
	Game* game = [[Game alloc] init];
	game.map = [ServerAPI currentMap];
	return game;
}

// =================================================================================

+ (Player*)addPlayerToGame:(Game*)game
{
	return [ServerAPI addPlayerToGame:game fromLobby:SERVER_DEFAULT_LOBBY];
}

// =================================================================================
// Returns the new player just added
+ (Player*)addPlayerToGame:(Game*)game fromLobby:(int)lobby
{
	// TODO: do actual server stuff
	Player* player = [[Player alloc] init];
	player.name = [NSString stringWithFormat:@"player%d", arc4random() % 100];
	
	game.numPlayers++;
	
	return player;
}

// =================================================================================
#pragma mark -						Information Posting
// =================================================================================

+ (void)updateLocation:(PathPoint*)point inGame:(Game*)game
{
	// TODO: send the point to the server to update where we are
}

// =================================================================================
// =================================================================================


@end











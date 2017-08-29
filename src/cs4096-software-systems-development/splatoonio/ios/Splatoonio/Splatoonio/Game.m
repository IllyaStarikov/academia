//
//  Game.m
//  Splatoonio
//
//  Created by Adam Evans on 8/24/17.
//  Copyright © 2017 Kijug Software. All rights reserved.
//

#import "Game.h"


#define GAME_ID_NONE		-1


@implementation Game


@synthesize gameID;
@synthesize numPlayers;
@synthesize me;
@synthesize map;
@synthesize players;
@synthesize items;


// =================================================================================
#pragma mark -						Initialization
// =================================================================================

- (id)init
{
	self = [super init];
	
	if (self != nil)
	{
		gameID = GAME_ID_NONE;
		numPlayers = 0;
		me = nil;
		map = nil;
		players = [[NSMutableArray<Player*> alloc] init];
		items = [[NSMutableArray<Item*> alloc] init];
	}
	
	return self;
}

// =================================================================================

- (void)movePlayer:(Player*)player toPoint:(CLLocation*)loc
{
	PathPoint* point = [[PathPoint alloc] init];
	point.location = loc.coordinate;
	point.radius = player.brushRadius;
	
	[player.path addObject:point];
}

// =================================================================================

@end

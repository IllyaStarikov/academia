//
//  Player.m
//  Splatoonio
//
//  Created by Adam Evans on 8/25/17.
//  Copyright © 2017 Kijug Software. All rights reserved.
//

#import "Player.h"


#define PLAYER_ID_NONE			-1
#define PLAYER_START_RADIUS		2.0		// 2 meters seems like a good starting radius (4 meter wide circle)


@implementation Player


@synthesize playerID;
@synthesize teamColor;
@synthesize brushRadius;
@synthesize name;
@synthesize path;


// =================================================================================
#pragma mark -						Initializers
// =================================================================================

- (id)init
{
	self = [super init];
	
	if (self != nil)
	{
		playerID = PLAYER_ID_NONE;
		teamColor = TEAM_RED;
		brushRadius = PLAYER_START_RADIUS;
		name = @"ERROR: No name";
		path = [[NSMutableArray<PathPoint*> alloc] init];
	}
	
	return self;
}

// =================================================================================
// =================================================================================
// =================================================================================




@end

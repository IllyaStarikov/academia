//
//  Player.h
//  Splatoonio
//
//  Created by Adam Evans on 8/25/17.
//  Copyright © 2017 Kijug Software. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "PathPoint.h"


#define PLAYER_MAX_ITEMS		5


typedef enum
{
	TEAM_RED = 0,
	TEAM_GREEN,
	TEAM_BLUE,
	
	TEAM_COUNT
} TeamColor;


@interface Player : NSObject

@property (readwrite) int playerID;
@property (readwrite) float brushRadius;		// in meters
@property (readwrite) TeamColor teamColor;
@property (readwrite) NSString* name;
@property (readwrite) NSMutableArray<PathPoint*>* path;

@end

//
//  GameMap.m
//  Splatoonio
//
//  Created by Adam Evans on 8/24/17.
//  Copyright © 2017 Kijug Software. All rights reserved.
//

#import "GameMap.h"


@implementation GameMap


@synthesize boundingRegion;


// =================================================================================
#pragma mark -						Initialization
// =================================================================================

- (id)init
{
	self = [super init];
	
	if (self != nil)
	{
		boundingRegion = MKCoordinateRegionMakeWithDistance(CLLocationCoordinate2DMake(0, 0), 0, 0);
	}
	
	return self;
}

// =================================================================================



@end

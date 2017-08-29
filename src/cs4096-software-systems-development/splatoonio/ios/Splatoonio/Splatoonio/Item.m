//
//  Item.m
//  Splatoonio
//
//  Created by Adam Evans on 8/25/17.
//  Copyright © 2017 Kijug Software. All rights reserved.
//

#import "Item.h"


@implementation Item


@synthesize type;
@synthesize location;


// =================================================================================
#pragma mark -						Initializers
// =================================================================================

- (id)init
{
	self = [super init];
	
	if (self != nil)
	{
		type = ITEM_TYPE_NONE;
		location = CLLocationCoordinate2DMake(0, 0);
	}
	
	return self;
}

// =================================================================================

- (NSString*)name
{
	return [Item nameForItemOfType:type];
}

// =================================================================================
#pragma mark -					Item Information Accessors
// =================================================================================

+ (UIImage*)imageForItemOfType:(ItemType)type
{
	switch (type)
	{
		case ITEM_TYPE_BOMB:	return [UIImage imageNamed:@"itemIconBomb.png"];
		default:				return [UIImage imageNamed:@"itemIconGeneric.png"];
	}
}

// =================================================================================

+ (NSString*)nameForItemOfType:(ItemType)type
{
	switch (type)
	{
		case ITEM_TYPE_BOMB:	return @"Bomb";
		default:				return @"Generic Item";
	}
}

// =================================================================================

@end

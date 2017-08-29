//
//  Item.h
//  Splatoonio
//
//  Created by Adam Evans on 8/25/17.
//  Copyright © 2017 Kijug Software. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <CoreLocation/CoreLocation.h>


typedef enum
{
	ITEM_TYPE_NONE = -1,
	
	ITEM_TYPE_GENERIC = 0,
	ITEM_TYPE_BOMB,
	
	ITEM_TYPE_COUNT,
} ItemType;


@interface Item : NSObject

@property (readwrite) ItemType type;
@property (readwrite) CLLocationCoordinate2D location;
@property (readonly, getter=name) NSString* name;

+ (UIImage*)imageForItemOfType:(ItemType)type;

@end

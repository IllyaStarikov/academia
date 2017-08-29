//
//  PathPoint.h
//  Splatoonio
//
//  Created by Adam Evans on 8/25/17.
//  Copyright © 2017 Kijug Software. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>


@interface PathPoint : NSObject


@property (readwrite) CLLocationCoordinate2D location;		// lat/lon in degrees
@property (readwrite) float radius;							// in meters


@end

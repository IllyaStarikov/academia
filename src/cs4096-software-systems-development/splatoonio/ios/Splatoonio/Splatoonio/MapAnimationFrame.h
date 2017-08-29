//
//  MapAnimationFrame.h
//  Splatoonio
//
//  Created by Adam Evans on 8/27/17.
//  Copyright © 2017 Kijug Software. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>

@interface MapAnimationFrame : NSObject

@property (readwrite) CLLocationCoordinate2D location;
@property (readwrite) CLLocationDegrees heading;

@end

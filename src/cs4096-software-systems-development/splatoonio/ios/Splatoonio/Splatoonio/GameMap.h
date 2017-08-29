//
//  GameMap.h
//  Splatoonio
//
//  Created by Adam Evans on 8/24/17.
//  Copyright © 2017 Kijug Software. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <MapKit/MapKit.h>


@interface GameMap : NSObject

@property (readwrite) MKCoordinateRegion boundingRegion;

@end

//
//  GPSManager.h
//  Splatoonio
//
//  Created by Adam Evans on 8/24/17.
//  Copyright © 2017 Kijug Software. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>


// =================================================================================

@protocol GPSManagerDelegate;

// =================================================================================

@interface GPSManager : NSObject <CLLocationManagerDelegate>
{
	// used to track how many times GPS has been turned on to turn off GPS only when all
	// turnOn() calls have had a corresponding turnOff() call
	int onCount;
	
	CLLocationManager* locationManager;
}

@property (readonly) CLLocation* prevLocation;
@property (readonly) CLLocation* currentLocation;
@property (readwrite) NSObject<GPSManagerDelegate>* delegate;

+ (GPSManager*)defaultManager;
- (void)turnOn;
- (void)turnOff;

@end

// =================================================================================

@protocol GPSManagerDelegate <NSObject>

- (void)locationUpdated:(CLLocation*)newLocation;

@end

// =================================================================================


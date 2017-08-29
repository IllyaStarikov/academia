//
//  GPSManager.m
//  Splatoonio
//
//  Created by Adam Evans on 8/24/17.
//  Copyright © 2017 Kijug Software. All rights reserved.
//

#import "GPSManager.h"


@implementation GPSManager


@synthesize prevLocation;
@synthesize currentLocation;
@synthesize delegate;


static GPSManager* instance;


// =================================================================================
#pragma mark -						Initiailization
// =================================================================================
// Uses singleton pattern
+ (GPSManager*)defaultManager
{
	if (instance == nil)
	{
		instance = [[GPSManager alloc] init];
	}
	
	return instance;
}

// =================================================================================
// You should never need to call this method directly. Use defaultManager() to grab the singleton instance
- (id)init
{
	self = [super init];
	
	if (self != nil)
	{
		onCount = 0;
		prevLocation = nil;
		currentLocation = nil;
		delegate = nil;
		
		locationManager = [[CLLocationManager alloc] init];
		locationManager.delegate = self;
		locationManager.desiredAccuracy = kCLLocationAccuracyBest;
		locationManager.distanceFilter = kCLDistanceFilterNone;		// update us if we move at least one meter from where we currently are
		locationManager.pausesLocationUpdatesAutomatically = NO;
		[locationManager requestWhenInUseAuthorization];
	}
	
	return self;
}

// =================================================================================
#pragma mark -						Normal Functions
// =================================================================================

- (void)turnOn
{
	[locationManager startUpdatingLocation];
	onCount++;
}

// =================================================================================

- (void)locationManager:(CLLocationManager *)manager didUpdateLocations:(NSArray<CLLocation *> *)locations
{
	// TODO: handle multiple location updates by using the associated timestamp (do deferred locations have different timestamps?)
	prevLocation = currentLocation;
	currentLocation = [locations objectAtIndex:[locations count] - 1];
	
	if (delegate != nil)
	{
		[delegate locationUpdated:currentLocation];
	}
}

// =================================================================================

- (void)locationManager:(CLLocationManager *)manager didFailWithError:(NSError *)error
{
	NSLog(@"ERROR: CLLocationManager.didFailWithError: %@", error.description);
}

// =================================================================================

- (void)turnOff
{
	onCount--;
	
	// turn off only if nobody is using it
	if (onCount == 0)
	{
		[locationManager stopUpdatingLocation];
	}
}

// =================================================================================


@end

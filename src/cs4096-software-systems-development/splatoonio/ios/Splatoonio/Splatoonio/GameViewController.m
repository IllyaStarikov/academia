//
//  GameViewController.m
//  Splatoonio
//
//  Created by Adam Evans on 8/24/17.
//  Copyright © 2017 Kijug Software. All rights reserved.
//

#import "GameViewController.h"
#import "MyUtilities.h"


#define ANIMATION_FPS		20
#define CAMERA_ALTITUDE		205


@implementation GameViewController


@synthesize game;


int count;


// =================================================================================
#pragma mark -						Fancy Graphics
// =================================================================================

- (void)locationUpdated:(CLLocation*)location
{
//	CLLocation* now = [GPSManager defaultManager].currentLocation;
//	CLLocation* old = [GPSManager defaultManager].prevLocation;
//	NSTimeInterval travelTime = [now.timestamp timeIntervalSinceDate:old.timestamp];
//	
	NSLog(@"location updated to %f, %f with speed=%f", location.coordinate.latitude, location.coordinate.longitude, location.speed);
////	MKCoordinateRegion region = MKCoordinateRegionMakeWithDistance(location.coordinate, 100, 70);
////	[mapView setRegion:region animated:YES];
//	
//	[mapView setCenterCoordinate:CLLocationCoordinate2DMake(now.coordinate.latitude, now.coordinate.longitude) animated:NO];
//	
//	// animate the change
//	int nframes = (int)(travelTime * ANIMATION_FPS);
//	latChange = (now.coordinate.latitude - old.coordinate.latitude) / nframes;
//	lonChange = (now.coordinate.longitude - old.coordinate.longitude) / nframes;
//	headingChange = now.course - old.course;
//	
//	if (headingChange >= 180)	headingChange -= 360;
//	if (headingChange < -180)	headingChange += 360;
//	
//	headingChange /= nframes;
////	headingChange = 0.5;
//	NSLog(@"camera altitude=%f", [mapView.camera altitude]);
	
	// begin animating
//	if (animationTimer != nil)
//	{
//		[animationTimer invalidate];
//	}
//	
//	count = 0;
//	animationTimer = [NSTimer scheduledTimerWithTimeInterval:1.0 / ANIMATION_FPS
//													 repeats:YES
//													   block:^(NSTimer* timer)
//					  {
//						  [mapView setCenterCoordinate:CLLocationCoordinate2DMake(mapView.region.center.latitude + latChange,
//																				  mapView.region.center.longitude + lonChange)
//											  animated:NO];
//						  
//						  MKMapCamera* camera = [mapView.camera copy];
//						  CLLocationDirection dir = camera.heading + headingChange;
//						  
//						  NSLog(@"setting dir from %f to %f with altitude %f", mapView.camera.heading, dir, mapView.camera.altitude);
//						  [camera setHeading:dir];
//						  [mapView setCamera:camera animated:NO];
//						  
//						  count++;
//					  }];
}

// =================================================================================
#pragma mark -						MKMapViewDelegate
// =================================================================================

- (void)mapView:(MKMapView *)map regionDidChangeAnimated:(BOOL)animated
{
//	NSLog(@"--------------------- regionDidChange ---------------------");
//	NSLog(@"location=%f %f", mapView.centerCoordinate.latitude, mapView.centerCoordinate.longitude);
//	NSLog(@"heading=%f altitude=%f", mapView.camera.heading, mapView.camera.altitude);
//	NSLog(@"=================");
}

// =================================================================================

- (MKAnnotationView*)mapView:(MKMapView *)map viewForAnnotation:(id<MKAnnotation>)annotation
{
	if (annotation == map.userLocation)
	{
		NSLog(@"view for userLocation annotation");
		MKAnnotationView* annotationView = [[MKAnnotationView alloc] init];
//		annotationView.image = [UIImage imageNamed:@"blank.png"];
		annotationView.image = [MyUtilities circleImageWithColor:UIColor.greenColor size:10];
		
		return annotationView;
	}
	
	// Use the default annotation
	return nil;
}

// =================================================================================

- (void)mapView:(MKMapView*)map didUpdateUserLocation:(nonnull MKUserLocation *)userLocation
{
	NSLog(@"didUpdate user location");
//	[map setCenterCoordinate:userLocation.location.coordinate animated:NO];
	
//	MKMapCamera* camera = [map.camera copy];
//	camera.altitude = CAMERA_ALTITUDE;
//	[map setCamera:camera animated:NO];
//	[map.camera setAltitude:CAMERA_ALTITUDE];
}

// =================================================================================
#pragma mark -						UIViewController
// =================================================================================

- (void)viewDidLoad
{
    [super viewDidLoad];
	
	[GPSManager defaultManager].delegate = self;
	
	[mapView setRegion:game.map.boundingRegion];
	NSLog(@"altitude=%f", mapView.camera.altitude);
	mapView.delegate = self;
	mapView.scrollEnabled = NO;
	mapView.zoomEnabled = NO;
	mapView.rotateEnabled = NO;
	mapView.showsCompass = NO;
	mapView.showsTraffic = NO;
	mapView.showsUserLocation = YES;
	mapView.showsPointsOfInterest = NO;
	mapView.mapType = MKMapTypeSatellite;
//	mapView.userTrackingMode = MKUserTrackingModeFollowWithHeading;			// we don't want this since it shows the default blue circles
	[mapView setUserTrackingMode:MKUserTrackingModeFollowWithHeading animated:NO];
	NSLog(@"after altitude=%f", mapView.camera.altitude);
	
	// add some default items for testing
	[itemPicker addItem:ITEM_TYPE_GENERIC];
	[itemPicker addItem:ITEM_TYPE_BOMB];
	[itemPicker addItem:ITEM_TYPE_BOMB];
	[itemPicker addItem:ITEM_TYPE_BOMB];
}

// =================================================================================

- (BOOL)prefersStatusBarHidden
{
	return YES;
}

// =================================================================================

@end

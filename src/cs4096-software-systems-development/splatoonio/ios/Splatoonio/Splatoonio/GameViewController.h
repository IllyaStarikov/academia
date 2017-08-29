//
//  GameViewController.h
//  Splatoonio
//
//  Created by Adam Evans on 8/24/17.
//  Copyright © 2017 Kijug Software. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <MapKit/MapKit.h>
#import "GPSManager.h"

#import "MapAnimationFrame.h"
#import "ItemPickerView.h"
#import "Game.h"


@interface GameViewController : UIViewController <MKMapViewDelegate, GPSManagerDelegate>
{
//	MyQueue* locationAnimationQueue;	// contains CLLocationCoordinate2D values for the centers of the map regions to display, also contain the heading
//	MyQueue* headingAnimationQueue;		// contains CLLocationCoordinate2D values for the centers of the map regions to display, also contain the heading
	
	CLLocationDirection headingChange;	// per frame heading change in degrres
	CLLocationDegrees latChange;		// per frame latitude change in degrres
	CLLocationDegrees lonChange;		// per frame longitude change in degrres
	MKCoordinateRegion currentRegion;	//
	NSTimer* animationTimer;			// triggers all the mapView frame changes
	
	IBOutlet MKMapView* mapView;
	IBOutlet ItemPickerView* itemPicker;
}

@property (readwrite) Game* game;

@end

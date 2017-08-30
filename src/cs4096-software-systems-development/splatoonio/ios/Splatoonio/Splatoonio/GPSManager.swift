//
//  GPSManager.swift
//  Splatoonio
//
//  Created by Adam Evans on 8/29/17.
//  Copyright © 2017 Kijug Software. All rights reserved.
//

import Foundation
import CoreLocation


protocol GPSManagerDelegate
{
	func locationUpdated(newLocation:CLLocation)
}


class GPSManager : NSObject, CLLocationManagerDelegate
{
	// used to track how many times GPS has been turned on to turn off GPS only when all
	// turnOn() calls have had a corresponding turnOff() call
	var prevLocation:CLLocation?
	var currentLocation:CLLocation?
	var delegate:GPSManagerDelegate?
	
	private var onCount:Int
	private var locationManager:CLLocationManager
	
	// uses the singleton design pattern
	private static let instance:GPSManager = GPSManager()
	
	// =================================================================================
	//									Initialization
	// =================================================================================
	
	static func defaultManager() -> GPSManager
	{
		return instance
	}
	
	// =================================================================================
	
	override init()
	{
		onCount = 0
		prevLocation = nil
		currentLocation = nil
		delegate = nil
		locationManager = CLLocationManager()
		
		super.init()
		
		locationManager.delegate = self
		locationManager.desiredAccuracy = kCLLocationAccuracyBest
		locationManager.distanceFilter = kCLDistanceFilterNone		// update us if we move at least one meter from where we currently are
		locationManager.pausesLocationUpdatesAutomatically = false
		locationManager.requestWhenInUseAuthorization()
	}
	
	// =================================================================================
	//									Lifecycle
	// =================================================================================
	
	func turnOn()
	{
		locationManager.startUpdatingLocation()
		locationManager.startUpdatingHeading()
		onCount += 1
	}
	
	// =================================================================================
	
	func locationManager(_ manager: CLLocationManager, didUpdateLocations locations: [CLLocation])
	{
		// TODO: handle multiple location updates by using the associated timestamp (do deferred locations have different timestamps?)
		prevLocation = currentLocation;
		currentLocation = locations[locations.count - 1]
		
		delegate?.locationUpdated(newLocation:currentLocation!)
	}
	
	// =================================================================================
	
	func locationManager(_ manager: CLLocationManager, didUpdateHeading newHeading: CLHeading)
	{
		// TODO: Do CLLocation objects from location updates contain updated headings? If so,
		// nothing to do, else figure out what to do 
	}
	
	// =================================================================================
	
	func locationManager(_ manager: CLLocationManager, didFailWithError error: Error)
	{
		print("ERROR: GPSManager failed: \(error)")
	}
	
	// =================================================================================
	
	func turnOff()
	{
		onCount -= 1
		
		// turn off only if nobody is using it
		if (onCount == 0)
		{
			locationManager.stopUpdatingHeading()
			locationManager.stopUpdatingLocation()
		}
	}
	
	// =================================================================================

}








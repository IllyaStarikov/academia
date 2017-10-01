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
	func headingUpdated(newHeading:CLHeading)
}


class GPSManager : NSObject, CLLocationManagerDelegate
{
	// used to track how many times GPS has been turned on to turn off GPS only when all
	// turnOn() calls have had a corresponding turnOff() call
	var prevLocation:CLLocation?
	var currentLocation:CLLocation?
	var prevHeading:CLHeading?
	var currentHeading:CLHeading?
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
		prevHeading = nil
		currentHeading = nil
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
		print("turning on GPSManager...")
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
		prevHeading = currentHeading;
		currentHeading = newHeading
		
		delegate?.headingUpdated(newHeading:currentHeading!)
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
	//									Query Functions
	// =================================================================================
	// Only returns nil before we have gotten our first location update
	func location() -> CLLocationCoordinate2D!
	{
		guard let prev = prevLocation else
		{
			return currentLocation?.coordinate
		}
		guard let current = currentLocation else
		{
			return nil
		}
		
		// interpolate between the points
//		let timeDiff = prev.timestamp.timeIntervalSince(current.timestamp)
		let timeDiff:TimeInterval = 1       // Assumes every update is for the past 1 second of movement
		let latDiff = current.coordinate.latitude - prev.coordinate.latitude
		let lonDiff = current.coordinate.longitude - prev.coordinate.longitude
		
		let time = Date().timeIntervalSince(current.timestamp)
		let fraction = (time > timeDiff ? 1 : time / timeDiff)       // clamp to [0, 1]
		let lat = prev.coordinate.latitude + (fraction * latDiff)
		let lon = prev.coordinate.longitude + (fraction * lonDiff)
		
		return CLLocationCoordinate2DMake(lat, lon)
	}
	
	// =================================================================================
	// Only returns nil before we have gotten our first heading update
	func heading() -> CLLocationDirection!
	{
		guard let prev = prevHeading else
		{
			return currentHeading?.trueHeading
		}
		guard let current = currentHeading else
		{
			return nil
		}
		
		// when interpolating, we assume we are getting data 0.03 seconds after when the device changed heading 
		let timeDiff:TimeInterval = 0.03
		
		// turn/interpolate in the direction that requires the least turning, and account for crossing
		// the 0/360 degree boundary
		var from = prev.trueHeading
		var to = current.trueHeading
		let angleDiff = abs(to - from)
		
		if (angleDiff > 180)
		{
			let change = 360 * Int((angleDiff + 180) / 360)
			
			if (to > from)
			{
				from += CLLocationDirection(change)
			}
			else
			{
				to += CLLocationDirection(change)
			}
		}
		
		let headingDiff = to - from
		let time = Date().timeIntervalSince(current.timestamp)
		let fraction = (time > timeDiff ? 1 : time / timeDiff)       // clamp to [0, 1]
		var finalHeading = prev.trueHeading + (fraction * headingDiff)
		
		// get in bounds of [0, 360)
		if (finalHeading < 0)
		{
			finalHeading += Double(360 * Int((-finalHeading / 360) + 1))
		}
		else if (finalHeading >= 360)
		{
			finalHeading -= Double(360 * Int(-finalHeading / 360))
		}
		
		return CLLocationDirection(finalHeading)
	}
	
	// =================================================================================

}








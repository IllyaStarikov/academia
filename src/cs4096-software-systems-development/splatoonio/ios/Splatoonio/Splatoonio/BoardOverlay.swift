//
//  BoardOverlay.swift
//  Splatoonio
//
//  Created by Adam Evans on 9/3/17.
//  Copyright © 2017 Kijug Software. All rights reserved.
//

import Foundation
import MapKit


class BoardOverlay : NSObject, MKOverlay
{
	var board:GameBoard!
	
	// =================================================================================
	//										MKOverlay
	// =================================================================================
	
	var coordinate: CLLocationCoordinate2D
	{
		return board.boundingRegion.center
	}
	
	// =================================================================================
	
	var boundingMapRect: MKMapRect
	{
		let geoBounds = board.boundingRegion
		let topLeft = CLLocationCoordinate2DMake(geoBounds.center.latitude + (geoBounds.span.latitudeDelta / 2),
		                                         geoBounds.center.longitude - (geoBounds.span.longitudeDelta / 2))
		let botRight = CLLocationCoordinate2DMake(topLeft.latitude - geoBounds.span.latitudeDelta,
		                                          topLeft.longitude + geoBounds.span.longitudeDelta)
		                                          
		let origin = MKMapPointForCoordinate(topLeft)
		let opposite = MKMapPointForCoordinate(botRight)
		let rect = MKMapRectMake(origin.x, origin.y, opposite.x - origin.x, opposite.y - origin.y)
		
		return rect
	}
	
	// =================================================================================
}

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
		print("   overlay center=\(board.boundingRegion.center.latitude, board.boundingRegion.center.longitude)")
		return board.boundingRegion.center
	}
	
	// =================================================================================
	
	var boundingMapRect: MKMapRect
	{
		let geoBounds = board.boundingRegion
		let topLeft = CLLocationCoordinate2DMake(geoBounds.center.latitude - (geoBounds.span.latitudeDelta / 2),
		                                         geoBounds.center.longitude - (geoBounds.span.longitudeDelta / 2))
		let botRight = CLLocationCoordinate2DMake(topLeft.latitude + geoBounds.span.latitudeDelta,
		                                          topLeft.longitude + geoBounds.span.longitudeDelta)
		                                          
		let origin = MKMapPointForCoordinate(topLeft)
		let opposite = MKMapPointForCoordinate(botRight)
		let rect = MKMapRectMake(origin.x, origin.y, opposite.x - origin.x, opposite.y - origin.y)
		
		return rect
	}
	
	// =================================================================================
	//									Utilities
	// =================================================================================
	// Returns the pixel index or a negative index if out of bounds
	func pixelIndexForGPSLocation(location:CLLocationCoordinate2D) -> Int
	{
		let boardBounds = board.boundingRegion
		let mapPoint = MKMapPointForCoordinate(location)
		let boardRect = MKMapRectMake(boardBounds.center.longitude - (boardBounds.span.longitudeDelta / 2),
		                              boardBounds.center.latitude - (boardBounds.span.latitudeDelta / 2),
		                              boardBounds.span.longitudeDelta,
		                              boardBounds.span.latitudeDelta)
		
		// if out of bounds, return -1
		if (!MKMapRectContainsPoint(boardRect, mapPoint))
		{
			return -1
		}
		
		let landUnitWidthInLon = boardRect.size.width / Double(board.width)
		let landUnitHeightInLat = boardRect.size.height / Double(board.height)
		let row = Int((location.latitude - boardRect.origin.y) / landUnitHeightInLat)
		let col = Int((location.longitude - boardRect.origin.x) / landUnitWidthInLon)
		
		return (row * board.width) + col
	}
	
	// =================================================================================
}

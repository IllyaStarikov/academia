//
//  GameBoard.swift
//  Splatoonio
//
//  Created by Adam Evans on 8/29/17.
//  Copyright © 2017 Kijug Software. All rights reserved.
//

import Foundation
import MapKit


protocol GameBoardDelegate
{
	func boardUpdated(pixels:[PixelUpdate])
}


class GameBoard
{
	static var BOARD_PIXEL_SIZE:Double = 1.0				// meters per land unit side
	
	var width:Int
	var height:Int
	var delegate:GameBoardDelegate?
	
	private var boardData:[TeamColor]
	private var geoBounds:MKCoordinateRegion		// backing variable for boundingRegion
	
	// computed properties
	var boundingRegion:MKCoordinateRegion
	{
		get
		{
			return geoBounds
		}
		set
		{
			geoBounds = newValue
			
			let topLeft = CLLocation(latitude: geoBounds.center.latitude + (geoBounds.span.latitudeDelta / 2),
			                         longitude: geoBounds.center.longitude - (geoBounds.span.longitudeDelta / 2))
			let topRight = CLLocation(latitude: geoBounds.center.latitude + (geoBounds.span.latitudeDelta / 2),
			                          longitude: geoBounds.center.longitude + (geoBounds.span.longitudeDelta / 2))
			let botLeft = CLLocation(latitude: geoBounds.center.latitude - (geoBounds.span.latitudeDelta / 2),
			                         longitude: geoBounds.center.longitude - (geoBounds.span.longitudeDelta / 2))
			let widthMeters = topLeft.distance(from: topRight)
			let heightMeters = topLeft.distance(from: botLeft)
			
			width = Int(round(widthMeters / GameBoard.BOARD_PIXEL_SIZE))
			height = Int(round(heightMeters / GameBoard.BOARD_PIXEL_SIZE))
			boardData = [TeamColor](repeating:.none, count:MemoryLayout<TeamColor>.size * width * height)
		}
	}
	
	// =================================================================================
	//									Initializiers
	// =================================================================================
	
	init()
	{
		width = 0
		height = 0
		delegate = nil
		boardData = [TeamColor]()
		geoBounds = MKCoordinateRegion(center: CLLocationCoordinate2DMake(0, 0), span: MKCoordinateSpanMake(0, 0))
	}
	
	// =================================================================================
	//									Normal Functions
	// =================================================================================
	
	func updatePixels(pixels:[PixelUpdate])
	{
		// TODO: update the baord pixels
		for pixel in pixels
		{
			boardData[pixel.index] = pixel.team
		}
		
		delegate?.boardUpdated(pixels:pixels)
	}
	
	// =================================================================================
	
	func setBoardColor(row:Int, col:Int, color:TeamColor)
	{
		setBoardColor(index:(row * width) + col, color:color)
	}
	
	// =================================================================================
	
	func setBoardColor(index:Int, color:TeamColor)
	{
		boardData[index] = color
		
		var update = PixelUpdate()
		update.index = index
		update.team = color
		delegate?.boardUpdated(pixels:[update])
	}
	
	// =================================================================================
	
	func getBoardColor(row:Int, col:Int) -> TeamColor
	{
		if (row < 0) || (row >= height) || (col < 0) || (col >= width)
		{
			print("ERROR: bad row or col value: r=\(row) c=\(col)")
		}
		
		let index = (row * width) + col
		return boardData[index]
	}
	
	// =================================================================================
	// Returns the pixel index or a negative index if out of bounds
	func pixelIndexForGPSLocation(location:CLLocationCoordinate2D) -> Int
	{
		let topLeftLat = geoBounds.center.latitude + (geoBounds.span.latitudeDelta / 2)
		let topLeftLon = geoBounds.center.longitude - (geoBounds.span.longitudeDelta / 2)
		let botRightLat = geoBounds.center.latitude - (geoBounds.span.latitudeDelta / 2)
		let botRightLon = geoBounds.center.longitude + (geoBounds.span.longitudeDelta / 2)
		
		if (location.latitude < botRightLat) || (location.latitude > topLeftLat) ||
			(location.longitude < topLeftLon) || (location.longitude > botRightLon)
		{
			return -1
		}
		
		let landUnitWidth = geoBounds.span.longitudeDelta / Double(width)
		let landUnitHeight = geoBounds.span.latitudeDelta / Double(height)
		let row = Int((topLeftLat - location.latitude) / landUnitHeight)
		let col = Int((location.longitude - topLeftLon) / landUnitWidth)
		
		return (row * width) + col
	}
	
	// =================================================================================
	// speed is in meters per second
	func paintLine(from fromCoord:CLLocationCoordinate2D, to toCoord:CLLocationCoordinate2D, travelTime:TimeInterval, forPlayer player:Player) -> [PixelUpdate]
	{
		let maxLat = geoBounds.center.latitude + (geoBounds.span.latitudeDelta / 2)
		let minLon = geoBounds.center.longitude - (geoBounds.span.longitudeDelta / 2)
		let landUnitHeight = geoBounds.span.latitudeDelta / Double(height)
		let landUnitWidth = geoBounds.span.longitudeDelta / Double(width)
		let from = CGPoint(x:(fromCoord.longitude - minLon) / landUnitWidth,
		                   y:(maxLat - fromCoord.latitude) / landUnitHeight)
		let to = CGPoint(x:(toCoord.longitude - minLon) / landUnitWidth,
		                 y:(maxLat - toCoord.latitude) / landUnitHeight)
		
		// record what pixels were drawn to
		let pixelCenterDist = 1.0 / UIScreen.main.scale
		var updates = [PixelUpdate]()
		
		let minx = min(from.x, to.x)
		let maxx = max(from.x, to.x)
		let miny = min(from.y, to.y)
		let maxy = max(from.y, to.y)
		let radiusInLandUnits = CGFloat(player.brushRadius) / CGFloat(GameBoard.BOARD_PIXEL_SIZE)
		
		let startr = max(0,          Int(round(miny - radiusInLandUnits)))
		let endr   = min(height - 1, Int(round(maxy + radiusInLandUnits)))
		let startc = max(0,          Int(round(minx - radiusInLandUnits)))
		let endc   = min(width - 1,  Int(round(maxx + radiusInLandUnits)))
		
		// have to use variables i and j instead of range-based for loops because can't create ranges with start > end
		var i = startr
		
		while (i < endr)
		{
			var j = startc
			
			while (j < endc)
			{
				let index = (i * width) + j
				
				// TODO: compute timestamp... somehow
				// Drop a normal to the line we are drawing and compute the distance to the endpoints
				let here = CGPoint(x:CGFloat(j) + pixelCenterDist, y:CGFloat(i) + pixelCenterDist)
				let dx = to.x - from.x		// distance to center line along x axis
				let dy = to.y - from.y		// distance to center line along y axis
				var dist:CGFloat			// distance to center line squared
				let intersection:CGPoint
				
				if (dx == 0)
				{
					dist = (here.x - from.x) * (here.x - from.x)
					intersection = CGPoint(x:from.x, y:here.y)
				}
				else if (dy == 0)
				{
					dist = (here.y - from.y) * (here.y - from.y)
					intersection = CGPoint(x:here.x, y:from.y)
				}
				else
				{
					// find the point of intersection of the normal and center line
					let m1 = dy / dx
					let b1 = from.y - (m1 * from.x)
					let m2 = -dx / dy
					let b2 = here.y - (m2 * here.x)
					let x:CGFloat = (b2 - b1) / (m1 - m2)
					let y:CGFloat = b1 + (m1 * x)
					intersection = CGPoint(x:x, y:y)
					
					let xterm = here.x - x
					let yterm = here.y - y
					dist = (xterm * xterm) + (yterm * yterm)
				}
				
				// if the intersection is outside the two endpoints, use the distance to the
				// closest endpoint instead of distance to center line
//				if ((intersection.x - from.x) * (intersection.x - from.x) > 0) &&
//					((intersection.x - to.x) * (intersection.x - to.x) > 0)
				if (intersection.x < minx) || (intersection.x > maxx) || (intersection.y < miny) || (intersection.y > maxy)
				{
					var xterm = here.x - from.x
					var yterm = here.y - from.y
					let fromDist = (xterm * xterm) + (yterm * yterm)
					
					xterm = here.x - to.x
					yterm = here.y - to.y
					let toDist = (xterm * xterm) + (yterm * yterm)
					
					dist = min(fromDist, toDist)
				}
				
				// paint the land unit if within the player's radius
				if (dist < CGFloat(player.brushRadius * player.brushRadius))
				{
					var update = PixelUpdate()
					update.team = player.team
					update.index = index
					update.timestamp = 0		// TODO: needs to be set to true value
					updates.append(update)
				}
				
				j += 1
			}
			
			i += 1
		}
		
//		self.updatePixels(pixels:updates)
		return updates
	}
	
	// =================================================================================	
}












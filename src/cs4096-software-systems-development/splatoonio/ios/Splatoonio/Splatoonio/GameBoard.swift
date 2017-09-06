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
	static var BOARD_PIXEL_SIZE:Double = 1.0 / 111320		// degrees per land unit (latitude); uses 111.320 km per degree
	
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
			
			print("   geoBounds=\(geoBounds.center.latitude, geoBounds.center.longitude) span=\(geoBounds.span.latitudeDelta, geoBounds.span.longitudeDelta)")
			width = Int(geoBounds.span.longitudeDelta / GameBoard.BOARD_PIXEL_SIZE)
			height = Int(geoBounds.span.latitudeDelta / (GameBoard.BOARD_PIXEL_SIZE * cos(geoBounds.center.latitude)))
			boardData = [TeamColor](repeating:.none, count:MemoryLayout<TeamColor>.size * width * height)
			print("   set GameBoard bounding region -> width=\(width) height=\(height)")
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
			boardData[pixel.index] = pixel.owner
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
		update.owner = color
		delegate?.boardUpdated(pixels:[update])
	}
	
	// =================================================================================
	
	func getBoardColor(row:Int, col:Int) -> TeamColor
	{
		return boardData[(row * width) + col]
	}
	
	// =================================================================================	
}












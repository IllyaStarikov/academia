//
//  GameBoard.swift
//  Splatoonio
//
//  Created by Adam Evans on 8/29/17.
//  Copyright © 2017 Kijug Software. All rights reserved.
//

import Foundation
import MapKit


class GameBoard
{
	static var BOARD_PIXEL_SIZE:Double = 1.0		// meters per land unit
	
	private var width:Int
	private var height:Int
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
			
			width = Int(geoBounds.span.longitudeDelta / GameBoard.BOARD_PIXEL_SIZE)
			height = Int(geoBounds.span.latitudeDelta / GameBoard.BOARD_PIXEL_SIZE)
			boardData = [TeamColor](repeating:.none, count:width * height)
		}
	}
	
	// =================================================================================
	//									Initializiers
	// =================================================================================
	
	init()
	{
		width = 0
		height = 0
		boardData = [TeamColor]()
		geoBounds = MKCoordinateRegion(center: CLLocationCoordinate2DMake(0, 0), span: MKCoordinateSpanMake(0, 0))
	}
	
	// =================================================================================
	//								Getters and Setters
	// =================================================================================
	
	func setBoardColor(row:Int, col:Int, color:TeamColor)
	{
		boardData[(row * width) + col] = color
	}
	
	// =================================================================================
	
	func getBoardColor(row:Int, col:Int) -> TeamColor
	{
		return boardData[(row * width) + col]
	}
	
	// =================================================================================	
}

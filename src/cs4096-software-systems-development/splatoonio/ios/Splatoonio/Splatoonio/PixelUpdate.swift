//
//  PixelUpdate.swift
//  Splatoonio
//
//  Created by Adam Evans on 8/31/17.
//  Copyright © 2017 Kijug Software. All rights reserved.
//

import Foundation


// Represents an update to a single pixel, for use with communication with the server
struct PixelUpdate
{
	var index:Int		// index in the board for this pixel. Indices count like reading a book
	var team:TeamColor
	var timestamp:UInt32
	
	init()
	{
		index = 0
		team = .none
		timestamp = 0
	}
}


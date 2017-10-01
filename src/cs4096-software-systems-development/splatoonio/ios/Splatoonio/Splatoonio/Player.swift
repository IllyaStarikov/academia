//
//  Player.swift
//  Splatoonio
//
//  Created by Adam Evans on 8/30/17.
//  Copyright © 2017 Kijug Software. All rights reserved.
//

import Foundation
import CoreLocation


class Player
{
	var id:PlayerID
	var team:TeamColor
	var brushRadius:Float		// in meters
	var location:CLLocation?
	var name:String
	
	// =================================================================================
	//									Initializers
	// =================================================================================
	
	init()
	{
		id = 0
		team = .none
		brushRadius = 0
		location = nil
		name = ""
	}
	
	// =================================================================================
}

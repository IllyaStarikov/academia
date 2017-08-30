//
//  Item.swift
//  Splatoonio
//
//  Created by Adam Evans on 8/29/17.
//  Copyright © 2017 Kijug Software. All rights reserved.
//

import UIKit
import CoreLocation



class Item
{
	var id:UInt64
	var location:CLLocationCoordinate2D
	
	let type:ItemType = .generic
	
	// =================================================================================
	//									Initializers
	// =================================================================================
	
	init()
	{
		id = 0
		location = CLLocationCoordinate2DMake(0, 0)
	}
	
	// =================================================================================
}

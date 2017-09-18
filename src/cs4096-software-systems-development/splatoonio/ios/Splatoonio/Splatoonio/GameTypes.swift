//
//  GameTypes.swift
//  Splatoonio
//
//  Created by Adam Evans on 8/29/17.
//  Copyright © 2017 Kijug Software. All rights reserved.
//

import UIKit


typealias GameID = UInt64
typealias PlayerID = UInt64


// =================================================================================

enum LobbyID
{
	case lobby(UInt64)
	case none
}

// =================================================================================
// TODO: convert to use UInt8's
enum TeamColor : Int
{
	case red = 0
	case green
	case blue
	
	case count
	case none
	
	// =================================================================================
	
	func color() -> PaintColor
	{
		switch (self)
		{
			case .red:		return PaintColor(255, 0,   0)
			case .green:	return PaintColor(0,   255, 0)
			case .blue:		return PaintColor(0,   0,   255)
			default:		return PaintColor(0,   0,   0)
		}
	}
	
	// =================================================================================
	
	func description() -> String
	{
		switch (self)
		{
			case .red:		return "Red"
			case .green:	return "Green"
			case .blue:		return "Blue"
			case .none:		return "None"
			case .count:	return "Count"
		}
	}
}

// =================================================================================

struct PaintColor
{
	var r:UInt8 = 0
	var g:UInt8 = 0
	var b:UInt8 = 0
	var description:String
	{
		return "\(r, g, b)"
	}
	
	init(_ inr:UInt8, _ ing:UInt8, _ inb:UInt8)
	{
		r = inr
		g = ing
		b = inb
	}
}

// =================================================================================
//									ItemType
// =================================================================================

enum ItemType : Int
{
	case generic = 0
	case bomb
//	case greenShell
	
	case count
	case none
	
	// =================================================================================
	
	func name() -> String
	{
		switch (self)
		{
			case .generic:		return "Generic Item"
			case .bomb:			return "Bomb"
//			case .greenShell:	return "Green Shell"
			default:			return "ERROR: bad item type"
		}
	}
	
	// =================================================================================
	
	func icon() -> UIImage!
	{
		switch (self)
		{
			case .generic:		return UIImage(named:"itemIconGeneric.png")!
			case .bomb:			return UIImage(named:"itemIconBomb.png")!
//			case .greenShell:	return UIImage(named:"itemIconGeneric.png")!
			default:			print("ERROR: no image for item type \(self)")
		}
		
		return nil
	}
	
	// =================================================================================
}







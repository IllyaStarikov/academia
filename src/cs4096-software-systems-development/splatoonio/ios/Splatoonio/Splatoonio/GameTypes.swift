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

enum TeamColor : Int
{
	case red = 0
	case green
	case blue
	
	case count
	case none
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







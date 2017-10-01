//
//  GameMenuItemType.swift
//  Splatoonio
//
//  Created by Adam Evans on 9/28/17.
//  Copyright © 2017 Kijug Software. All rights reserved.
//

import UIKit

enum GameMenuItemType : Int
{
	case expand
	case quit
	case settings
	case toggleMinimap
	case none
	
	func title() -> String
	{
		switch (self)
		{
		case .expand:			return "Expand"
		case .quit:				return "Quit"
		case .settings:			return "Settings"
		case .toggleMinimap:	return "Toggle Minimap"
		default:				return ""
		}
	}
	
	func icon() -> UIImage?
	{
		return UIImage(named:"itemIconBomb.png")
	}
}

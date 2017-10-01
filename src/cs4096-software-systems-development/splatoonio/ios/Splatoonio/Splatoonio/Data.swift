//
//  Data.swift
//  Splatoonio
//
//  Created by Adam Evans on 9/28/17.
//  Copyright © 2017 Kijug Software. All rights reserved.
//

import Foundation

// constants for settings
let SETTING_MINIMAP_ON =		"settingMinimapOn"			// Bool
let SETTING_SOUNDS_ON =			"settingSoundsOn"			// Bool
let SETTING_MINIMAP_ALPHA = 	"settingMinimapAlpha"		// Int
let SETTING_PAINT_ALPHA =		"settingPaintAlpha"			// Int

// Credentials
let USER_INFO_ID =				"userInfoID"				// UInt64

// other constants and stuff
let TRACKING_NUM_LAUNCHES =		"trackingNumLaunches"		// Int


class Data
{
	// =================================================================================

	static func initializeUserDefaults()
	{
		let d = UserDefaults.standard
		let numLaunches = d.integer(forKey:TRACKING_NUM_LAUNCHES)		// defaults to 0 if no value for this key
		
		// initialize values on first launch
		if (numLaunches == 0)
		{
			d.set(true, forKey:SETTING_MINIMAP_ON)
			d.set(true, forKey:SETTING_SOUNDS_ON)
			d.set(100, forKey:SETTING_MINIMAP_ALPHA)
			d.set(100, forKey:SETTING_PAINT_ALPHA)
		}
		
		d.set(numLaunches + 1, forKey:TRACKING_NUM_LAUNCHES)
	}

	// =================================================================================
}

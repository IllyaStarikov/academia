//
//  MenuViewController.swift
//  Splatoonio
//
//  Created by Adam Evans on 8/29/17.
//  Copyright © 2017 Kijug Software. All rights reserved.
//

import UIKit
import CoreLocation


class MenuViewController: UIViewController
{
	// =================================================================================
	//								UIViewController
	// =================================================================================
	
	override func viewDidLoad()
	{
		super.viewDidLoad()
		
		// Make sure that we have access to location services and turn it on
		if (!CLLocationManager.locationServicesEnabled())
		{
			let alert = UIAlertController(title:"Uh-Oh", message:"Turn on Location Services in Settings to play", preferredStyle:.alert)
			alert.addAction(UIAlertAction(title:"Okay", style:.cancel, handler:nil))
			
			self.navigationController?.present(alert, animated:true, completion:nil)
		}
		else
		{
			GPSManager.defaultManager().turnOn()
		}
	}
	
	// =================================================================================
	
	override var prefersStatusBarHidden: Bool
	{
		get { return true }
	}
	
	// =================================================================================
}


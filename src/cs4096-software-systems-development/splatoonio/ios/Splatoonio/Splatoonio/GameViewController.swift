//
//  GameViewController.swift
//  Splatoonio
//
//  Created by Adam Evans on 8/30/17.
//  Copyright © 2017 Kijug Software. All rights reserved.
//

import UIKit
import MapKit


class GameViewController: UIViewController, MKMapViewDelegate
{
	var game:Game!
	
	@IBOutlet private var mapView:MKMapView!
	@IBOutlet private var itemPicker:ItemPickerView!
	
	// =================================================================================
	//								MKMapViewDelegate
	// =================================================================================
	
	func mapView(_ map: MKMapView, didUpdate userLocation: MKUserLocation)
	{
		// TODO: do stuff?
	}
	
	// =================================================================================
	
	func mapView(_ map: MKMapView, viewFor annotation: MKAnnotation) -> MKAnnotationView?
	{
		if (annotation === map.userLocation)	// check that they are the same object
		{
			let annotationView = MKAnnotationView(annotation:annotation, reuseIdentifier:"customUserLocation")
			annotationView.image = MyUtilities.circleImageWithColor(color:.green, radius:10)
			
			return annotationView
		}
		
		// use the default annotation
		return nil
	}
	
	// =================================================================================
	//								UIViewController
	// =================================================================================
	
    override func viewDidLoad()
	{
        super.viewDidLoad()

		mapView.delegate = self
		mapView.isScrollEnabled = false
		mapView.isPitchEnabled = false
		mapView.isZoomEnabled = false
		mapView.isRotateEnabled = false
		mapView.showsCompass = false
		mapView.showsTraffic = false
		mapView.showsUserLocation = false
		mapView.showsPointsOfInterest = false
		mapView.mapType = .satellite
		mapView.setUserTrackingMode(.followWithHeading, animated:false)
		
		// add some default items for testing
		itemPicker.addItem(type:.generic)
		itemPicker.addItem(type:.bomb)
		itemPicker.addItem(type:.bomb)
		itemPicker.addItem(type:.bomb)
    }

	// =================================================================================
	
	override var prefersStatusBarHidden: Bool
	{
		get { return true }
	}
	
	// =================================================================================
}

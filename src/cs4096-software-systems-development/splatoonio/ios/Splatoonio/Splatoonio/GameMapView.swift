//
//  GameMapView.swift
//  Splatoonio
//
//  Created by Adam Evans on 9/13/17.
//  Copyright © 2017 Kijug Software. All rights reserved.
//

import UIKit
import MapKit


class GameMapView: MKMapView, MKMapViewDelegate
{
	var game:Game!
	var boardOverlay:BoardOverlay!
	var boardRenderer:BoardOverlayRenderer!
	
	private var prevLocation:CLLocation?
	
	// =================================================================================
	//								  Initializers
	// =================================================================================
	
	init?(game newGame:Game)
	{
		super.init(frame:CGRect.zero)
		
		game = newGame
		
		boardOverlay = BoardOverlay()
		boardOverlay.board = game.board
		
		guard let renderer = BoardOverlayRenderer(boardOverlay:boardOverlay) else		// must initialize with an overlay or it won't draw
		{
			print("ERROR: Could not create overlay renderer")
			return nil
		}
		
		boardRenderer = renderer
		boardRenderer.gameBoard = game.board
		
		self.add(boardOverlay)
		self.initializeMapSettings()
	}
	
	// =================================================================================
	
	required init?(coder aDecoder: NSCoder)
	{
		print("ERROR: GameMapView.initWithCoder() should not be called")
		super.init(coder:aDecoder)
		self.initializeMapSettings()
	}
	
	// =================================================================================
	
	var timer:Timer!
	var timer2:Timer!
	
	func initializeMapSettings()
	{
		// for testing on simulator - kills heading and location tracking on device... not sure why
		let coord = CLLocationCoordinate2DMake(37.952902, -91.772447)
		let region = MKCoordinateRegionMakeWithDistance(coord, 200, 140)
		self.setRegion(region, animated:true)
		
		self.delegate = self
		self.isScrollEnabled = false
		self.isPitchEnabled = true
		self.isZoomEnabled = true
		self.isRotateEnabled = true
		self.showsCompass = false
		self.showsTraffic = false
		self.showsUserLocation = true
		self.showsPointsOfInterest = false
//		self.mapType = .satellite
		
//		timer = Timer.scheduledTimer(timeInterval:0.03, target:self, selector:#selector(updateLocation(timer:)), userInfo:nil, repeats:true)
	}
	
	// =================================================================================
	//								Location Updating
	// =================================================================================
	// Updates the heading and our location on the map to reflect the user's location and heading
	func updateLocation(timer:Timer)
	{
		let gps = GPSManager.defaultManager()
		
		if let loc = gps.location()
		{
			self.centerCoordinate = loc
			
			if  let me = self.game.me,
				let to = gps.currentLocation
			{
				game.move(player:me.id, to:to)
			}
		}
		
		if let heading = gps.heading()
		{
			self.camera.heading = heading
		}
		
		self.setNeedsDisplay()
	}
	
	// =================================================================================
	//								MKMapViewDelegate
	// =================================================================================
	
	func mapView(_ mapView: MKMapView, rendererFor overlay: MKOverlay) -> MKOverlayRenderer
	{
		return boardRenderer
	}
	
	// =================================================================================
	
	func mapView(_ mapView: MKMapView, viewFor annotation: MKAnnotation) -> MKAnnotationView?
	{
		if (annotation === mapView.userLocation)		// pointer/reference check, not equality
		{
			let annotationView = MKAnnotationView(annotation:annotation, reuseIdentifier:"customUserLocation")
			annotationView.image = nil
			
			return annotationView
		}
		
		// use the default annotation
		return nil
	}
	
	// =================================================================================
}














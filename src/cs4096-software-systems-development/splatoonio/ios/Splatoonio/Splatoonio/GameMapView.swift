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
	
	func initializeMapSettings()
	{
		// for testing on simulator - kills heading and location tracking on device... not sure why
		let coord = CLLocationCoordinate2DMake(37.952902, -91.772447)
		let region = MKCoordinateRegionMakeWithDistance(coord, 100, 70)
		self.setRegion(region, animated:true)
		
		self.delegate = self
		self.isScrollEnabled = false
		self.isPitchEnabled = false
		self.isZoomEnabled = true
		self.isRotateEnabled = false
		self.showsCompass = false
		self.showsTraffic = false
		self.showsUserLocation = false
		self.showsPointsOfInterest = false
		self.mapType = .satellite
		self.setUserTrackingMode(.followWithHeading, animated:false)
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
	
	// TODO: uncomment this function to use real user location
//	func mapView(_ mapView: MKMapView, didUpdate userLocation: MKUserLocation)
//	{
//		guard let me = game.me else
//		{
//			return
//		}
//		guard let to = userLocation.location else
//		{
//			return
//		}
//		
//		let from = (prevLocation != nil ? prevLocation! : to)
//		let travelTime = to.timestamp.timeIntervalSince(from.timestamp)
//		
//		game.board.paintLine(from:from.coordinate, to:to.coordinate, travelTime:travelTime, forPlayer:me)
//		
//		prevLocation = to
//	}
	
	// =================================================================================
}














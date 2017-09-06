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
	private var boardOverlay:BoardOverlay!
	private var boardRenderer:BoardOverlayRenderer!
	
	@IBOutlet private var map:MKMapView!
	@IBOutlet private var itemPicker:ItemPickerView!
	
	// =================================================================================
	//								Touch Functions
	// =================================================================================
	
	override func touchesMoved(_ touches: Set<UITouch>, with event: UIEvent?)
	{
		guard let touchpoint = touches.first?.location(in:map) else
		{
			return
		}
		
		let coord = map.convert(touchpoint, toCoordinateFrom:map)
		let index = boardOverlay.pixelIndexForGPSLocation(location: coord)
		
		if (index >= 0)
		{
			print("setting red at r=\(index / game.board.width) c=\(index % game.board.width)")
			game.board.setBoardColor(index:index, color:.red)
		}
	}
	
	// =================================================================================
	
	override func touchesEnded(_ touches: Set<UITouch>, with event: UIEvent?)
	{
		guard let touchpoint = touches.first?.location(in:map) else
		{
			return
		}
		
		let coord = map.convert(touchpoint, toCoordinateFrom:map)
		let index = boardOverlay.pixelIndexForGPSLocation(location: coord)
		
		if (index >= 0)
		{
			game.board.setBoardColor(index:index, color:.red)
		}
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
		if (annotation === mapView.userLocation)	// check that they are the same object
		{
			let annotationView = MKAnnotationView(annotation:annotation, reuseIdentifier:"customUserLocation")
//			annotationView.image = MyUtilities.circleImageWithColor(color:.green, radius:10)
			annotationView.image = nil
			
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

//		let coord = GPSManager.defaultManager().currentLocation!.coordinate
		let coord = CLLocationCoordinate2DMake(37.953039, -91.772499)
		let region = MKCoordinateRegionMakeWithDistance(coord, 200, 140)
		map.setRegion(region, animated:true)

		map.delegate = self
		map.isScrollEnabled = true
		map.isPitchEnabled = false
		map.isZoomEnabled = true
		map.isRotateEnabled = false
		map.showsCompass = false
		map.showsTraffic = false
		map.showsUserLocation = false
		map.showsPointsOfInterest = false
		map.mapType = .satellite
//		map.setUserTrackingMode(.followWithHeading, animated:false)
		
		boardOverlay = BoardOverlay()
		boardOverlay.board = game.board
		
		boardRenderer = BoardOverlayRenderer(overlay:boardOverlay)	// must initialize with an overlay or it won't draw
		boardRenderer.board = game.board

		map.add(boardOverlay)
		
		// add some default items for testing
		itemPicker.addItem(type:.generic)
		itemPicker.addItem(type:.bomb)
		itemPicker.addItem(type:.bomb)
		itemPicker.addItem(type:.bomb)
		itemPicker.isHidden = true
		
		// used to intercept touches, allowing us to process them instead of the map
//		self.view.addSubview(UIView(frame:self.view.bounds))
    }

	// =================================================================================
	
	override var prefersStatusBarHidden: Bool
	{
		return true
	}
	
	// =================================================================================
}

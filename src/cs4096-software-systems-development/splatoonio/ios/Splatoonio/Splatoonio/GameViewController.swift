//
//  GameViewController.swift
//  Splatoonio
//
//  Created by Adam Evans on 8/30/17.
//  Copyright © 2017 Kijug Software. All rights reserved.
//

import UIKit
import MapKit


class GameViewController: UIViewController, ItemPickerViewDelegate, GameBoardDelegate
{
	var game:Game!
	
	private var lastCoord:CLLocationCoordinate2D!
	private var lastTouchTime:Date!
	private var lastIndex:Int!
	private var minimap:Minimap!
	private var map:GameMapView!
	
	@IBOutlet private var itemPicker:ItemPickerView!
	
	// =================================================================================
	//								Touch Functions
	// =================================================================================
	
	override func touchesBegan(_ touches: Set<UITouch>, with event: UIEvent?)
	{
		guard let touchpoint = touches.first?.location(in:map) else
		{
			return
		}
		
		lastTouchTime = Date()
		lastCoord = map.convert(touchpoint, toCoordinateFrom:map)
		lastIndex = game.board.pixelIndexForGPSLocation(location: lastCoord)
		
		if (lastIndex >= 0)
		{
//			game.board.setBoardColor(index:lastIndex, color:.red)
			game.board.paintLine(from:lastCoord, to:lastCoord, travelTime:1.0, forPlayer:game.me!)
		}
	}
	
	// =================================================================================
	
	override func touchesMoved(_ touches: Set<UITouch>, with event: UIEvent?)
	{
		handleTouch(touch: touches.first)
	}
	
	// =================================================================================
	
	override func touchesEnded(_ touches: Set<UITouch>, with event: UIEvent?)
	{
		handleTouch(touch: touches.first)
	}
	
	// =================================================================================
	
	func handleTouch(touch:UITouch?)
	{
		guard let touchpoint = touch?.location(in:map) else
		{
			return
		}
		
		let coord = map.convert(touchpoint, toCoordinateFrom:map)
		let index = game.board.pixelIndexForGPSLocation(location: coord)
		let now = Date()
		let travelTime = now.timeIntervalSince(lastTouchTime)
		
		// if at least one of the points is on the board, draw the line
		if (index >= 0) || (lastIndex >= 0)
		{
			game.board.paintLine(from:lastCoord, to:coord, travelTime:travelTime, forPlayer:game.me!)
		}
		
		lastCoord = coord
		lastTouchTime = now
		lastIndex = index
	}
	
	// =================================================================================
	//								  GameBoardDelegate
	// =================================================================================
	
	func boardUpdated(pixels: [PixelUpdate])
	{
		map.boardRenderer.updatePixels(pixels)
		minimap.updatePixels(pixels)
	}
	
	// =================================================================================
	//								ItemPickerViewDelegate
	// =================================================================================
	
	func itemPicker(_ picker: ItemPickerView, pickedItem item: ItemType)
	{
		switch (item)
		{
			case .generic: game.me?.team = .red
			case .bomb: game.me?.team = .blue
//			case .greenShell: game.me?.team = .green
			default: game.me?.team = .green
		}
	}
	
	// =================================================================================
	//								UIViewController
	// =================================================================================
	
	func createMinimap()
	{
		let MINIMAP_PADDING:CGFloat = 7
		let MAX_MINIMAP_SIZE:CGFloat = 120
		
		let minimapWidth:CGFloat
		let minimapHeight:CGFloat
		
		minimap = Minimap(newBoard:game.board)
		
		if let imageSize = minimap.image?.size
		{
			if (imageSize.width > imageSize.height)
			{
				minimapWidth = MAX_MINIMAP_SIZE
				minimapHeight = (imageSize.height / imageSize.width) * minimapWidth
			}
			else
			{
				minimapHeight = MAX_MINIMAP_SIZE
				minimapWidth = (imageSize.width / imageSize.height) * minimapHeight
			}
		}
		else
		{
			minimapWidth = 0
			minimapHeight = 0
		}
		
		minimap.frame = CGRect(x:MINIMAP_PADDING,
		                       y:itemPicker.frame.origin.y - (MINIMAP_PADDING + minimapHeight),
		                       width:minimapWidth,
		                       height:minimapHeight)
		self.view.addSubview(minimap)
	}
	
	// =================================================================================
	
    override func viewDidLoad()
	{
        super.viewDidLoad()

		game.board.delegate = self

		map = GameMapView(game:game)
		map.frame = CGRect(x:0, y:0, width:self.view.frame.size.width, height:itemPicker.frame.origin.y)
		self.view.addSubview(map)
		
		// add some default items for testing
		itemPicker.addItem(type:.generic)
		itemPicker.addItem(type:.bomb)
		itemPicker.addItem(type:.bomb)
		itemPicker.addItem(type:.bomb)
		itemPicker.delegate = self
		
		self.createMinimap()
		
		// used to intercept touches, allowing us to process them instead of the map (top half of screen)
//		let touchFrame = CGRect(x:0, y:0, width:self.view.frame.size.width, height:self.view.frame.size.height / 2)
//		self.view.addSubview(UIView(frame:touchFrame))
		
		let from = CLLocationCoordinate2DMake(20, 20)
		let to = CLLocationCoordinate2DMake(30, 30)
		game.board.paintLine(from:from, to:to, travelTime:1.0, forPlayer:game.me!)
    }

	// =================================================================================
	
	override var prefersStatusBarHidden: Bool
	{
		return true
	}
	
	// =================================================================================
}

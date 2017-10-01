//
//  GameViewController.swift
//  Splatoonio
//
//  Created by Adam Evans on 8/30/17.
//  Copyright © 2017 Kijug Software. All rights reserved.
//

import UIKit
import MapKit


class GameViewController: UIViewController, ItemPickerViewDelegate, GameBoardDelegate, GameMenuViewDelegate
{
	var game:Game!
	
	private var lastCoord:CLLocationCoordinate2D!
	private var lastTouchTime:Date!
	private var lastIndex:Int!
	private var minimap:Minimap!
	private var map:GameMapView!
	private var menu:GameMenuView!
	
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
			let updates = game.board.paintLine(from:lastCoord, to:lastCoord, travelTime:1.0, forPlayer:game.me!)
			game.board.updatePixels(pixels:updates)
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
		
		// if at least one of the points is on the board, draw the line
		if (index >= 0) || (lastIndex >= 0)
		{
			if let me = game.me
			{
				let location = CLLocation(coordinate:coord, altitude:0, horizontalAccuracy:0, verticalAccuracy:0, course:0, speed:0, timestamp:now)
				game.move(player:me.id, to:location)
			}
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
		// the game model has been updated, so forward those updates to the UI components
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
	//								   GameMenuDelegate
	// =================================================================================
	
	func menuItemPressed(item: GameMenuItemType)
	{
		if (item == .quit)
		{
			if let menu = self.navigationController?.viewControllers[0]
			{
				self.navigationController?.popToViewController(menu, animated:true)
			}
		}
		else if (item == .settings)
		{
			
		}
		else if (item == .toggleMinimap)
		{
			let current = UserDefaults.standard.bool(forKey:SETTING_MINIMAP_ON)
			minimap.isHidden = !current
			UserDefaults.standard.set(!current, forKey:SETTING_MINIMAP_ON)
		}
	}
	
	// =================================================================================
	//                                 UIViewController
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
		
		minimap.frame = CGRect(x:self.view.bounds.size.width - (MINIMAP_PADDING + minimapWidth),
		                       y:MINIMAP_PADDING,
		                       width:minimapWidth,
		                       height:minimapHeight)
		minimap.isHidden = UserDefaults.standard.bool(forKey:SETTING_MINIMAP_ON)
		self.view.addSubview(minimap)
	}
	
	// =================================================================================
	
	func createMenu()
	{
		let PADDING:CGFloat = 0
		let WIDTH:CGFloat = self.view.frame.size.width
		
		menu = GameMenuView(expandUpward:true, iconOnLeft:false)
		menu.delegate = self
		menu.frame.origin = CGPoint(x:WIDTH - (PADDING + menu.frame.size.width), y:itemPicker.frame.origin.y - (PADDING + menu.frame.size.height))
		menu.updateUI()
		
		self.view.addSubview(menu)
	}
	
	// =================================================================================
	
    override func viewDidLoad()
	{
        super.viewDidLoad()

		game.board.delegate = self

		map = GameMapView(game:game)
		map.frame = CGRect(x:0, y:0, width:self.view.frame.size.width, height:itemPicker.frame.origin.y)
		self.view.insertSubview(map, at:0)
		
		// add some default items for testing
		itemPicker.addItem(type:.generic)
		itemPicker.addItem(type:.bomb)
		itemPicker.addItem(type:.bomb)
		itemPicker.addItem(type:.bomb)
		itemPicker.delegate = self
		
		self.createMinimap()
		self.createMenu()
    }

	// =================================================================================
	
	override var prefersStatusBarHidden: Bool
	{
		return true
	}
	
	// =================================================================================
}

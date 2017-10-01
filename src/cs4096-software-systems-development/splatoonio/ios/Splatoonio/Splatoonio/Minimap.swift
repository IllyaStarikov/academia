//
//  Minimap.swift
//  Splatoonio
//
//  Created by Adam Evans on 9/12/17.
//  Copyright © 2017 Kijug Software. All rights reserved.
//

import UIKit


class Minimap: UIImageView
{
	private var board:GameBoard!
	private var imageData:UnsafeMutableRawBufferPointer! 
	private var imageContext:CGContext!
	
	private let bitmapInfo:UInt32 = UInt32(CGBitmapInfo.byteOrder32Big.rawValue) | UInt32(CGImageAlphaInfo.premultipliedLast.rawValue)
	
	var gameBoard:GameBoard!
	{
		get
		{
			return board
		}
		set
		{
			setBoard(newBoard:newValue)
		}
	}
	
	// =================================================================================
	//									Initializers
	// =================================================================================
	
	init?(newBoard:GameBoard)
	{
		super.init(image:nil)
		
		self.layer.borderWidth = 2
		self.layer.borderColor = UIColor.black.cgColor
		self.alpha = CGFloat(UserDefaults.standard.integer(forKey:SETTING_MINIMAP_ALPHA)) / 255.0
		
		gameBoard = newBoard
		
		if let image = imageContext.makeImage()
		{
			self.image = UIImage(cgImage:image)
		}
	}
	
	// =================================================================================
	
	required init?(coder aDecoder: NSCoder)
	{
		super.init(coder:aDecoder)
		
		self.layer.borderWidth = 2
		self.layer.borderColor = UIColor.black.cgColor
		self.alpha = CGFloat(UserDefaults.standard.integer(forKey:SETTING_MINIMAP_ALPHA)) / 255.0
	}
	
	// =================================================================================
	//								Image Buffer Management
	// =================================================================================
	
	func updatePixels(_ pixels: [PixelUpdate])
	{
		// update the changed pixels in the image
		for update in pixels
		{
			let index = 4 * update.index
			let rgb = update.team.color()
			
			imageData[index + 0] = rgb.r
			imageData[index + 1] = rgb.g
			imageData[index + 2] = rgb.b
			imageData[index + 3] = 255
		}
		
		// create an image
		if let image = imageContext.makeImage()
		{
			self.image = UIImage(cgImage:image)
		}
	}
	
	// =================================================================================
	
	private func setBoard(newBoard:GameBoard)
	{
		// free old context data
		if (imageData != nil)
		{
			imageData.deallocate()
		}
		
		// initialize new context data
		board = newBoard
		
		let contextBuffer = UnsafeMutableRawPointer.allocate(bytes:4 * board.width * board.height, alignedTo:MemoryLayout<UInt8>.alignment)
		imageData = UnsafeMutableRawBufferPointer(start:contextBuffer, count:4 * board.width * board.height)
		
		// initialize to transparent gray background
//		let alpha = UInt8(UserDefaults.standard.integer(forKey:SETTING_MINIMAP_ALPHA)
		var i = 0
		
		while i < 4 * board.width * board.height
		{
			imageData[i + 0] = 0
			imageData[i + 1] = 0
			imageData[i + 2] = 0
			imageData[i + 3] = 255
			i += 4
		}
		
		if let context = CGContext(data: contextBuffer,
		                           width: board.width,
		                           height: board.height,
		                           bitsPerComponent: 8,
		                           bytesPerRow: 4 * board.width,
		                           space: CGColorSpaceCreateDeviceRGB(),
		                           bitmapInfo: bitmapInfo)
		{
			imageContext = context
		}
		else
		{
			print("ERROR: Could not create minimap context")
			return
		}
		
		if let image = imageContext.makeImage()
		{
			self.image = UIImage(cgImage:image)
		}
		else
		{
			print("ERROR: Could not create image from minimap context")
			return
		}
	}
	
	// =================================================================================
}

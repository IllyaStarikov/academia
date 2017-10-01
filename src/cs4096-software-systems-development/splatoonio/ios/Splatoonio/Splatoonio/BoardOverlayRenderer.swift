//
//  BoardOverlayRenderer.swift
//  Splatoonio
//
//  Created by Adam Evans on 9/2/17.
//  Copyright © 2017 Kijug Software. All rights reserved.
//

import UIKit
import MapKit


class BoardOverlayRenderer: MKOverlayRenderer
{
	private var board:GameBoard
	private var imageData:[UInt8]
	private var imageContext:CGContext
	
	private let bitmapInfo:UInt32 = UInt32(CGBitmapInfo.byteOrder32Big.rawValue) | UInt32(CGImageAlphaInfo.premultipliedLast.rawValue)
	
	var gameBoard:GameBoard
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
	
	init?(boardOverlay:BoardOverlay)
	{
		let width = boardOverlay.board.width
		let height = boardOverlay.board.height
		imageData = [UInt8](repeating:0, count:4 * width * height)
		
		guard let inboard = boardOverlay.board,
			  let context = CGContext(data:&imageData,
			                          width:width,
			                          height:height,
			                          bitsPerComponent:8,
			                          bytesPerRow:4 * width,
			                          space:CGColorSpaceCreateDeviceRGB(),
			                          bitmapInfo:bitmapInfo) else
		{
			print("ERROR: Could not create overlay renderer with board overlay \(boardOverlay)")
			return nil
		}
		
		imageContext = context
		board = inboard
		
		super.init(overlay:boardOverlay)
	}
	
	// =================================================================================
	//									MKOverlayRenderer
	// =================================================================================
	
	override func draw(_ mapRect: MKMapRect, zoomScale: MKZoomScale, in context: CGContext)
	{
		let boardContext = imageContext
		
		let rect = self.rect(for:self.overlay.boundingMapRect)
		let landUnitWidth = rect.size.width / CGFloat(board.width)
		
		if let image = boardContext.makeImage()
		{
			// have to invert the context in the y axis to make the board image draw right side up
			context.scaleBy(x:1.0, y:-1.0)
			context.translateBy(x:0.0, y:-rect.size.height)
			context.draw(image, in:rect)
		}
		
		// draw the border
		context.setStrokeColor(UIColor.black.cgColor)
		context.stroke(rect, width:landUnitWidth)
	}
	
	// =================================================================================
	//								Image Buffer Management
	// =================================================================================
	
	func updatePixels(_ pixels: [PixelUpdate])
	{
		let alpha:UInt8 = UInt8(UserDefaults.standard.integer(forKey:SETTING_PAINT_ALPHA))
		let alphaFactor = Float(Float(alpha) / 255.0)
		
		// update the changed pixels in the image
		for update in pixels
		{
			let index = 4 * update.index
			let rgb = update.team.color()
			
			imageData[index + 0] = UInt8(Float(rgb.r) * alphaFactor)
			imageData[index + 1] = UInt8(Float(rgb.g) * alphaFactor)
			imageData[index + 2] = UInt8(Float(rgb.b) * alphaFactor)
			imageData[index + 3] = alpha
		}
		
		// TODO: pass the rect encompassing the updated pixels to reduce drawing
		self.setNeedsDisplay()
	}
	
	// =================================================================================
	
	private func setBoard(newBoard:GameBoard)
	{
		let width = newBoard.width
		let height = newBoard.height
		
		board = newBoard
		imageData = [UInt8](repeating:0, count:4 * width * height)
		
		guard let context = CGContext(data:&imageData,
		                              width:width,
		                              height:height,
		                              bitsPerComponent:8,
		                              bytesPerRow:4 * width,
		                              space:CGColorSpaceCreateDeviceRGB(),
		                              bitmapInfo:bitmapInfo) else
		{
			print("ERROR: Could not set boardOverlayRenderer.board to \(board)")
			return
		}
		
		imageContext = context
	}
	
	// =================================================================================
}

















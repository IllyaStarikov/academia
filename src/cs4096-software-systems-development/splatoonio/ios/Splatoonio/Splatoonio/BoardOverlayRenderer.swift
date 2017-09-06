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
	var board:GameBoard!
	
	// =================================================================================
	//									MKOverlayRenderer
	// =================================================================================
	
	override func draw(_ mapRect: MKMapRect, zoomScale: MKZoomScale, in context: CGContext)
	{
		if (board == nil)
		{
			return
		}
		
		print("rendering...")
		let width = board.width
		let height = board.height
		
		let rect = self.rect(for:self.overlay.boundingMapRect)
		let landUnitWidth = rect.size.width / CGFloat(board.width)
		let landUnitHeight = rect.size.height / CGFloat(board.height)
		print("context size=\(context.width, context.height)")
		
//		context.setFillColor(red:0.5, green:0.5, blue:0.5, alpha:0.6)
//		context.fill(rect)
		
		context.scaleBy(x:1.0, y:-1.0)
		context.translateBy(x:0.0, y:-rect.size.height)
		
		// for testing
		for i in 0..<80
		{
			for j in 0..<80
			{
				let team = TeamColor(rawValue:Int(arc4random() % UInt32(TeamColor.count.rawValue)))!
				board.setBoardColor(row:i, col:j, color:team)
			}
		}
		
		// Draw the land units
		for teamValue in 0..<TeamColor.count.rawValue
		{
			// set the color for this team
			let teamColor = TeamColor(rawValue:teamValue)!
			let rgb = teamColor.color()
			let r = CGFloat(rgb.r) / 255.0
			let g = CGFloat(rgb.g) / 255.0
			let b = CGFloat(rgb.b) / 255.0
			
			context.setFillColor(red:r, green:g, blue:b, alpha:0.4)
			
			// draw all the pixels for this team color
			var i:Int = 0
			var j:Int = 0
			
			while (i < height)
			{
				j = 0
				
				while (j < width)
				{
					if (board.getBoardColor(row:i, col:j) == teamColor)
					{
						// compute the pixel rect bounds
						let rect = CGRect(x:CGFloat(Int(rect.origin.x + (CGFloat(j) * landUnitWidth))),
						                  y:CGFloat(Int(rect.origin.y + (CGFloat(i) * landUnitHeight))),
						                  width:landUnitWidth,
						                  height:landUnitHeight)
						context.fill(rect)
					}
					
					j += 1
				}
				
				i += 1
			}
		}
	}
	
	// =================================================================================
}

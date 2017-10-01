//
//  MyUtilities.swift
//  Splatoonio
//
//  Created by Adam Evans on 8/30/17.
//  Copyright © 2017 Kijug Software. All rights reserved.
//

import UIKit
import CoreGraphics
import CoreLocation


class MyUtilities
{
	// =================================================================================
	
	class func circleImageWithColor(color:UIColor, radius:CGFloat) -> UIImage!
	{
		let size = Int(radius + radius)
		let colorSpace = CGColorSpace(name: CGColorSpace.sRGB)!
		let context = CGContext(data:nil,
		                        width:size,
		                        height:size,
		                        bitsPerComponent:8,
		                        bytesPerRow:4 * size,
		                        space:colorSpace,
		                        bitmapInfo:UInt32(CGBitmapInfo.byteOrder32Little.rawValue) | UInt32(CGImageAlphaInfo.premultipliedLast.rawValue))
		
		if let c = context
		{
			c.setFillColor(color.cgColor)
			c.fillEllipse(in: CGRect(x:0, y:0, width:size, height:size))
			
			return UIImage(cgImage:c.makeImage()!)
		}
		
		return nil
	}
	
	// =================================================================================
	
	class func roundedRectImage(color:UIColor, width:Int, height:Int, radius:CGFloat) -> UIImage!
	{
		let size = Int(radius + radius)
		let colorSpace = CGColorSpace(name: CGColorSpace.sRGB)!
		let context = CGContext(data:nil,
		                        width:width,
		                        height:height,
		                        bitsPerComponent:8,
		                        bytesPerRow:4 * width,
		                        space:colorSpace,
		                        bitmapInfo:UInt32(CGBitmapInfo.byteOrder32Little.rawValue) | UInt32(CGImageAlphaInfo.premultipliedLast.rawValue))
		
		if let c = context
		{
			c.setFillColor(color.cgColor)
			c.fillEllipse(in: CGRect(x:0, y:0, width:size, height:size))							// topLeft
			c.fillEllipse(in: CGRect(x:width - size, y:0, width:size, height:size))					// topRight
			c.fillEllipse(in: CGRect(x:0, y:height - size, width:size, height:size))				// botLeft
			c.fillEllipse(in: CGRect(x:width - size, y:height - size, width:size, height:size))		// botRight
			c.fill(CGRect(x:Int(radius), y:0, width:width - size, height:height))
			c.fill(CGRect(x:0, y:Int(radius), width:width, height:height - size))
			
			return UIImage(cgImage: context!.makeImage()!)
		}
		
		return nil
	}
	
	// =================================================================================
	
	class func normalizedGPSLocation(location:CLLocationCoordinate2D) -> CLLocationCoordinate2D
	{
		var answer = CLLocationCoordinate2D(latitude:location.latitude, longitude:location.longitude)
		
		var factor = Int((answer.latitude + 90) / 180)
		answer.latitude -= Double(180 * factor)
		answer.latitude += 90
		
		factor = Int((answer.longitude + 180) / 360)
		answer.longitude -= Double(360 * factor)
		answer.longitude += 180
		
		return answer;
	}
	
	// =================================================================================
}







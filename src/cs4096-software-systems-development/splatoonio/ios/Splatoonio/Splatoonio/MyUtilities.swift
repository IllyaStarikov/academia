//
//  MyUtilities.swift
//  Splatoonio
//
//  Created by Adam Evans on 8/30/17.
//  Copyright © 2017 Kijug Software. All rights reserved.
//

import UIKit
import CoreGraphics


class MyUtilities
{
	class func circleImageWithColor(color:UIColor, radius:CGFloat) -> UIImage
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
		
		context?.setFillColor(color.cgColor)
		context?.fillEllipse(in: CGRect(x:0, y:0, width:size, height:size))
		
		return UIImage(cgImage: context!.makeImage()!)
	}
}

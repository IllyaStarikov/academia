//
//  MyUtilities.m
//  Splatoonio
//
//  Created by Adam Evans on 8/28/17.
//  Copyright © 2017 Kijug Software. All rights reserved.
//

#import "MyUtilities.h"


@implementation MyUtilities


// =================================================================================

+ (UIImage*)circleImageWithColor:(UIColor*)color size:(int)size
{
	uint8_t* data = (uint8_t*)calloc(sizeof(uint8_t), size * size * 4);
	CGColorSpaceRef colorSpace = CGColorSpaceCreateDeviceRGB();
	CGContextRef context = CGBitmapContextCreate(data, size, size, 8, 4 * size, colorSpace, kCGBitmapByteOrderDefault | kCGImageAlphaPremultipliedLast);
	
	CGContextSetFillColorWithColor(context, color.CGColor);
	CGContextFillEllipseInRect(context, CGRectMake(0, 0, size, size));
	
	CGImageRef cgimage = CGBitmapContextCreateImage(context);
	UIImage* image = [UIImage imageWithCGImage:cgimage];
	
	CGImageRelease(cgimage);
	CGContextRelease(context);
	CGColorSpaceRelease(colorSpace);
	
	return image;
	
//	int center = size / 2;
//	int hypotenuse = size * size;
//	
//	for (int i = 0; i < size; i++)
//	{
//		for (int j = 0; j < size; j++)
//		{
//			int x = j - center;
//			int y = i - center;
//			
//			if ((x * x) + (y * y) <= hypotenuse)
//			{
//				
//			}
//		}
//	}
}

// =================================================================================



@end

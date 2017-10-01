//
//  GameMenuItem.swift
//  Splatoonio
//
//  Created by Adam Evans on 9/25/17.
//  Copyright © 2017 Kijug Software. All rights reserved.
//

import UIKit


class GameMenuItem: UIView
{
	static let HPADDING:CGFloat = 10
	static let BORDER_SIZE:CGFloat = 10
	static let ICON_SIZE:CGFloat = 30
	
	var type:GameMenuItemType
	var button:UIButton
	var label:UILabel
	var icon:UIImageView?
	var iconOnLeft:Bool
	var background:UIImageView
	
	// =================================================================================
	//									Initializers
	// =================================================================================
	
	init(type inType:GameMenuItemType, iconOnLeft left:Bool, action:Selector, target:AnyObject)
	{
		type = inType
		iconOnLeft = left
		
		label = UILabel()
		label.text = type.title()
		button = UIButton(type:.custom)
		button.tag = type.rawValue
		button.addTarget(target, action:action, for:.touchUpInside)
		
		if let image = type.icon()
		{
			icon = UIImageView(image:image)
			icon!.frame.size = CGSize(width:GameMenuItem.ICON_SIZE, height:GameMenuItem.ICON_SIZE)
		}
		
		background = UIImageView()
		background.alpha = 0.2
		
		super.init(frame:.zero)
		
		self.addSubview(background)
		
		if let imageview = icon
		{
			self.addSubview(imageview)
		}
		
		self.addSubview(label)
		self.addSubview(button)
		
		layoutSubviews()
	}
	
	// =================================================================================
	
	required init?(coder aDecoder: NSCoder)
	{
		type = .none
		iconOnLeft = true
		label = UILabel()
		button = UIButton(type:.custom)
		icon = nil
		background = UIImageView()
		
		super.init(coder:aDecoder)
		
		self.addSubview(background)
		self.addSubview(label)
		self.addSubview(button)
		self.layoutSubviews()
	}
	
	// =================================================================================
	//									Normal Functions
	// =================================================================================
	
	override func layoutSubviews()
	{
		label.sizeToFit()
		label.frame.size.width += GameMenuItem.HPADDING
		
		// calculate the overall size of this menu item
		var width:CGFloat = label.frame.size.width + GameMenuItem.BORDER_SIZE
		var height:CGFloat = label.frame.size.height + (2 * GameMenuItem.BORDER_SIZE)
		
		if let imageview = icon
		{
			width += imageview.frame.size.width + GameMenuItem.HPADDING
			
			if (imageview.frame.size.height > height)
			{
				height = imageview.frame.size.height
			}
		}
		
		if (self.frame.size.width < width)
		{
			self.frame.size.width = width
		}
		if (self.frame.size.height < height)
		{
			self.frame.size.height = height
		}
		
		// ------------------------------------
		// layout all the subviews
		let w = Int(width * UIScreen.main.scale)
		let h = Int(height * UIScreen.main.scale)
		background.image = MyUtilities.roundedRectImage(color:.black, width:w, height:h, radius:10)
		
		if (iconOnLeft)
		{
			var x:CGFloat = GameMenuItem.BORDER_SIZE
			
			if let imageview = icon
			{
				imageview.center = CGPoint(x:imageview.frame.size.width / 2, y:self.frame.size.height / 2)
				x += imageview.frame.size.width + GameMenuItem.HPADDING
			}
			
			label.center = CGPoint(x:x + (label.frame.size.width / 2), y:self.frame.size.height / 2)
			label.textAlignment = .left
			background.frame = CGRect(x:0, y:0, width:width, height:height)
		}
		else
		{
			var x = self.frame.width - GameMenuItem.BORDER_SIZE
			
			if let imageview = icon
			{
				let tempx = x - (imageview.frame.size.width / 2)
				imageview.center = CGPoint(x:tempx, y:self.frame.size.height / 2)
				
				x = imageview.frame.origin.x - GameMenuItem.HPADDING
			}
			
			label.center = CGPoint(x:x - (label.frame.size.width / 2), y:self.frame.size.height / 2)
			label.textAlignment = .right
			background.frame = CGRect(x:self.frame.size.width - width, y:0, width:width, height:height)
		}
		
		button.frame = self.bounds
	}
	
	// =================================================================================
}

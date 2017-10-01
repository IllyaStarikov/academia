//
//  GameMenuView.swift
//  Splatoonio
//
//  Created by Adam Evans on 9/25/17.
//  Copyright © 2017 Kijug Software. All rights reserved.
//

import UIKit


protocol GameMenuViewDelegate
{
	func menuItemPressed(item:GameMenuItemType)
}


class GameMenuView: UIView
{
	static let VPADDING:CGFloat = 5		// padding between menu item rows
	static let BORDER_SIZE:CGFloat = 10		// padding around the menu items
	
	private var iconOnLeftBacker:Bool
	private var expanded:Bool
	private var expandedWidth:CGFloat
	private var expandedHeight:CGFloat
	private var expandItem:GameMenuItem!      // the item from menuItems that triggers expanding and contracting
	private var menuItems:[GameMenuItem]
	
	var delegate:GameMenuViewDelegate?
	var expandUpward:Bool                // true to expand upward and contract downward, false for the reverse
	var iconOnLeft:Bool
	{
		get
		{
			return iconOnLeftBacker
		}
		set
		{
			iconOnLeftBacker = newValue
			
			for item in menuItems
			{
				item.iconOnLeft = iconOnLeftBacker
			}
			
			self.updateUI()
		}
	}
	
	// =================================================================================
	//									Initializers
	// =================================================================================
	
	init(expandUpward expandUp:Bool, iconOnLeft leftIcon:Bool)
	{
		iconOnLeftBacker = leftIcon
		expanded = false
		expandedWidth = 0
		expandedHeight = 0
		menuItems = [GameMenuItem]()
		
		delegate = nil
		expandUpward = expandUp
		
		super.init(frame:.zero)
		
		populateMenu()
	}
	
	// =================================================================================
	
	required init?(coder aDecoder: NSCoder)
	{
		iconOnLeftBacker = true
		expanded = false
		expandedWidth = 0
		expandedHeight = 0
		menuItems = [GameMenuItem]()
		
		delegate = nil
		expandUpward = false		
		
		super.init(coder:aDecoder)
		
		populateMenu()
	}
	
	// =================================================================================
	
	func populateMenu()
	{
		let action = #selector(self.menuItemPressed(sender:))
		var types:[GameMenuItemType] = [.quit, .settings, .toggleMinimap]
		
		// put the expand/contract button close to the anchor point
		if (expandUpward)
		{
			types.append(.expand)
		}
		else
		{
			types.insert(.expand, at:0)
		}
		
		// configure each menu item
		var y:CGFloat = GameMenuView.BORDER_SIZE
		
		for i in 0..<types.count
		{
			let item = GameMenuItem(type:types[i], iconOnLeft:iconOnLeft, action:action, target:self)
			item.frame.origin = CGPoint(x:GameMenuItem.BORDER_SIZE, y:y)
			
			y += item.frame.size.height
			
			if (i != self.menuItems.count - 1)
			{
				y += GameMenuView.VPADDING
			}
			
			if (item.frame.size.width > expandedWidth)
			{
				expandedWidth = item.frame.size.width
			}
			
			expandedHeight += item.frame.size.height
			
			if (types[i] == .expand)
			{
				expandItem = item
			}
			
			menuItems.append(item)
			self.addSubview(item)
		}
		
		// account for paddings
		expandedHeight += CGFloat(types.count - 1) * GameMenuView.VPADDING
		expandedHeight += 2 * GameMenuView.BORDER_SIZE
		expandedWidth += 2 * GameMenuView.BORDER_SIZE
		
		// have to do this separate since we need expandedWidth computed first
		for item in menuItems
		{
			item.frame.size.width = expandedWidth - (2 * GameMenuView.BORDER_SIZE)
		}
		
		self.frame.size = CGSize(width:self.expandedWidth, height:self.expandedHeight)
		
		updateUI()
	}
	
	// =================================================================================
	//								  Normal Functions
	// =================================================================================
	
	func menuItemPressed(sender:UIView)
	{
		if (expanded)
		{
			if let item = GameMenuItemType(rawValue:sender.tag)
			{
				if (item == .expand)
				{
					contract()
				}
				else
				{
					delegate?.menuItemPressed(item:item)
				}
			}
		}
		else
		{
			expand()
		}
	}
	
	// =================================================================================
	
	func updateUI()
	{
		// reload all the menu items
		for item in menuItems
		{
			item.layoutSubviews()
		}
		
		if (expanded)
		{
			expand()
		}
		else
		{
			contract()
		}
	}
	
	// =================================================================================
	
	func expand()
	{
		let animator = UIViewPropertyAnimator(duration:0.2, curve:.easeInOut, animations: {() -> Void in
			if (self.expandUpward)
			{
				self.frame.origin.y = self.frame.maxY - self.expandedHeight
			}
			
			self.frame.size = CGSize(width:self.expandedWidth, height:self.expandedHeight)
			
			// layout the menu items
			var y:CGFloat = GameMenuView.BORDER_SIZE
			
			for i in 0..<self.menuItems.count
			{
				self.menuItems[i].frame.origin.y = y
				self.menuItems[i].alpha = 1
				
				y += self.menuItems[i].frame.size.height
				
				if (i != self.menuItems.count - 1)
				{
					y += GameMenuView.VPADDING
				}
			}
		})
		
		animator.addCompletion({(_:UIViewAnimatingPosition) -> Void in
			if let item = self.expandItem
			{
				item.label.text = "Hide"
			}
		})
		
		animator.startAnimation()
		expanded = true
	}
	
	// =================================================================================
	
	func contract()
	{
		let animator = UIViewPropertyAnimator(duration:0.2, curve:.easeInOut, animations: {() -> Void in
			for item in self.menuItems
			{
				item.alpha = 0
				item.frame.origin.y = GameMenuView.BORDER_SIZE
			}
			
			if let item = self.expandItem
			{
				item.alpha = 1
				self.frame.size.height = item.frame.size.height + (2 * GameMenuView.BORDER_SIZE)
				
				if (self.expandUpward && self.expanded)
				{
					self.frame.origin.y += self.expandedHeight - self.frame.size.height
				}
			}
		})
		
		animator.addCompletion({(_:UIViewAnimatingPosition) -> Void in
			if let item = self.expandItem
			{
				item.label.text = "Menu"
			}
		})
		
		animator.startAnimation()
		expanded = false
	}
	
	// =================================================================================
}












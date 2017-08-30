//
//  ItemPickerView.swift
//  Splatoonio
//
//  Created by Adam Evans on 8/30/17.
//  Copyright © 2017 Kijug Software. All rights reserved.
//

import UIKit

class ItemPickerView: UIView
{
	private static let ICON_SIZE:CGFloat					= 40
	private static let MULTIPLICITY_LABEL_OFFSET_X:CGFloat	= ICON_SIZE / 2
	private static let MULTIPLICITY_LABEL_OFFSET_Y:CGFloat	= ICON_SIZE / 2
	private static let MULTIPLICITY_LABEL_WIDTH:CGFloat		= 30
	private static let MULTIPLICITY_LABEL_HEIGHT:CGFloat	= 30
	private static let MULTIPLICITY_LABEL_FONT_SIZE:CGFloat	= 15
	
	private var nslots:Int
	private var itemCounts:[Int]
	private var itemIcons:[UIImageView]
	private var itemButtons:[UIButton]
	private var multiplicityLabels:[UILabel]
	private var selectionBox:UIView
	
	var selectedType:ItemType
	
	// =================================================================================
	//									Initializers
	// =================================================================================
	
	required init?(coder aDecoder: NSCoder)
	{
		nslots = 0
		selectedType = .none
		
		itemCounts			= [Int]			(repeating:0, count:Int(ItemType.count.rawValue))
		itemIcons			= [UIImageView]	(repeating:UIImageView(), count:Int(ItemType.count.rawValue))
		itemButtons			= [UIButton]	(repeating:UIButton(), count:Int(ItemType.count.rawValue))
		multiplicityLabels	= [UILabel]		(repeating:UILabel(), count:Int(ItemType.count.rawValue))
		
		selectionBox = UIView()
		
		super.init(coder:aDecoder)
		
		selectionBox.backgroundColor = .black
		selectionBox.alpha = 0.2
		self.addSubview(selectionBox)
		
		for i in 0 ..< Int(ItemType.count.rawValue)
		{
			let type = ItemType(rawValue:i)!
			
			itemIcons[i] = UIImageView(image: type.icon())
			itemIcons[i].frame = CGRect(x:0, y:0, width:ItemPickerView.ICON_SIZE, height:ItemPickerView.ICON_SIZE)
			self.addSubview(itemIcons[i])
			
			multiplicityLabels[i] = UILabel(frame:CGRect(x:0,
			                                             y:0,
			                                             width:ItemPickerView.MULTIPLICITY_LABEL_WIDTH,
			                                             height:ItemPickerView.MULTIPLICITY_LABEL_HEIGHT))
			multiplicityLabels[i].font = UIFont.systemFont(ofSize:ItemPickerView.MULTIPLICITY_LABEL_FONT_SIZE)
			self.addSubview(multiplicityLabels[i])
		}
	}
	
	// =================================================================================
	//									Touch Functions
	// =================================================================================
	
	override func touchesEnded(_ touches: Set<UITouch>, with event: UIEvent?)
	{
		let loc = touches.first!.location(in:self)
		let slotWidth = self.frame.size.width / CGFloat(nslots)
		let slot = Int(loc.x / slotWidth)
		
		// show the selectionBox
		var type:Int = -1
		var slotCount:Int = 0
		
		while (slotCount <= slot)	// slot >= 0, so this will always loop at least once
		{
			type += 1
			
			if (itemCounts[type] > 0)
			{
				slotCount += 1
			}
		}
		
		selectedType = ItemType(rawValue: type)!
		refreshList()
	}
	
	// =================================================================================
	//									Normal Functions
	// =================================================================================
	
	func addItems(items:[Item])
	{
		for item in items
		{
			itemCounts[item.type.rawValue] += 1
		}
		
		refreshList()
	}
	
	// =================================================================================
	
	func addItem(type:ItemType)
	{
		itemCounts[type.rawValue] += 1
		refreshList()
	}
	
	// =================================================================================
	
	func removeItem(type:ItemType)
	{
		if (itemCounts[type.rawValue] > 0)
		{
			itemCounts[type.rawValue] -= 1
			refreshList()
		}
	}
	
	// =================================================================================
	
	func refreshList()
	{
		// figure out how many different item "slots" we need to show
		nslots = 0
		
		for i in 0..<ItemType.count.rawValue
		{
			if (itemCounts[i] > 0)
			{
				nslots += 1
			}
		}
		
		let SIDE_PADDING:CGFloat = 0
		let SLOT_WIDTH:CGFloat = (self.frame.size.width - (2 * SIDE_PADDING)) / CGFloat(nslots)
		
		// ------------------------------------
		// setup selection
		if (selectedType == .none)
		{
			selectionBox.isHidden = true
		}
		else if (itemCounts[selectedType.rawValue] == 0)
		{
			selectionBox.isHidden = true
			selectedType = .none
		}
		else
		{
			var selectedSlot = 0
			
			// figure out which slot has the items of the selected type
			for i in 0..<selectedType.rawValue
			{
				if (itemCounts[i] > 0)
				{
					selectedSlot += 1
				}
			}
			
			// configure the selection box
			selectionBox.isHidden = false
			selectionBox.frame = CGRect(x:SLOT_WIDTH * CGFloat(selectedSlot), y:0, width:SLOT_WIDTH, height:self.frame.size.height)
		}
		
		// ------------------------------------
		// put all the UI components where they need to go
		var x:CGFloat = SIDE_PADDING
		let ICON_CENTER_Y:CGFloat = self.frame.size.height / 2
		
		for i in 0..<ItemType.count.rawValue
		{
			// check if this item type shouldn't be displayed
			if (itemCounts[i] == 0)
			{
				itemIcons[i].isHidden = true
				multiplicityLabels[i].isHidden = true
				continue
			}
			
			// configure the icon
			itemIcons[i].isHidden = false
			itemIcons[i].center = CGPoint(x:x + (SLOT_WIDTH / 2), y:ICON_CENTER_Y)
			
			// configure the multiplicity label
			if (itemCounts[i] == 1)
			{
				multiplicityLabels[i].isHidden = true
			}
			else
			{
				multiplicityLabels[i].isHidden = false
				multiplicityLabels[i].text = "x\(itemCounts[i])"
				multiplicityLabels[i].sizeToFit()
				multiplicityLabels[i].center = CGPoint(x: itemIcons[i].center.x + ItemPickerView.MULTIPLICITY_LABEL_OFFSET_X,
				                                       y: itemIcons[i].center.y + ItemPickerView.MULTIPLICITY_LABEL_OFFSET_Y)
			}
			
			x += SLOT_WIDTH
		}
	}
	
	// =================================================================================


}












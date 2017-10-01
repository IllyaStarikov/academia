//
//  OptionsViewController.swift
//  Splatoonio
//
//  Created by Adam Evans on 9/30/17.
//  Copyright © 2017 Kijug Software. All rights reserved.
//

import UIKit

class OptionsViewController: UIViewController
{
	let defaults = UserDefaults.standard
	
	// =================================================================================
	//							Change Settings Functions 
	// =================================================================================
	
	func toggleSounds(sender:AnyObject)
	{
		let value = (sender as! UISwitch).isOn
		defaults.set(value, forKey:SETTING_SOUNDS_ON)
		defaults.synchronize()
	}
	
	// =================================================================================
	
	func toggleMinimap(sender:AnyObject)
	{
		let value = (sender as! UISwitch).isOn
		defaults.set(value, forKey:SETTING_MINIMAP_ON)
		defaults.synchronize()
	}
	
	// =================================================================================
	
	func changeMinimapTransparency(sender:AnyObject)
	{
		let value = Int((sender as! UISlider).value)
		defaults.set(value, forKey:SETTING_MINIMAP_ALPHA)
		defaults.synchronize()
	}
	
	// =================================================================================
	
	func changePaintTransparency(sender:AnyObject)
	{
		let value = Int((sender as! UISlider).value)
		defaults.set(value, forKey:SETTING_PAINT_ALPHA)
		defaults.synchronize()
	}
	
	// =================================================================================
	//								Other UI Functions
	// =================================================================================
	
	func backPressed(_:UIView)
	{
		self.navigationController?.popViewController(animated:true)
	}
	
	// =================================================================================
	//								UIViewController
	// =================================================================================
	
	func setupUI()
	{
		let width = self.view.frame.size.width
		let PADDING:CGFloat = 10				// space between views in self.view
		let BORDER:CGFloat = 10					// space between the edge of self.view's frame and the section frames
		let OUTER_PADDING:CGFloat = 10			// space between the edge of a section's frame and its subviews
		let SECTION_WIDTH:CGFloat = width - (2 * PADDING)
		
		// create the title label
		let title = UILabel()
		title.text = "Options"
		title.font = UIFont.systemFont(ofSize:40)
		title.sizeToFit()
		title.center = CGPoint(x:width / 2, y:(2 * PADDING) + (title.frame.size.height / 2))
		self.view.addSubview(title)
		
		// create the back button
		let backImage = UIImageView(image:UIImage(named:"backArrow.png"))
		backImage.frame = CGRect(x:14, y:14, width:40, height:40)
		self.view.addSubview(backImage)
		
		let backButton = UIButton(type:.custom)
		backButton.frame = CGRect(x:0, y:0, width:67, height:67)
		backButton.addTarget(self, action:#selector(backPressed(_:)), for:.touchUpInside)
		self.view.addSubview(backButton)
		
		// create the sections
		var y:CGFloat = title.frame.maxY + (2 * PADDING)
		let settingLabels = ["Sounds", "Minimap", "Minimap Transparency", "Paint Transparency"]
		let settingInputs:[UIView] = [UISwitch(), UISwitch(), UISlider(), UISlider()]
		let settingActions = [#selector(toggleSounds(sender:)),
							  #selector(toggleMinimap(sender:)),
		                      #selector(changeMinimapTransparency(sender:)),
		                      #selector(changePaintTransparency(sender:))]
		
		for i in 0..<settingLabels.count
		{
			let sectionFrame = CGRect(x:BORDER, y:y, width:SECTION_WIDTH, height:0)
			let section = UIView(frame:sectionFrame)
			
			// background
			let backgroundImage = UIImageView()
			backgroundImage.alpha = 0.3
			section.addSubview(backgroundImage)
			
			// name of the option/setting
			let label = UILabel()
			label.text = settingLabels[i]
			label.sizeToFit()
			label.center = CGPoint(x:OUTER_PADDING + (label.frame.size.width / 2), y:OUTER_PADDING + (label.frame.size.height / 2))
			section.addSubview(label)
			
			// input control
			(settingInputs[i] as! UIControl).addTarget(self, action:settingActions[i], for:.valueChanged)
			
			if let input = settingInputs[i] as? UISwitch
			{
				// put the switch to the right of the label
				section.frame.size.height = OUTER_PADDING + max(label.frame.size.height, input.frame.size.height) + OUTER_PADDING
				
				input.center = CGPoint(x:section.frame.size.width - (PADDING + input.frame.size.width / 2),
				                       y:section.frame.size.height / 2)
				
				// readjust the label position if the switch is tall enough that it is no longer vertically centered
				if (input.frame.size.height > label.frame.size.height)
				{
					label.center.y = section.frame.size.height / 2
				}
			}
			else if let slider = settingInputs[i] as? UISlider
			{
				// put the slider below the label
				let sliderWidth = section.frame.size.width - (2 * OUTER_PADDING)
				slider.frame = CGRect(x:OUTER_PADDING, y:label.frame.maxY + PADDING, width:sliderWidth, height:slider.frame.size.height)
				section.frame.size.height = OUTER_PADDING + label.frame.size.height + PADDING + slider.frame.size.height + OUTER_PADDING
			}
			
			section.addSubview(settingInputs[i])
			self.view.addSubview(section)
			
			// finalize the background now that we have the final dimensions of the section
			backgroundImage.frame = section.bounds
			backgroundImage.image = MyUtilities.roundedRectImage(color:.black,
			                                                     width:Int(2 * section.frame.size.width),
			                                                     height:Int(2 * section.frame.size.height),
			                                                     radius:10)
			y += section.frame.size.height + PADDING
		}
		
		// set initial values
		(settingInputs[0] as! UISwitch).isOn = defaults.bool(forKey:SETTING_SOUNDS_ON)
		(settingInputs[1] as! UISwitch).isOn = defaults.bool(forKey:SETTING_MINIMAP_ON)
		(settingInputs[2] as! UISlider).minimumValue = 0
		(settingInputs[2] as! UISlider).maximumValue = 255
		(settingInputs[2] as! UISlider).value = Float(defaults.integer(forKey:SETTING_MINIMAP_ALPHA))
		(settingInputs[3] as! UISlider).minimumValue = 0
		(settingInputs[3] as! UISlider).maximumValue = 255
		(settingInputs[3] as! UISlider).value = Float(defaults.integer(forKey:SETTING_PAINT_ALPHA))
	}
	
	// =================================================================================
	
	override func viewDidLoad()
	{
		super.viewDidLoad()
		
		setupUI()
	}
	
	// =================================================================================
	
	override var prefersStatusBarHidden: Bool
	{
		return true
	}
	
	// =================================================================================
}

//
//  LoginView.swift
//  SocketServer
//
//  Created by Illya Starikov on 4/23/17.
//  Copyright © 2017 Illya Starikov. All rights reserved.
//

import UIKit
import SkyFloatingLabelTextField
import FontAwesome_swift


class LoginView: UIView {
    struct Constants {
        static let horizontalPaddingPercentage: CGFloat = 0.10
        static let verticalPadding: CGFloat = 5.0
    }
    
    func generateLabel(withFrame frame: CGRect, labeled label: String, withIconText icon: String) -> SkyFloatingLabelTextField {
        let textField = SkyFloatingLabelTextFieldWithIcon(frame: frame)
        textField.placeholder = label
        textField.title = label
        
        // Set up the Icon
        textField.iconFont = UIFont.fontAwesome(ofSize: 15)
        textField.iconText = icon
        
        // Pretty colors
        textField.tintColor = UIColor.jsq_messageBubbleBlue()
        textField.selectedTitleColor = UIColor.jsq_messageBubbleBlue()
        textField.selectedLineColor = UIColor.jsq_messageBubbleBlue()
        textField.selectedIconColor = UIColor.jsq_messageBubbleBlue()
        
        return textField
    }
    
    override func draw(_ rect: CGRect) {
        let labelWidth = Int(frame.width) - Int(2*Constants.horizontalPaddingPercentage*frame.width)
        let x = Constants.horizontalPaddingPercentage*frame.width
        
        let usernameLabel = generateLabel(withFrame: CGRect(x: Int(x), y: Int(Constants.verticalPadding), width: labelWidth, height: 45), labeled: "Username", withIconText: "\u{f007}")
        let hostnameLabel = generateLabel(withFrame: CGRect(x: Int(x), y: Int(Constants.verticalPadding + usernameLabel.frame.maxY), width: Int(0.45*Double(labelWidth)), height: 45), labeled: "Hostname", withIconText: "\u{f233}")
        let portLabel = generateLabel(withFrame: CGRect(x: Int(hostnameLabel.frame.maxX + 0.1*CGFloat(labelWidth)), y: Int(Constants.verticalPadding + usernameLabel.frame.maxY), width: Int(0.45*Double(labelWidth)), height: 45), labeled: "Port", withIconText: "\u{f108}")

        
        addSubview(hostnameLabel)
        addSubview(usernameLabel)
        addSubview(portLabel)
    }


}

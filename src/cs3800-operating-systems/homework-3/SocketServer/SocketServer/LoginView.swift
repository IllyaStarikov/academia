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


class LoginButton: UIButton {
    override init(frame: CGRect) {
        super.init(frame: frame)
        
        self.layer.cornerRadius = 4.0;
        self.layer.borderColor = UIColor.jsq_messageBubbleBlue().cgColor
        self.layer.borderWidth = 1.5
        
        self.tintColor = UIColor.black
        
        self.setTitleColor(UIColor.jsq_messageBubbleBlue(), for: [])
    }
    
    required init?(coder aDecoder: NSCoder) {
        fatalError("init(coder:) has not been implemented")
    }
}

class LoginView: UIView, UITextFieldDelegate {
    var buttonAction: () -> Void = {}
    
    public var usernameLabel = SkyFloatingLabelTextFieldWithIcon(), hostnameLabel = SkyFloatingLabelTextFieldWithIcon()
    
    public var portLabel = SkyFloatingLabelTextFieldWithIcon() {
        didSet {
            portLabel.errorColor = UIColor.red
            portLabel.delegate = self
        }
    }
    
    public var loginButton = LoginButton() {
        didSet {
            loginButton.addTarget(self, action: #selector(actionSelector), for: .touchDown)
        }
    }
    
    @objc private func actionSelector() {
        buttonAction()
    }
    
    
    func generateLabel(withFrame frame: CGRect, labeled label: String, withIconText icon: String) -> SkyFloatingLabelTextFieldWithIcon {
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
    
    func generateLoginButton(withFrame frame: CGRect) -> LoginButton {
        let button = LoginButton()
        
        button.frame = frame
        button.setTitle("Login", for: [])
        
        return button
    }
    
    override func draw(_ rect: CGRect) {
        let labelWidth = Int(frame.width) - Int(2*Constants.horizontalPaddingPercentage*frame.width)
        let x = Constants.horizontalPaddingPercentage*frame.width
        
        usernameLabel = generateLabel(withFrame: CGRect(x: Int(x), y: Int(0.25*frame.maxY), width: labelWidth, height: 45), labeled: "Username", withIconText: "\u{f007}")
        hostnameLabel = generateLabel(withFrame: CGRect(x: Int(x), y: Int(Constants.verticalPadding + usernameLabel.frame.maxY), width: Int(0.45*Double(labelWidth)), height: 45), labeled: "Hostname", withIconText: "\u{f233}")
        portLabel = generateLabel(withFrame: CGRect(x: Int(hostnameLabel.frame.maxX + 0.1*CGFloat(labelWidth)), y: Int(Constants.verticalPadding + usernameLabel.frame.maxY), width: Int(0.45*Double(labelWidth)), height: 45), labeled: "Port", withIconText: "\u{f108}")
        
        loginButton = generateLoginButton(withFrame: CGRect(x: Int(x), y: Int(Int(3*Constants.verticalPadding + hostnameLabel.frame.maxY)), width: Int(labelWidth), height: 45))
        
        addSubview(hostnameLabel)
        addSubview(usernameLabel)
        addSubview(portLabel)
        addSubview(loginButton)
    }
    
    func textField(_ textField: UITextField, shouldChangeCharactersIn range: NSRange, replacementString string: String) -> Bool {
        if let text = textField.text {
            if let floatingLabelTextField = textField as? SkyFloatingLabelTextField {
                switch floatingLabelTextField.title! {
                case "Port":

                if Int(text) == nil || Int(text)! <= 0 || Int(text)! >= 70_000 {
                    floatingLabelTextField.errorMessage = "Invalid Port"
                } else {
                    floatingLabelTextField.errorMessage = ""
                }
                
                    break
                    
                default:
                    break
                }
            }
        }
        return true
    }
    
    
    
    struct Constants {
        static let horizontalPaddingPercentage: CGFloat = 0.10
        static let verticalPadding: CGFloat = 15.0
    }
}

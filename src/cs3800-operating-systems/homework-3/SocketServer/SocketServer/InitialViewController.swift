//
//  InitialViewController.swift
//  SocketServer
//
//  Created by Illya Starikov on 4/20/17.
//  Copyright © 2017 Illya Starikov. All rights reserved.
//

import JSQMessagesViewController
import UIKit
import SwiftSocket
import SkyFloatingLabelTextField

// Create avatar with Placeholder Image
let SenderAvatar = JSQMessagesAvatarImageFactory().avatarImage(withUserInitials: "", backgroundColor: UIColor.gray, textColor: UIColor.white, font: UIFont.systemFont(ofSize: 12))
let RecieverAvatar = JSQMessagesAvatarImageFactory().avatarImage(withUserInitials: "RE", backgroundColor: UIColor.jsq_messageBubbleBlue(), textColor: UIColor.white, font: UIFont.systemFont(ofSize: 12))

enum User: String {
    case sender = "1"
    case reciever = "2"
}

// Helper Function to get usernames for a secific User.
func getName(_ user: User) -> String{
    return "" //"Anonymous"
}


// Helper Method for getting an avatar for a specific User.
func getAvatar(_ id: String) -> JSQMessagesAvatarImage{
    switch id {
    case User.sender.rawValue: return SenderAvatar
    case User.reciever.rawValue: return RecieverAvatar
    default: return SenderAvatar
    }
}


class InitialViewController: UIViewController {
    var client = TCPClient(address: "", port: 123)
    
    @IBOutlet weak var loginView: LoginView!
    
    var messages = [JSQMessage]()
    var timer = Timer()
    let chatView = ChatViewController()
    
    var username = ""
    
    func connect() {
        let address = self.loginView.hostnameLabel.text
        let port = Int(self.loginView.portLabel.text!)
        username = loginView.usernameLabel.text!
        
        guard port != nil else {
            presentErrorMessage(titled: "Invalid Port", withMessage: "Invalid port number, please try again.")
            return
        }
        
        guard address != "" else {
            presentErrorMessage(titled: "Invalid Address", withMessage: "Address cannot be blank, please user hostname provided from server.")
            return
        }
        
        guard username != "" else {
            presentErrorMessage(titled: "Invalid Username", withMessage: "Username cannot be blank, please use one.")
            return
        }
        
        client = TCPClient(address: address!, port: Int32(port!))
        
        switch client.connect(timeout: 1) {
        case .success:
            self.timer = Timer.scheduledTimer(withTimeInterval: 1.0, repeats: true) {
                _ in
                self.getNewMessage()
            }
            self.chatView.sendMethod = { let _ = self.client.send(string: self.username + ": " + $0) }
            self.chatView.closeMethod = {
                self.timer.invalidate()
                let _ = self.client.close()
            }
            
            let chatNavigationController = UINavigationController(rootViewController: self.chatView)
            present(chatNavigationController, animated: true, completion: nil)
            
        case .failure(let error):
            presentErrorMessage(titled: "Cannot Connect", withMessage: "Cannot connect to server. (\(error.localizedDescription))")
            return
        }
    }
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        loginView.buttonAction = connect
    }
    
    func presentErrorMessage(titled title: String, withMessage message: String) {
        let alert = UIAlertController(title: title, message: message, preferredStyle: UIAlertControllerStyle.alert)
        alert.addAction(UIAlertAction(title: "Close", style: UIAlertActionStyle.default, handler: nil))
        self.present(alert, animated: true, completion: nil)
    }
    
    
    func getNewMessage() {
        DispatchQueue.global(qos: .background).async {
            let data = self.client.read(1024*10)
            
            guard data != nil else {
                return
            }
            
            if let string = String(bytes: data!, encoding: .utf8) {
                let message = JSQMessage(senderId: (User.reciever.rawValue), displayName: getName(User.reciever), text: string)
                self.chatView.newMessage(message)
            } else {
                print("not a valid UTF-8 sequence")
            }
            
            DispatchQueue.main.async {
                self.chatView.finishReceivingMessage()
            }
        }
    }
}

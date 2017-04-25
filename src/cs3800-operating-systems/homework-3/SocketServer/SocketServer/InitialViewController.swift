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
        let port = Int(self.loginView.portLabel.text!)!
        
        username = loginView.usernameLabel.text!
        
        client = TCPClient(address: address!, port: Int32(UInt32(port)))
        
        switch client.connect(timeout: 1) {
        case .success:
            self.timer = Timer.scheduledTimer(withTimeInterval: 1.0, repeats: true) {
                _ in
                self.getNewMessage()
            }
            self.chatView.sendMethod = { let _ = self.client.send(string: self.username + ": " + $0) }

            let chatNavigationController = UINavigationController(rootViewController: self.chatView)
            present(chatNavigationController, animated: true, completion: nil)
            
        case .failure(let error):
            print("\(error)")
        }
        
    }
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
    
        loginView.buttonAction = connect
    }
    
    
    func getNewMessage() {
        DispatchQueue.global(qos: .background).async {
            let data = self.client.read(1024*10)
            
            
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

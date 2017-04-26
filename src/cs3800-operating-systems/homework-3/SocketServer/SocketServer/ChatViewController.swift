//
//  ChatViewController.swift
//  SwiftExample
//
//  Created by Dan Leonard on 5/11/16.
//  Copyright © 2016 MacMeDan. All rights reserved.
//

import UIKit
import JSQMessagesViewController
import SwiftSocket

class ChatViewController: JSQMessagesViewController {
    
    
    var sendMethod: ((String) -> Void)? = nil
    var closeMethod: (() -> Void)? = nil
    
    var messages = [JSQMessage]()
    let defaults = UserDefaults.standard
    
    var conversation: Conversation?
    
    var incomingBubble: JSQMessagesBubbleImage!
    var outgoingBubble: JSQMessagesBubbleImage!
    
    fileprivate var displayName: String!
    
    
    public func newMessage(_ message: JSQMessage) {
        messages.append(message)
    }
    
    func setupBackButton() {
        let backButton = UIBarButtonItem(title: "Back", style: UIBarButtonItemStyle.plain, target: self, action: #selector(backButtonTapped))
        backButton.tintColor = .black
        navigationItem.leftBarButtonItem = backButton
    }
    
    func setupSettingsButton() {
        let settingsButton = UIBarButtonItem(image: #imageLiteral(resourceName: "settings "), style: UIBarButtonItemStyle.plain, target: self, action: #selector(settingsButtonTapped))
        settingsButton.tintColor = .black
        navigationItem.rightBarButtonItem = settingsButton
    }
    
    func settingsButtonTapped() {
        let storyboard = UIStoryboard(name: "Main", bundle: nil)
        let settingsTableView = storyboard.instantiateViewController(withIdentifier: "Settings")
        
        let settingsNavigationController = UINavigationController(rootViewController: settingsTableView)
        present(settingsNavigationController, animated: true, completion: nil)
    }
    
    func backButtonTapped() {
        closeMethod!()
        dismiss(animated: true, completion: nil)
    }
    
    func setupTitle() {
        navigationItem.title = "Messages"
    }
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        setupBackButton()
        setupSettingsButton()
        setupTitle()
        
        self.inputToolbar.contentView?.leftBarButtonItem = nil
        

        collectionView?.collectionViewLayout.outgoingAvatarViewSize = .zero
        collectionView?.collectionViewLayout.incomingAvatarViewSize = .zero
//        if defaults.bool(forKey: Setting.removeAvatar.rawValue) {
//            
//        } else {
//            collectionView?.collectionViewLayout.incomingAvatarViewSize = CGSize(width: kJSQMessagesCollectionViewAvatarSizeDefault, height:kJSQMessagesCollectionViewAvatarSizeDefault )
//            collectionView?.collectionViewLayout.outgoingAvatarViewSize = CGSize(width: kJSQMessagesCollectionViewAvatarSizeDefault, height:kJSQMessagesCollectionViewAvatarSizeDefault )
//        }
    
        
        // This is a beta feature that mostly works but to make things more stable it is diabled.
        
        incomingBubble = JSQMessagesBubbleImageFactory().incomingMessagesBubbleImage(with: .black)
        outgoingBubble = JSQMessagesBubbleImageFactory().outgoingMessagesBubbleImage(with: .black)
        
        collectionView?.collectionViewLayout.springinessEnabled = false
        
        automaticallyScrollsToMostRecentMessage = true
        
        self.collectionView?.reloadData()
        self.collectionView?.layoutIfNeeded()
    }
    
    // MARK: JSQMessagesViewController method overrides
    override func didPressSend(_ button: UIButton, withMessageText text: String, senderId: String, senderDisplayName: String, date: Date) {
        let message = JSQMessage(senderId: senderId, senderDisplayName: senderDisplayName, date: date, text: text)
        self.messages.append(message)
        self.sendMethod!(text)

        self.finishSendingMessage(animated: true)
    }
    
    
    //MARK: JSQMessages CollectionView DataSource
    
    override func senderId() -> String {
        return User.sender.rawValue
    }
    
    override func senderDisplayName() -> String {
        return getName(.sender)
    }
    
    override func collectionView(_ collectionView: UICollectionView, numberOfItemsInSection section: Int) -> Int {
        return messages.count
    }
    
    override func collectionView(_ collectionView: JSQMessagesCollectionView, messageDataForItemAt indexPath: IndexPath) -> JSQMessageData {
        return messages[indexPath.item]
    }
    
    override func collectionView(_ collectionView: JSQMessagesCollectionView, messageBubbleImageDataForItemAt indexPath: IndexPath) -> JSQMessageBubbleImageDataSource {
        
        return messages[indexPath.item].senderId == self.senderId() ? outgoingBubble : incomingBubble
    }
    
    override func collectionView(_ collectionView: JSQMessagesCollectionView, avatarImageDataForItemAt indexPath: IndexPath) -> JSQMessageAvatarImageDataSource? {
        let message = messages[indexPath.item]
        return getAvatar(message.senderId)
    }
    
    override func collectionView(_ collectionView: JSQMessagesCollectionView, attributedTextForCellTopLabelAt indexPath: IndexPath) -> NSAttributedString? {
        // If first element or five minutes have passed since the last message, put at date attribute
        
        if let lastMessage = messages.first, indexPath.item == 0 {
            return JSQMessagesTimestampFormatter.shared().attributedTimestamp(for: lastMessage.date)
        } else if indexPath.item > 0  {
            
            let messageDate = messages[indexPath.item].date
            let messageDatePlus5Minutes = messageDate.addingTimeInterval(-5*60)
            
            let previousMessage = messages[indexPath.item - 1]
            
            if previousMessage.date.compare(messageDatePlus5Minutes) == ComparisonResult.orderedAscending  {
                return JSQMessagesTimestampFormatter.shared().attributedTimestamp(for: messageDate)
            }
        }
        
        return nil
    }
    
    override func collectionView(_ collectionView: JSQMessagesCollectionView, attributedTextForMessageBubbleTopLabelAt indexPath: IndexPath) -> NSAttributedString? {
        let message = messages[indexPath.item]
       
        if message.senderId == self.senderId() {
            return nil
        }
        
        return NSAttributedString(string: message.senderDisplayName)
    }
    
    override func collectionView(_ collectionView: JSQMessagesCollectionView, layout collectionViewLayout: JSQMessagesCollectionViewFlowLayout, heightForCellTopLabelAt indexPath: IndexPath) -> CGFloat {
        // If first element or five minutes have passed since the last message, put at date attribute
        
        if indexPath.item == 0 {
            return kJSQMessagesCollectionViewCellLabelHeightDefault
        } else if indexPath.item > 0 {
            let messageDate = messages[indexPath.item].date
            let messageDatePlus5Minutes = messageDate.addingTimeInterval(-5*60)
            
            let previousMessage = messages[indexPath.item - 1]
            
            if previousMessage.date.compare(messageDatePlus5Minutes) == ComparisonResult.orderedAscending  {
                return kJSQMessagesCollectionViewCellLabelHeightDefault
            }
        }
        
        return 0.0
    }
    
    override func collectionView(_ collectionView: JSQMessagesCollectionView, layout collectionViewLayout: JSQMessagesCollectionViewFlowLayout, heightForMessageBubbleTopLabelAt indexPath: IndexPath) -> CGFloat {
    
        let currentMessage = self.messages[indexPath.item]
        
        if currentMessage.senderId == self.senderId() {
            return 0.0
        }
        
        if indexPath.item - 1 > 0 {
            let previousMessage = self.messages[indexPath.item - 1]
            if previousMessage.senderId == currentMessage.senderId {
                return 0.0
            }
        }
        
        return kJSQMessagesCollectionViewCellLabelHeightDefault;
    }
    
}

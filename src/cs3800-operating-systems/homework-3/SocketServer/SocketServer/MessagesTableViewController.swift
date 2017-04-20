//
//  MessagesTableViewController.swift
//  SocketServer
//
//  Created by Illya Starikov on 4/19/17.
//  Copyright © 2017 Illya Starikov. All rights reserved.
//

import UIKit
import SwiftSocket

class MessagesTableViewController: UITableViewController {
    
    let client = TCPClient(address: "r01isgx2.device.mst.edu", port: 12345)
    
    var messages = [String]()
    var timer = Timer()
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        switch client.connect(timeout: 1) {
        case .success:
            timer = Timer.scheduledTimer(withTimeInterval: 1.0, repeats: true) {
                _ in
                self.getNewMessage()
            }
            
        case .failure(let error):
            print("\(error)")
        }
    }
    
    func getNewMessage() {
        DispatchQueue.global(qos: .background).async {
            let data = self.client.read(1024*10)
            
            if let string = String(bytes: data!, encoding: .utf8) {
                self.messages.append(string);
                print(self.messages)
            } else {
                print("not a valid UTF-8 sequence")
            }
            
    
            DispatchQueue.main.async {
                self.tableView.reloadData();
            }
        }
    }
    
    // MARK: - Table view data source
    
    override func numberOfSections(in tableView: UITableView) -> Int {
        return 1
    }
    
    override func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        return messages.count
    }
    
    
    override func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        let cell = tableView.dequeueReusableCell(withIdentifier: "LabelCell", for: indexPath)
        cell.textLabel?.text = messages[indexPath.row]
        
        return cell
    }
    
    
    
    /*
     // MARK: - Navigation
     
     // In a storyboard-based application, you will often want to do a little preparation before navigation
     override func prepare(for segue: UIStoryboardSegue, sender: Any?) {
     // Get the new view controller using segue.destinationViewController.
     // Pass the selected object to the new view controller.
     }
     */
    
}

//
//  SettingsTableViewController.swift
//  SwiftExample
//
//  Created by Dan Leonard on 5/15/16.
//  Copyright © 2016 MacMeDan. All rights reserved.
//

import UIKit

class SettingsTableViewController: UITableViewController {    
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        setupBackButton()
        setupTitle()
        
    }
    
    func setupBackButton() {
        let backButton = UIBarButtonItem(title: "Back", style: UIBarButtonItemStyle.plain, target: self, action: #selector(backButtonTapped))
        navigationItem.leftBarButtonItem = backButton
    }
    
    func backButtonTapped() {
        dismiss(animated: true, completion: nil)
    }
    
    func setupTitle() {
        navigationItem.title = "Settings"
    }

}

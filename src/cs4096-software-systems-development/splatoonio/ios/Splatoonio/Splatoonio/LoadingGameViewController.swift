//
//  LoadingGameViewController.swift
//  Splatoonio
//
//  Created by Adam Evans on 8/30/17.
//  Copyright © 2017 Kijug Software. All rights reserved.
//

import UIKit


class LoadingGameViewController: UIViewController
{
	private var game:Game!
	
	@IBOutlet private var statusLabel:UILabel!
	
	// =================================================================================
	//								Loading States
	// =================================================================================
	
	func loadGame(id:GameID)
	{
		game = ServerAPI.gameForID(id:id)
		loadingComplete()
	}
	
	// =================================================================================
	
	func loadingComplete()
	{
		performSegue(withIdentifier:"LoadingGameToGame", sender:self)
	}
	
	// =================================================================================
	//								UIViewController
	// =================================================================================
	
	override func prepare(for segue: UIStoryboardSegue, sender: Any?)
	{
		let vc = segue.destination as? GameViewController
		vc?.game = game
	}
	
	// =================================================================================
	
    override func viewDidLoad()
	{
        super.viewDidLoad()
		
		statusLabel.text = "Loading Game"
		loadGame(id: GameID(0))
    }
	
	// =================================================================================
	
	override var prefersStatusBarHidden: Bool
	{
		return true
	}
	
	// =================================================================================
}

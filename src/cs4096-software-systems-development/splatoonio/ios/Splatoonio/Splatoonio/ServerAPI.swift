//
//  ServerAPI.swift
//  Splatoonio
//
//  Created by Adam Evans on 8/29/17.
//  Copyright © 2017 Kijug Software. All rights reserved.
//

import Foundation
import MapKit
import CoreLocation


// TODO: maybe needs to be an actual object if we need to manage connection information?
// Maybe make connection information static (we should never be talking to more than one server)?
class ServerAPI
{
	// =================================================================================
	//								Information Retrieval
	// =================================================================================
	// Returns the current public game for our current location
	static func currentGame() -> Game
	{
		// TODO: Implement. This dummy code just gives a dummy local rectangle for testing
		let game = Game()
		game.board.boundingRegion = MKCoordinateRegionMakeWithDistance(CLLocationCoordinate2DMake(37.953265, -91.77260), 100, 70)
		
		return game
	}
	
	// =================================================================================
	
	static func gameForLocation(location:CLLocation) -> Game
	{
		// TODO: implement
		return currentGame()
	}
	
	// =================================================================================
	
	static func gameForID(id:GameID) -> Game
	{
		// TODO: implement
		return currentGame()
	}
	
	// =================================================================================
	//								Information Posting
	// =================================================================================
	
	static func addPlayerToGame(game:GameID) -> Game
	{
		// TODO: implement
		return addNewPlayerToGame(gameID:game, fromLobby:.none)
	}
	
	// =================================================================================
	// Returns the game resulting from adding the player
	static func addNewPlayerToGame(gameID:GameID, fromLobby lobby:LobbyID) -> Game
	{
		// TODO: implement
		let game = Game()
		game.id = gameID
		
		let me = Player()
		me.id = PlayerID(arc4random())
		me.name = String(format:"player%d", arc4random() % 100)
		
		_ = game.addPlayer(player:me, isMe:true)
		
		return game
	}
	
	// =================================================================================
}

//
//  Game.swift
//  Splatoonio
//
//  Created by Adam Evans on 8/29/17.
//  Copyright © 2017 Kijug Software. All rights reserved.
//

import Foundation
import CoreLocation


class Game
{
	var id:GameID
	var numPlayers:Int
	var me:Player?			// we can have a game that we aren't in
	var board:GameBoard
	var players:[PlayerID:Player]
	var items:[Item]
	
	// =================================================================================
	//									Initializiers
	// =================================================================================
	
	init()
	{
		id = 0
		numPlayers = 0
		me = nil
		board = GameBoard()
		players = [PlayerID:Player]()
		items = [Item]()
	}
	
	// =================================================================================
	//									Normal Functions
	// =================================================================================
	// player - The player to add to the game
	// me - Pass true to designate player as us
	// Returns player if the given player is not in the game, else returns the player in
	// the game with the same player ID as the given player.
	@discardableResult func addPlayer(player:Player, isMe:Bool) -> Player
	{
		// check if player is already playing (don't add the same player twice)
		for (id, p) in players
		{
			if (id == player.id)
			{
				// allow updating which player we are
				if (isMe)
				{
					me = p
				}
				
				return p
			}
		}
		
		// We only get here if player is not in the game
		players[player.id] = player
		numPlayers += 1
		
		if (isMe)
		{
			me = player
		}
		
		return player
	}
	
	// =================================================================================
	
	func move(player pid:PlayerID, to location:CLLocation)
	{
		// TODO: implement
		// check that the player is valid
		guard let player = players[pid] else
		{
			return
		}
		
		if let oldLoc = player.location
		{
			let travleTime = location.timestamp.timeIntervalSince(oldLoc.timestamp)
			let updatedPixels = board.paintLine(from:oldLoc.coordinate, to:location.coordinate, travelTime:travleTime, forPlayer:player)
			
			board.updatePixels(pixels:updatedPixels)
			
			// notify the server if this was us
			if (pid == me?.id)
			{
				ServerAPI.sendUpdates(updates:updatedPixels)
			}
		}
		
		player.location = location
	}
	
	// =================================================================================	
}

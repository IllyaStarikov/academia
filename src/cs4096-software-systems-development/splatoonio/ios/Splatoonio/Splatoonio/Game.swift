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
	var players:[Player]
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
		players = [Player]()
		items = [Item]()
	}
	
	// =================================================================================
	//									Normal Functions
	// =================================================================================
	// player - The player to add to the game
	// me - Pass true to designate player as us
	// Returns player if the given player is not in the game, else returns the player in
	// the game with the same player ID as the given player.
	func addPlayer(player:Player, isMe:Bool) -> Player
	{
		// check if player is already playing (don't add the same player twice)
		for p in players
		{
			if (p.id == player.id)
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
		players.append(player)
		numPlayers += 1
		
		if (isMe)
		{
			me = player
		}
		
		return player
	}
	
	// =================================================================================
	
	func move(player:PlayerID, location:CLLocation)
	{
		// TODO: implement
	}
	
	// =================================================================================	
}

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

enum ServerError: Error
{
    case unexpectedStatusCode(String)
}


// TODO: maybe needs to be an actual object if we need to manage connection information?
// Maybe make connection information static (we should never be talking to more than one server)?
class ServerAPI
{
    enum StatusCodes {
        case success, failure
    }
    
	// =================================================================================
	//								Information Retrieval
	// =================================================================================
	// Returns the current public game for our current location
	static func currentGame() -> Game
	{
		// TODO: Implement. This dummy code just gives a dummy local rectangle for testing
		let game = Game()
		game.board.boundingRegion = MKCoordinateRegionMakeWithDistance(CLLocationCoordinate2DMake(37.952902, -91.772447), 100, 70)
		
		let me = Player()
		me.team = .red
		me.brushRadius = 2
		me.id = 0
		me.name = "ME"
		game.addPlayer(player:me, isMe:true)
		
		return game
    }
    
    
    // =================================================================================
    //                                Illya's Methods
    // =================================================================================
    static func getAllUsers()
    {
        let users = [User(), User(), User()]
        
        return users
    }
    
    // =================================================================================
    
    static func delete(user: User) -> Bool
    {
        // do something with user.ID
        
        // return if successful
        return true
    }
    
    // =================================================================================
    
    static func createUserWith(username name: String) throws -> Bool
    {
        // register name
        let statuses = [
            "204": StatusCodes.success,
            "409": StatusCodes.failure
        ]
        
        let statusCode = "409"
        
        if statuses[statusCode] == .success
        {
            // valid username
            return true
        }
        else if statuses[statusCode] == .failure
        {
            return false
        }
        else
        {
            throw ServerError.unexpectedStatusCode(statusCode)
        }
    }
    
    // =================================================================================
    
    static func getUserVia(id: UserID) -> User?
    {
        let user: User? = nil
    
        return user
    }
    
    // =================================================================================
    
    static func getGameVia(gameID: GameID) -> Game?
    {
        let game: Game? = nil
        
        return game
    }
    
    // =================================================================================
    
    static func getGameVia(location: CLLocation) -> Game?
    {
        let game: Game? = nil
        
        return game
    }
    
    // =================================================================================
    
    static func getMapVia(gameID: GameID) -> Map
    {
        return Map()
    }
    
    // =================================================================================
    
    static func join(game: Game) -> Bool
    {
        let statuses = [
            "204": StatusCodes.success
        ]
        
        let statusCode = "204"
        
        if statuses[statusCode] == .success
        {
            return true
        }
        else
        {
            return false
        }
    }
    
    // =================================================================================
    
    static func getServerTimeVia(gameID: GameID) -> Date
    {
        return Date() // Always return the current time
    }
    
    // =================================================================================
    
    static func updateServerTimeWith(pixels: PixelUpdate)
    {
        
    }
    
    // =================================================================================
    
    static func updateGameState(game: Game) -> Game
    {
        // do things to game
    }
    
    // =================================================================================
    
    static func getEntireGameState(game: Game) -> Game
    {
        
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
		
		game.addPlayer(player:me, isMe:true)
		
		return game
	}
	
	// =================================================================================
	//								In-Game Updates
	// =================================================================================
	
	static func sendUpdates(updates:[PixelUpdate])
	{
		// TODO: implement
	}
	
	// =================================================================================
}


extension Int {
    static func randomInt(from: Int, to: Int) -> Int {
        return from + Int(arc4random_uniform(UInt32(to - from)))
    }
}

extension Array {
    func randomItem() -> Element? {
        if isEmpty { return nil }
        
        let index = Int.randomInt(from: 0, to: self.count)
        return self[index]
    }
}

extension User {
    convenience init() {
        struct StaticHolder {
            static var id = 0;
        }
        
        self.ID = StaticHolder.id
        self.name = ["Ian", "Adam", "Illya", "Deacon", "Luke", "Eric", "Michael"].randomItem()! // if this is every empty, i'll shit myself
    }
}

//
//  main.cpp
//  Source Code
//
//  Created by Illya Starikov on 12/20/16.
//  Copyright © 2016 Illya Starikov. All rights reserved.
//

#include <iostream>
#include <tuple>

#include "board.hpp"
#include "functions.hpp"

int main(int argc, char *argv[]) {
	Board board;
	unsigned short row, column;
    
    bool player = 0;

	do {
        board.print();

        if (player) {
		    std::tie(row, column) = getPlayerMove('X', board);
		    board[row][column] = x;
        } else {
		    std::tie(row, column) = getPlayerMove('O', board);
		    board[row][column] = o;
        }

        player = !player;
	} while (!board.noMoreMovesAvailable() && !board.hasWon());
	
	std::cout << "Player" << board.getWinner() << " Won! \n\n";
}

//
//  board.hpp
//  Source Code
//
//  Created by Illya Starikov on 12/20/16.
//  Copyright © 2016 Illya Starikov. All rights reserved.
//

#include <vector>

#include "functions.hpp"

#ifndef board_hpp
#define board_hpp

enum GameState { blank = 0, x, o };

class Board {
    std::vector<std::vector<GameState>> board = std::vector<std::vector<GameState>>(3, std::vector<GameState>(3, blank));

protected:
    char stateToCharacter(const GameState state);

public:
    auto operator[](const int i)const { return board[i]; }
    auto& operator[](const int i) { return board[i]; }

    GameState getWinner();
    bool hasWon();
    bool noMoreMovesAvailable();
    void print();
};

#endif /* board_hpp */

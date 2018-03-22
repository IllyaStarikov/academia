//
//  fen-parser.h
//  src
//
//  Created by Illya Starikov on 03/08/18.
//  Copyright 2018. Illya Starikov. All rights reserved.
//

#ifndef fen_parser_h
#define fen_parser_h

#include "state.h"
#include "chess-engine.h"

#include <string>
#include <regex>
#include <map>
#include <iostream>
#include <algorithm>

enum FenToken {
    board, colorAtPlay, castling, enPassant, halfTurns, fullTurns
};

class FenParser {
private:
    std::string fenString;
    std::string getToken(const FenToken& token);

    void parseBoard(std::vector<Bitboard>& whiteBitboard, std::vector<Bitboard>& blackBitboard);
    Color parseColorAtPlay();
    Bitboard parseCastling();
    Bitboard parseEnPassant();


public:
    State operator()(const std::string &string);
};

#endif /* fen-parser_h */


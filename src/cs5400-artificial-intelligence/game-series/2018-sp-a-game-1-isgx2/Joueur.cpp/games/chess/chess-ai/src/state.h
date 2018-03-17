//
//  state.h
//  src
//
//  Created by Illya Starikov on 03/06/18.
//  Copyright 2018. Illya Starikov. All rights reserved.
//

#ifndef state_h
#define state_h

#include <ostream>

#include "bitboard.h"
#include "chess-engine.h"
#include "chess-pieces.h"
#include "color.h"

class State {
public:
    Color colorAtPlay;

    Bitboard allWhites;
    Bitboard allBlacks;

    std::vector<Bitboard> whites;
    std::vector<Bitboard> blacks;

    Bitboard enPassantSquares;
    Bitboard castlingSquares;

    State(const Color& colorAtPlay, const Bitboard& allWhites, const Bitboard& allBlacks, const std::vector<Bitboard>& whites, const std::vector<Bitboard>& blacks, const Bitboard& enPassantSquares, const Bitboard& castlingSquares): colorAtPlay(colorAtPlay), allWhites(allWhites), allBlacks(allBlacks), whites(whites), blacks(blacks), enPassantSquares(enPassantSquares), castlingSquares(castlingSquares) {}

    bool operator==(const State& other) const noexcept;

    friend std::ostream& operator<<(std::ostream& os, const State& object);
};

#endif /* state_h */


//
//  state.cpp
//  src
//
//  Created by Illya Starikov on 03/07/18.
//  Copyright 2018. Illya Starikov. All rights reserved.
//

#include "state.h"

using namespace ChessEngine;

bool State::operator==(const State& other) const noexcept {
    return colorAtPlay      == other.colorAtPlay
        && allWhites        == other.allWhites
        && allBlacks        == other.allBlacks
        && whites           == other.whites
        && blacks           == other.blacks
        && enPassantSquares == other.enPassantSquares
        && castlingSquares  == other.castlingSquares;
}

bool State::operator!=(const State& other) const noexcept {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const State& object) {
    auto color = object.colorAtPlay == white ? "white" : "black";
    os << "Color: " << color << "\nAll Whites: " << object.allWhites << "\nAll Blacks: " << object.allBlacks;

    os << "\nWhite King:   " << object.whites[MoveEngine::pieceToInt(king)];
    os << "\nWhite Queen:  " << object.whites[MoveEngine::pieceToInt(queen)];
    os << "\nWhite Rook:   " << object.whites[MoveEngine::pieceToInt(rook)];
    os << "\nWhite Bishop: " << object.whites[MoveEngine::pieceToInt(bishop)];
    os << "\nWhite Knight: " << object.whites[MoveEngine::pieceToInt(knight)];
    os << "\nWhite Pawn:   " << object.whites[MoveEngine::pieceToInt(pawn)];

    os << "\nBlack King:   " << object.blacks[MoveEngine::pieceToInt(king)];
    os << "\nBlack Queen:  " << object.blacks[MoveEngine::pieceToInt(queen)];
    os << "\nBlack Rook:   " << object.blacks[MoveEngine::pieceToInt(rook)];
    os << "\nBlack Bishop: " << object.blacks[MoveEngine::pieceToInt(bishop)];
    os << "\nBlack Knight: " << object.blacks[MoveEngine::pieceToInt(knight)];
    os << "\nBlack Pawn:   " << object.blacks[MoveEngine::pieceToInt(pawn)];

    os << "\nEn Passant: " << object.enPassantSquares << "\nCastling " << object.castlingSquares;

    return os;
}

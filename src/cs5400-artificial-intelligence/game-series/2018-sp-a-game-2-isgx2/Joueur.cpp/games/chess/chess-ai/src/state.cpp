//
//  state.cpp
//  src
//
//  Created by Illya Starikov on 03/07/18.
//  Copyright 2018. Illya Starikov. All rights reserved.
//

#include "state.h"


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

    os << "\nWhite King:   " << object.whites[ChessEngine::pieceToInt(king)];
    os << "\nWhite Queen:  " << object.whites[ChessEngine::pieceToInt(queen)];
    os << "\nWhite Rook:   " << object.whites[ChessEngine::pieceToInt(rook)];
    os << "\nWhite Bishop: " << object.whites[ChessEngine::pieceToInt(bishop)];
    os << "\nWhite Knight: " << object.whites[ChessEngine::pieceToInt(knight)];
    os << "\nWhite Pawn:   " << object.whites[ChessEngine::pieceToInt(pawn)];

    os << "\nBlack King:   " << object.blacks[ChessEngine::pieceToInt(king)];
    os << "\nBlack Queen:  " << object.blacks[ChessEngine::pieceToInt(queen)];
    os << "\nBlack Rook:   " << object.blacks[ChessEngine::pieceToInt(rook)];
    os << "\nBlack Bishop: " << object.blacks[ChessEngine::pieceToInt(bishop)];
    os << "\nBlack Knight: " << object.blacks[ChessEngine::pieceToInt(knight)];
    os << "\nBlack Pawn:   " << object.blacks[ChessEngine::pieceToInt(pawn)];

    os << "\nEn Passant: " << object.enPassantSquares << "\nCastling " << object.castlingSquares;

    return os;
}

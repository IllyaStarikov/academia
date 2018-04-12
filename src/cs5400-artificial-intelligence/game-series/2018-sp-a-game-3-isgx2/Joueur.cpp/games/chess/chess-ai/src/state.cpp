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
    static std::map<Piece, char> pieceToChar {
        {king, 'K'},
        {queen, 'Q'},
        {knight, 'N'},
        {rook, 'R'},
        {bishop, 'B'},
        {pawn, 'P'}
    };

    std::map<int, char> mappings;

    for (int i = 0; i < 6; i++) {
        for (auto index : object.whites[i].toIndices()) {
            mappings[index] = toupper(pieceToChar[MoveEngine::intToPiece(i)]);
        }

        for (auto index : object.blacks[i].toIndices()) {
            mappings[index] = tolower(pieceToChar[MoveEngine::intToPiece(i)]);
        }
    }

    std::stringstream ss;

    for (int i = 63; i >= 0; i--) {
        if (i == 63) {
            os << "    +------------------------+";
        }

        if ((i + 1) % 8 == 0) {
            auto string = ss.str();
            std::reverse(string.begin(), string.end());

            os << string;
            os << "\n " << static_cast<int>(i / 8 + 1) << " | ";

            ss.str("");
            ss.clear();
        }

        if (mappings.find(i) == mappings.end()) {
            ss << " . ";
        } else {
            ss << " " << mappings[i] << " ";
        }

        if (i == 0) {
            auto string = ss.str();
            std::reverse(string.begin(), string.end());

            os << string;
            os << "\n    +------------------------+";
            os << "\n      a  b  c  d  e  f  g  h\n";
        }
    }



    return os;
}

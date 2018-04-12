//
//  chess-pieces.h
//  src
//
//  Created by Illya Starikov on 02/26/18.
//  Copyright 2018. Illya Starikov. All rights reserved.
//

#ifndef chess_pieces_h
#define chess_pieces_h

#include <iostream>

namespace ChessEngine {
    enum Piece {
        king   = 0,
        queen  = 1,
        rook   = 2,
        bishop = 3,
        knight = 4,
        pawn   = 5
    };
}

namespace std {
    template <>
    struct hash<ChessEngine::Piece> {
        size_t operator()(const ChessEngine::Piece& piece) const {
            return static_cast<int>(piece);
        }
    };
}

#endif /* chess_pieces_h */


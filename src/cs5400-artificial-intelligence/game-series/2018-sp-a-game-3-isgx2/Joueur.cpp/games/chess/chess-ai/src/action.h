//
//  action.h
//  src
//
//  Created by Illya Starikov on 03/02/18.
//  Copyright 2018. Illya Starikov. All rights reserved.
//

#ifndef action_h
#define action_h

#include "bitboard.h"
#include "chess-pieces.h"
#include "color.h"

namespace ChessEngine {
    class Action {
    public:
        Piece piece; // the piece that created this move
        Color color; // the color that created this move

        Bitboard pieceBefore; // before and after the piece moved for *just this move*
        Bitboard pieceAfter;

        bool wasCaptured; // was an enemy piece captured on this move?
        Piece pieceCaptured; // if so, what piece?

        bool wasPromotion; // was this move a pawn promotion?
        Piece promotedTo; // if so, what was it promoted to?

        bool wasEnPassant; // was this an enpassant move?
        bool wasCastling; // was this a castling move?

        Action(const Piece& piece, const Color& color, const Bitboard& pieceBefore, const Bitboard& pieceAfter, const bool& wasCaptured, const Piece& pieceCaptured, const bool& wasPromotion, const Piece& promotedTo, const bool& wasEnPassant, const bool& wasCastling): piece(piece), color(color), pieceBefore(pieceBefore), pieceAfter(pieceAfter), wasCaptured(wasCaptured), pieceCaptured(pieceCaptured), wasPromotion(wasPromotion), promotedTo(promotedTo), wasEnPassant(wasEnPassant), wasCastling(wasCastling) {}
        Action() = default;
    };
}

#endif /* action_h */




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

class Action {
public:
    const Piece piece; // the piece that created this move
    const Color color; // the color that created this move

    const Bitboard pieceBefore; // before and after the piece moved for *just this move*
    const Bitboard pieceAfter;

    const bool wasCaptured; // was an enemy piece captured on this move?
    const Piece pieceCaptured; // if so, what piece?

    const bool wasPromotion; // was this move a pawn promotion?
    const Piece promotedTo; // if so, what was it promoted to?

    const bool wasEnPassant; // was this an enpassant move?
    const bool wasCastling; // was this a castling move?

    Action(const Piece& piece, const Color& color, const Bitboard& pieceBefore, const Bitboard& pieceAfter, const bool& wasCaptured, const Piece& pieceCaptured, const bool& wasPromotion, const Piece& promotedTo, const bool& wasEnPassant, const bool& wasCastling): piece(piece), color(color), pieceBefore(pieceBefore), pieceAfter(pieceAfter), wasCaptured(wasCaptured), pieceCaptured(pieceCaptured), wasPromotion(wasPromotion), promotedTo(promotedTo), wasEnPassant(wasEnPassant), wasCastling(wasCastling) {}
};

#endif /* action_h */




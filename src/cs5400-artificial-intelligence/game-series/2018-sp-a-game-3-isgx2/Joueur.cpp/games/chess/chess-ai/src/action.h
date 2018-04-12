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

#include <unordered_map>
#include <iostream>

/*
 * 0      : Color
 *          - 0 -> white
 *          - 1 -> black
 * 1 - 6  : From Index
 * 7 - 12 : To Index
 * 13-17  : Unused
 * 16-18  : piece type moved
 *          - 000 -> none (illegal)
 *          - 001 -> king
 *          - 010 -> pawn
 *          - 011 -> bishop
 *          - 100 -> knight
 *          - 101 -> rook
 *          - 110 -> queen
 * 19     : double pawn forward flag
 * 20     : queen side castle flag
 * 21     : king side castle flag
 * 22     : checking flag, will put opponent in check
 * 23-25  : capture type:
 *          - 000 -> none
 *          - 010 -> pawn
 *          - 011 -> bishop
 *          - 100 -> knight
 *          - 101 -> rook
 *          - 110 -> queen
 * 26     : en passant flag
 * 27     : equal capture flag, capturing same piece
 * 28-30  : promotion type
 *            - 001 -> none
 *            - 011 -> bishop
 *            - 100 -> knight
 *            - 101 -> rook
 *            - 110 -> queen
 * 31     : winning capture flag, capture is of a higher value piece
 */

namespace ChessEngine {
    class Action {
        uint32_t action;

        static uint32_t colorToBitboard(const Color& color);
        static Color actionToColor(const uint32_t& board);

        static uint32_t pieceBeforeToBitboard(const Bitboard& before);
        static Bitboard actionToPieceBefore(const uint32_t& board);

        static uint32_t pieceAfterToBitboard(const Bitboard& after);
        static Bitboard actionToPieceAfter(const uint32_t& board);

        static uint32_t pieceMovedToBitboard(const Piece& piece);
        static Piece actionToPieceMoved(const uint32_t& board);

        static uint32_t doublePawnForwardToBitboard(const bool& doublePawnForward);
        static bool actionToDoublePawnForward(const uint32_t& board);

        static uint32_t queenSideCastleToBitboard(const bool& queenSideCastling);
        static bool actionToQueenSideCastle(const uint32_t& board);

        static uint32_t kingSideCastleToBitboard(const bool& kingSideCastling);
        static bool actionToKingSideCastle(const uint32_t& board);

        static uint32_t enemyInCheckToBitboard(const bool& enemyInCheck);
        static bool actionToEnemyInCheck(const uint32_t& board);

        static uint32_t pieceCapturedToBitboard(const bool& wasCapture, const Piece& piece);
        static Piece actionToPieceCaptured(const uint32_t& board);
        static bool actionToWasCapture(const uint32_t& board);

        static uint32_t wasEnPassantCaptureToBitboard(const bool& wasEnPassantCapture);
        static bool actionToWasEnpassantCapture(const uint32_t& board);

        static uint32_t wasEqualPieceCaptureToBitboard(const bool& wasCapture, const Piece& piece, const Piece& capturePiece);
        static bool actionToWasEqualPieceCapture(const uint32_t& board);

        static uint32_t promotionToBitboard(const bool& wasPromotion, const Piece& promotedTo);
        static bool actionToWasPromotion(const uint32_t& board);
        static Piece actionToPromotedTo(const uint32_t& board);

    public:
        uint32_t key() const { return action; }

        Piece piece() const { return actionToPieceMoved(action); } // the piece that created this move
        Color color() const { return actionToColor(action); } // the color that created this move

        Bitboard pieceBefore() const { return actionToPieceBefore(action); } // before and after the piece moved for *just this move*
        Bitboard pieceAfter() const { return actionToPieceAfter(action); }

        bool doublePawnForward() const { return actionToDoublePawnForward(action); } // was this a pawn that moved forward twice

        bool queenSideCastling() const { return actionToQueenSideCastle(action); } // was this a queen side castling move?
        bool kingSideCastling() const { return actionToKingSideCastle(action); } // was this a king side castling move?

        bool enemyInCheck() const { return actionToEnemyInCheck(action); }

        bool wasCapture() const { return actionToWasCapture(action); } // was an enemy piece captured on this move?
        Piece pieceCaptured() const { return actionToPieceCaptured(action); } // if so, what piece?
        bool wasEnPassantCapture() const { return actionToWasEnpassantCapture(action); } // was this an enapassant capture?

        bool wasEqualCapture() const  { return actionToWasEqualPieceCapture(action); } // were the pieces equal?

        bool wasPromotion() const { return actionToWasPromotion(action); } // was this move a pawn promotion?
        Piece promotedTo() const { return actionToPromotedTo(action); } // if so, what was it promoted to?

        bool operator<(const Action& other) const { return this -> action < other.action; }
        bool operator>(const Action& other) const { return this -> action > other.action; }
        bool operator==(const Action& other) const { return this -> action == other.action; }

        Action(const Piece& piece, const Color& color, const Bitboard& pieceBefore, const Bitboard& pieceAfter, const bool& doublePawnForward,  const bool& queenSideCastling, const bool& kingSideCastling, const bool& enemyInCheck, const bool& wasCapture, const bool& wasEnPassantCapture, const Piece& pieceCaptured, const bool& wasPromotion, const Piece& promotedTo) {
            action = 0
                | colorToBitboard(color)
                | pieceBeforeToBitboard(pieceBefore)
                | pieceAfterToBitboard(pieceAfter)
                | pieceMovedToBitboard(piece)
                | doublePawnForwardToBitboard(doublePawnForward)
                | queenSideCastleToBitboard(queenSideCastling)
                | kingSideCastleToBitboard(kingSideCastling)
                | enemyInCheckToBitboard(enemyInCheck)
                | pieceCapturedToBitboard(wasCapture, pieceCaptured)
                | wasEnPassantCaptureToBitboard(wasEnPassantCapture)
                | wasEqualPieceCaptureToBitboard(wasCapture, piece, pieceCaptured)
                | promotionToBitboard(wasPromotion, promotedTo)
                ;
        }

        Action() = default;
        Action(const Action& other) = default;
    };
}

namespace std {
    template <>
    struct hash<ChessEngine::Action> {
        size_t operator()(const ChessEngine::Action& action) const {
            std::cout << static_cast<int>(action.key()) << "\n";
            return static_cast<int>(action.key());
        }
    };
}

#endif /* action_h */


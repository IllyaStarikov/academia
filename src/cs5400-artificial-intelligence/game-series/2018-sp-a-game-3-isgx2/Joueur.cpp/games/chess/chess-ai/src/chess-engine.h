//
//  AI.h
//  src
//
//  Created by Illya Starikov on 02/26/18.
//  Copyright 2018. Illya Starikov. All rights reserved.
//

#ifndef chess_engine_h
#define chess_engine_h

#include "chess-pieces.h"
#include "bitboard.h"
#include "action.h"
#include "direction.h"
#include "color.h"

#include <utility>
#include <map>
#include <vector>
#include <inttypes.h>
#include <math.h>

namespace ChessEngine {
    class MoveEngine {
    private:
        static Bitboard northMovesWithBlockers(Bitboard board, const Bitboard& blockerInverse);
        static Bitboard southMovesWithBlockers(Bitboard board, const Bitboard& blockerInverse);
        static Bitboard eastMovesWithBlockers(Bitboard board, const Bitboard& blockerInverse);
        static Bitboard westMovesWithBlockers(Bitboard board, const Bitboard& blockerInverse);
        static Bitboard northeastMovesWithBlockers(Bitboard board, const Bitboard& blockerInverse);
        static Bitboard northwestMovesWithBlockers(Bitboard board, const Bitboard& blockerInverse);
        static Bitboard southeastMovesWithBlockers(Bitboard board, const Bitboard& blockerInverse);
        static Bitboard southwestMovesWithBlockers(Bitboard board, const Bitboard& blockerInverse);

        static Bitboard pawnNorthMovesWithBlockers(Bitboard board, const Bitboard& blockerInverse);
        static Bitboard pawnNorthNorthMovesWithBlockers(Bitboard board, const Bitboard& blockerInverse);
        static Bitboard pawnSouthMovesWithBlockers(Bitboard board, const Bitboard& blockerInverse);
        static Bitboard pawnSouthSouthMovesWithBlockers(Bitboard board, const Bitboard& blockerInverse);

    public:
        static int pieceToInt(const Piece piece);
        static Piece intToPiece(const int integer);
        static std::vector<std::pair<char, int>> bitStringToDescription(Bitboard board);

        static void generateInitialState(std::vector<Bitboard>& white, std::vector<Bitboard>& black);
        static Bitboard allBitboardsInOneBoard(const std::vector<Bitboard> boards);

        static Bitboard allStandardMovesInOneBitboard(const std::vector<Bitboard>& selfPieces, const Bitboard& self, const Bitboard& enemy, const Color& selfColor) {
        // This is equivent to pieceToInt, but wayyy faster
        return kingMoves  (selfPieces[static_cast<int>(king  )], self                  )
             | queenMoves (selfPieces[static_cast<int>(queen) ], self, enemy           )
             | rookMoves  (selfPieces[static_cast<int>(rook)  ], self, enemy           )
             | bishopMoves(selfPieces[static_cast<int>(bishop)], self, enemy           )
             | knightMoves(selfPieces[static_cast<int>(knight)], self                  )
             | pawnMoves  (selfPieces[static_cast<int>(pawn)  ], self, enemy, selfColor);
        }

        static Bitboard moving(const Bitboard& board, const Direction& direction);

        // Moving Pieces
        static Bitboard kingMoves(const Bitboard& king, const Bitboard& self);
        static Bitboard knightMoves(const Bitboard& knight, const Bitboard& self);

        // Sliding Pieces
        static Bitboard rookMoves(const Bitboard& rook, Bitboard self, Bitboard enemy);
        static Bitboard bishopMoves(const Bitboard& bishop, Bitboard self, Bitboard enemy);
        static Bitboard queenMoves(const Bitboard& queen, Bitboard self, Bitboard enemy);

        // Freaking Pawns
        static Bitboard pawnMoves(const Bitboard& pawn, Bitboard self, Bitboard enemy, const Color& selfColor);
        static Bitboard enpassantMoves(const Bitboard& enemyEnpassantSquares, const Bitboard& selfPawns);

        // Castling
        static Bitboard castlingMoves(const Bitboard& castlingSquares, const Bitboard& allWhite, const Bitboard& allBlacks);
    };
}

#endif /* chess_engine_h */


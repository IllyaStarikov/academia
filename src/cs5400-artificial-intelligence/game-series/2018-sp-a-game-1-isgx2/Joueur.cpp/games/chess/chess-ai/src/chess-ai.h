//
//  chess-ai.h
//  src
//
//  Created by Illya Starikov on 03/06/18.
//  Copyright 2018. Illya Starikov. All rights reserved.
//

#ifndef chess_ai_h
#define chess_ai_h

#include "bitboard.h"
#include "color.h"
#include "state.h"
#include "action.h"
#include "chess-engine.h"
#include "fen-parser.h"

#include <vector>
#include <functional>
#include <utility>
#include <memory>
#include <map>
#include <tuple>

    /* const Color colorAtPlay; */

    /* const Bitboard allWhites; */
    /* const Bitboard allBlacks; */

    /* const std::vector<Bitboard> whites; */
    /* const std::vector<Bitboard> blacks; */

    /* const Bitboard enPassantSquares; */
    /* const Bitboard castlingSquares; */

const int NUMBER_OF_PIECES = 6;

class ChessAI {
    FenParser parser;

    static bool wasCapture(const Bitboard& enemyBitboard, const Bitboard& move);
    static Piece findCapturePiece(const std::vector<Bitboard>& enemyBitboards, const Bitboard& enemyBitboard, const Bitboard& move);

    static Bitboard enpassantMoveGenerator(const Bitboard& enPassantSquares, const Bitboard& pawn, const Color& friendlyColor);

    static Bitboard castlingMoveGenerator(const Bitboard& allWhites, const Bitboard& allBlacks, const Bitboard& castlingSquares, const Bitboard& rook);

    static Bitboard kingLocationAfterCastling(const Bitboard& rookAfterCastling);

public:
    State currentState;
    Color selfColor;

    ChessAI(const Color& selfColor);
    ChessAI(const std::string& fenString);

    ChessAI() = delete;
    ChessAI(const ChessAI& other) = delete;
    ChessAI(ChessAI&& other) = delete;
    ChessAI& operator=(const ChessAI& other) = delete;
    ChessAI& operator=(ChessAI&& other) = delete;

    void setState();

    // MARK: AI Operators
    static State initialState();
    static std::vector<Action> actions(const State& state);
    static State result(const State& state, const Action& action);
};


#endif /* chess_ai_h */

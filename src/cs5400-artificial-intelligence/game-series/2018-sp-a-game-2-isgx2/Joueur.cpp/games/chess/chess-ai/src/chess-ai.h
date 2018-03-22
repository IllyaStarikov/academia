//
//  chess-ai.h
//  src
//
//  Created by Illya Starikov on 03/06/18.
//  Copyright 2018. Illya Starikov. All rights reserved.
//

#ifndef chess_ai_h
#define chess_ai_h

#include "action.h"
#include "bitboard.h"
#include "chess-engine.h"
#include "chess-heuristic.h"
#include "chess-history.h"
#include "chess-outcome.h"
#include "color.h"
#include "fen-parser.h"
#include "state.h"

#include <functional>
#include <limits>
#include <map>
#include <memory>
#include <numeric>
#include <tuple>
#include <utility>
#include <vector>


class ChessAI {
    FenParser parser;
    PerceptSequence history;

    static bool wasCapture(const Bitboard& enemyBitboard, const Bitboard& move);
    static Piece findCapturePiece(const std::vector<Bitboard>& enemyBitboards, const Bitboard& enemyBitboard, const Bitboard& move);

    static Bitboard enpassantMoveGenerator(const Bitboard& enPassantSquares, const Bitboard& pawn, const Color& friendlyColor);
    static Bitboard castlingMoveGenerator(const Bitboard& allWhites, const Bitboard& allBlacks, const Bitboard& castlingSquares, const Bitboard& rook);
    static Bitboard kingLocationAfterCastling(const Bitboard& rookAfterCastling);

    static bool isEightfoldRepitionRule(const PerceptSequence& fromHistory);

    static Action depthLimitedMinimax(const int depthLimit, const State& state, const PerceptSequence& history);
    static float maxValue(const int depthLimit, const State& state, const Color& color, const PerceptSequence& history);
    static float minValue(const int depthLimit, const State& state, const Color& color, const PerceptSequence& history);

    static State flipColorAtPlay(State state) {
        state.colorAtPlay = static_cast<Color>((state.colorAtPlay + 1) % 2);
        return state;
    }


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

    static ChessOutcome terminalTest(const State& state, const Color& friendlyColor, const PerceptSequence& history);
    static float utilityFunction(const State& state, const Color& friendlyColor, const PerceptSequence& history);
    static float utilityHeurisitic(const State& state, const Color& friendlyColor);

    static Action minimax(const int depthLimit, const State& state, const PerceptSequence& history);

};



#endif /* chess_ai_h */

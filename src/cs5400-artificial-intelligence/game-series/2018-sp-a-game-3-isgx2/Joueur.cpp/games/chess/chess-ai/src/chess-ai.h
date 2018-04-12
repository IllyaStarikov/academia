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
#include "move-time-calculator.h"
#include "state.h"
#include "timer.h"

#include <algorithm>
#include <functional>
#include <limits>
#include <map>
#include <memory>
#include <numeric>
#include <random>
#include <tuple>
#include <utility>
#include <vector>

namespace ChessEngine {
    class ChessAI {
        FenParser parser;
        MoveTimeCalculator timeCalculator;

        PerceptSequence history;
        Timer moveTimer;

        double timeRemaining; // in seconds
        int halfMoveNumber;

        static bool wasCapture(const Bitboard& enemyBitboard, const Bitboard& move);
        static Piece findCapturePiece(const std::vector<Bitboard>& enemyBitboards, const Bitboard& enemyBitboard, const Bitboard& move);

        static Bitboard enpassantMoveGenerator(const Bitboard& enPassantSquares, const Bitboard& pawn, const Color& friendlyColor);
        static Bitboard castlingMoveGenerator(const Bitboard& allWhites, const Bitboard& allBlacks, const Bitboard& castlingSquares, const Bitboard& rook);
        static Bitboard kingLocationAfterCastling(const Bitboard& rookAfterCastling);

        static bool isEightfoldRepitionRule(const PerceptSequence& fromHistory);
        static bool insufficientMaterial(const State& currentState);
        static bool fiftyMoveRule(const PerceptSequence& history);

        std::shared_ptr<Action> depthLimitedMinimax(const int depthLimit, int quiescenceLimit, const double& timeLimit, const State& state, std::map<Action, int>& historyTable, const PerceptSequence& history);
        std::shared_ptr<float> maxValue(const int depthLimit, const int quiescenceLimit, const double& timeLimit, const State& state, const Action& action, float alpha, float beta, const Color& color, std::map<Action, int>& historyTable, const PerceptSequence& history);
        std::shared_ptr<float> minValue(const int depthLimit, int quiescenceLimit, const double& timeLimit, const State& state, const Action& action, float alpha, float beta, const Color& color, std::map<Action, int>& historyTable, const PerceptSequence& history);

        void addToHistoryTable(std::map<Action, int>& historyTable, const Action& action);

        static State flipColorAtPlay(State state) {
            state.colorAtPlay = static_cast<Color>((state.colorAtPlay + 1) % 2);
            return state;
        }

        static bool isNonQuiescenceState(const Action& action) {
            return action.wasCapture() || action.wasPromotion() || action.enemyInCheck();
        }

    public:
        State currentState;
        Color selfColor;

        ChessAI(const std::string& fenString);

        ChessAI() = delete;
        ChessAI(const ChessAI& other) = delete;
        ChessAI(ChessAI&& other) = delete;
        ChessAI& operator=(const ChessAI& other) = delete;
        ChessAI& operator=(ChessAI&& other) = delete;

        // MARK: AI Operators
        static State initialState();
        static std::vector<Action> actions(const State& state);
        static State result(const State& state, const Action& action);

        static ChessOutcome terminalTest(const State& state, const PerceptSequence& history);
        static float utilityFunction(const State& state, const Color& friendlyColor, const PerceptSequence& history);
        static float utilityHeurisitic(const State& state, const Color& friendlyColor);

        void updateTimer(const double& timeRemainingInSeconds);
        void updateMove(const Action& action);

        Action minimax(const double& timeLimit, const State& state, const PerceptSequence& history);

        Action move();
    };
}

#endif /* chess_ai_h */

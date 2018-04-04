//
//  chess-ai.cpp
//  src
//
//  Created by Illya Starikov on 03/07/18.
//  Copyright 2018. Illya Starikov. All rights reserved.
//

#include "chess-ai.h"

#include <algorithm>
#include <random>

using namespace ChessEngine;

ChessAI::ChessAI(const std::string& fenString): halfMoveNumber(2*parser.fullMoves(fenString)), currentState(parser(fenString)) {}

State ChessAI::initialState() {
    auto whiteBitboard = std::vector<Bitboard>(6), blackBitboard = std::vector<Bitboard>(6);
    Bitboard allWhites = 0xffff, allBlacks = 0xffff000000000000;
    auto enPassantSquares = Bitboard(0), castlingSquares = Bitboard(0x81) | Bitboard(0x8100000000000000);

    MoveEngine::generateInitialState(whiteBitboard, blackBitboard);
    return State(white, allWhites, allBlacks, whiteBitboard, blackBitboard, enPassantSquares, castlingSquares);
}

bool ChessAI::wasCapture(const Bitboard& enemyBitboard, const Bitboard& move) {
    static auto zeroBitboard = Bitboard(0);
    return (enemyBitboard & move) != zeroBitboard;
}
Piece ChessAI::findCapturePiece(const std::vector<Bitboard>& enemyBitboards, const Bitboard& enemyBitboard, const Bitboard& move) {
    // Just a simple short circuit
    if (!wasCapture(enemyBitboard, move)) { return king; }

    for (int i = 0; i < NUMBER_OF_PIECES; i++) {
        if ((move & enemyBitboards[i]) != 0) {
            return MoveEngine::intToPiece(i);
        }
    }

    return king;
}

Bitboard ChessAI::enpassantMoveGenerator(const Bitboard& enPassantSquares, const Bitboard& pawn, const Color& friendlyColor) {
    static const auto zeroBitboard = Bitboard(0);
    auto validSquaresToMoveEnPassant = MoveEngine::enpassantMoves(enPassantSquares, pawn);

    if (validSquaresToMoveEnPassant != zeroBitboard) {
        if (friendlyColor == white) {
            return MoveEngine::moving(enPassantSquares, north);
        } else {
            return MoveEngine::moving(enPassantSquares, south);
        }
    }

    return zeroBitboard;
}

Bitboard ChessAI::kingLocationAfterCastling(const Bitboard& rookAfterCastling) {
    static const auto zeroBitboard = Bitboard(0);

    static const auto whiteLongSideAfter = Bitboard(0x08), whiteShortSideAfter = Bitboard(0x20);
    static const auto blackLongSideAfter = Bitboard(0x800000000000000), blackShortSideAfter = Bitboard(0x2000000000000000);

    static const auto whiteLongSideKingLocation = Bitboard(0x04), whiteShortSideKingLocation = Bitboard(0x40);
    static const auto blackLongSideKingLocation = Bitboard(0x400000000000000), blackShortSideKingLocation = Bitboard(0x4000000000000000);

    if (rookAfterCastling == whiteLongSideAfter) {
        return whiteLongSideKingLocation;
    } else if (rookAfterCastling == whiteShortSideAfter) {
        return whiteShortSideKingLocation;
    } else if (rookAfterCastling == blackLongSideAfter) {
        return blackLongSideKingLocation;
    } else if (rookAfterCastling == blackShortSideAfter) {
        return blackShortSideKingLocation;
    }

    return zeroBitboard;
}

bool ChessAI::isEightfoldRepitionRule(const PerceptSequence& fromHistory) {
    if (fromHistory.size() < 8) { return false; }

    for (int i = 0; i < 4; i++) {
        if (fromHistory[i] != fromHistory[i + 4]) {
            return false;
        }
    }

    return fromHistory.movesSensePawnMovement() >= 8 && fromHistory.movesSenseCapture() >= 8;
}

std::shared_ptr<Action> ChessAI::depthLimitedMinimax(const int depthLimit, const double& timeLimit, const State& state, const PerceptSequence& history) {
    auto friendlyColor = state.colorAtPlay;
    auto possibleActions = actions(state);

    auto alpha = -std::numeric_limits<float>::infinity();
    auto beta = std::numeric_limits<float>::infinity();

    auto bestAction = possibleActions.back();
    auto currentMaxValue = minValue(depthLimit - 1, timeLimit, result(state, bestAction), alpha, beta, friendlyColor, history);

    possibleActions.pop_back();

    for (const auto& action : possibleActions) {
        auto value = minValue(depthLimit - 1, timeLimit, result(state, action), alpha, beta, friendlyColor, history);
        if (value == nullptr) {
            return nullptr;
        }

        if (value > currentMaxValue) {
            currentMaxValue = value;
            bestAction = action;
        }
    }

    return std::make_shared<Action>(bestAction);
}

std::shared_ptr<float> ChessAI::maxValue(const int depthLimit, const double& timeLimit, const State& state, float alpha, float beta, const Color& color, const PerceptSequence& history) {
    if (terminalTest(state, history) != nonterminal) { return std::make_shared<float>(utilityFunction(state, color, history)); }
    if (depthLimit <= 0) { return std::make_shared<float>(utilityHeurisitic(state, color)); }
    if (moveTimer.elapsed() > timeLimit) { return nullptr; }

    auto possibleActions = actions(state);
    auto value = -std::numeric_limits<float>::infinity();

    for (const auto& action : possibleActions) {
        auto newHistory = history;
        newHistory.add(result(state, action), action);

        auto newValue = minValue(depthLimit - 1, timeLimit, result(state, action), alpha, beta, color, newHistory);

        if (newValue == nullptr) {
            return nullptr;
        }

        value = std::max(value, *newValue);

        if (value >= beta) {
            return std::make_shared<float>(value);
        }

        alpha = std::max(alpha, value);
    }

    return std::make_shared<float>(value);
}

std::shared_ptr<float> ChessAI::minValue(const int depthLimit, const double& timeLimit, const State& state, float alpha, float beta, const Color& color, const PerceptSequence& history) {
    if (terminalTest(state, history) != nonterminal) { return std::make_shared<float>(utilityFunction(state, color, history)); }
    if (depthLimit <= 0) { return std::make_shared<float>(utilityHeurisitic(state, color)); }
    if (moveTimer.elapsed() > timeLimit) { return nullptr; }

    auto possibleActions = actions(state);
    auto value = std::numeric_limits<float>::infinity();

    for (const auto& action : possibleActions) {
        auto newHistory = history;
        newHistory.add(result(state, action), action);


        auto newValue = maxValue(depthLimit - 1, timeLimit, result(state, action), alpha, beta, color, newHistory);

        if (newValue == nullptr) {
            return nullptr;
        }

        value = std::min(value, *newValue);

        if (value <= alpha) {
            return std::make_shared<float>(value);
        }

        beta = std::min(beta, value);
    }

    return std::make_shared<float>(value);
}

Bitboard ChessAI::castlingMoveGenerator(const Bitboard& allWhites, const Bitboard& allBlacks, const Bitboard& castlingSquares, const Bitboard& rook) {
    static const auto zeroBitboard = Bitboard(0);

    static const auto whiteLongSideBefore = Bitboard(0x01), whiteShortSideBefore = Bitboard(0x80);
    static const auto blackLongSideBefore = Bitboard(0x100000000000000), blackShortSideBefore = Bitboard(0x8000000000000000);

    static const auto whiteLongSideAfter = Bitboard(0x08), whiteShortSideAfter = Bitboard(0x20);
    static const auto blackLongSideAfter = Bitboard(0x800000000000000), blackShortSideAfter = Bitboard(0x2000000000000000);

    auto possibleCastles = MoveEngine::castlingMoves(castlingSquares, allWhites, allBlacks);
    auto toReturn = zeroBitboard;

    // Just go through all of the possibilities and put those in a single bitboard
    if ((whiteLongSideBefore & possibleCastles & rook) != zeroBitboard) {
        toReturn |= whiteLongSideAfter;
    }

    if ((whiteShortSideBefore & possibleCastles & rook) != zeroBitboard) {
        toReturn |= whiteShortSideAfter;
    }

    if ((blackLongSideBefore & possibleCastles & rook) != zeroBitboard) {
        toReturn |= blackLongSideAfter;
    }

    if ((blackShortSideBefore & possibleCastles & rook) != zeroBitboard) {
        toReturn |= blackShortSideAfter;
    }

    return toReturn;
}

std::vector<Action> ChessAI::actions(const State& state) {
    static const auto zeroBitboard = Bitboard(0);
    static const auto firstEighthFile = Bitboard(0xff000000000000ff);

    std::vector<Action> actions;
    auto rng = std::default_random_engine {};

    // Dirty enum flip
    const auto& friendlyColor = state.colorAtPlay;
    const auto& enemyColor    = static_cast<Color>((state.colorAtPlay + 1) % 2);

    const auto& friendly = friendlyColor == white ? state.whites : state.blacks;
    const auto& enemy    = enemyColor    == white ? state.whites : state.blacks;

    const auto& allFriendly = friendlyColor == white ? state.allWhites : state.allBlacks;
    const auto& allEnemy    = enemyColor    == white ? state.allWhites : state.allBlacks;

    const auto& enPassantSquares = state.enPassantSquares;
    const auto& castlingSquares  = state.castlingSquares;

    // This is the main move generator. It keeps track of, in order:
    // 1. Which piece will be making this move
    // 2. Is it a castling move
    // 3. Is it an enpassant capture
    // 4. Given a board of the type from Step 1, what are all the possible places I can move with it.
    const std::vector<std::tuple<Piece, bool, bool, std::function<Bitboard(Bitboard)>>> moveGenerators = {
        std::make_tuple(king,   false, false, [&](const Bitboard& kingBoard)   { return MoveEngine::kingMoves  (kingBoard,   allFriendly                            ); } ),
        std::make_tuple(knight, false, false, [&](const Bitboard& knightBoard) { return MoveEngine::knightMoves(knightBoard, allFriendly                            ); } ),
        std::make_tuple(rook,   false, false, [&](const Bitboard& rookBoard)   { return MoveEngine::rookMoves  (rookBoard,   allFriendly, allEnemy                  ); } ),
        std::make_tuple(bishop, false, false, [&](const Bitboard& bishopBoard) { return MoveEngine::bishopMoves(bishopBoard, allFriendly, allEnemy                  ); } ),
        std::make_tuple(queen,  false, false, [&](const Bitboard& queenBoard)  { return MoveEngine::queenMoves (queenBoard,  allFriendly, allEnemy                  ); } ),
        std::make_tuple(pawn,   false, false, [&](const Bitboard& pawnBoard)   { return MoveEngine::pawnMoves  (pawnBoard,   allFriendly, allEnemy, friendlyColor); } ),
        std::make_tuple(pawn,   false, true , [&](const Bitboard& pawnBoard)   { return enpassantMoveGenerator  (pawnBoard,   enPassantSquares, friendlyColor);      } ),
        std::make_tuple(rook,   true,  false, [&](const Bitboard& rookBoard)   { return castlingMoveGenerator   (allFriendly, allEnemy, castlingSquares, rookBoard); } )
    };

    const auto promotablePieces = { queen, rook, bishop, knight };

    // Enumerating that behemoth that is the move generator
    for (const auto& pieceAndAttack : moveGenerators) {
        auto piece = std::get<0>(pieceAndAttack);
        auto isCastling  = std::get<1>(pieceAndAttack);
        auto isEnPassant = std::get<2>(pieceAndAttack);
        auto moveGenerator = std::get<3>(pieceAndAttack);

        auto currentBoard = friendly[MoveEngine::pieceToInt(piece)];

        for (const auto& pieceInsideBoard : currentBoard.seperated()) {
            // If I can't move anymore, I might as well not bother
            if (moveGenerator(pieceInsideBoard) == zeroBitboard) { continue; }

            // However, if I can move, figure out every place it can move
            auto locations = moveGenerator(pieceInsideBoard).seperated();

            for (const auto& newLocation : locations) {
                // Remove where the piece was, and place it down where it is now
                auto newAllFriendly = (allFriendly & (~currentBoard)) | newLocation;

                // If it's a capture, then might as well get rid of it
                auto newAllEnemy = (allEnemy & (~newLocation));

                // This is to handle an edge case. Suppose that I capture an enemy piece. Well, that's not reflected in all the enemy pieces
                // So, the enemy will will think they have one more piece than they really have. This is just saying pretend that I captured a piece
                // What would the new bitboard look like?
                auto temporaryAllEnemy = enemy;

                for (auto& pieces : temporaryAllEnemy) {
                    pieces &= newAllEnemy;
                }

                // Check everywhere the enemy can go after this move
                auto allEnemyMoves = MoveEngine::allStandardMovesInOneBitboard(temporaryAllEnemy, newAllEnemy, newAllFriendly, enemyColor);

                // Determine where the King currently is
                auto kingPiece = piece == king ? newLocation : friendly[MoveEngine::pieceToInt(king)];
                if (isCastling) {
                    kingPiece = kingLocationAfterCastling(newLocation);
                }

                // Determine if this move will lead to a pinned king
                auto enemiesThatCanAttackKing = allEnemyMoves & kingPiece;

                // If that's not zero, go ahead and add it to the possible actions
                if (enemiesThatCanAttackKing == zeroBitboard) {
                    auto wasACapture = wasCapture(allEnemy, newLocation);
                    auto capturedPiece = findCapturePiece(enemy, allEnemy, newLocation);

                    auto before = pieceInsideBoard;
                    auto after = newLocation;

                    // Handle promotions accordingly
                    if (piece == pawn && (newLocation & firstEighthFile) != zeroBitboard) {
                        auto wasPromotion = true;

                        // Add possible promotions to the board
                        for (const auto& promotedPiece : promotablePieces) {
                            auto promotedTo = promotedPiece;
                            auto action = Action(piece, friendlyColor, before, after, wasACapture, capturedPiece, wasPromotion, promotedTo, isEnPassant, isCastling);

                            actions.push_back(action);
                        }
                    } else {
                        auto wasPromotion = false;
                        auto promotedTo = king;

                        auto action = Action(piece, friendlyColor, before, after, wasACapture, capturedPiece, wasPromotion, promotedTo, isEnPassant, isCastling);
                        actions.push_back(action);
                    }
                }
            }

        }
    }

    std::shuffle(std::begin(actions), std::end(actions), rng);
    return actions;
}


State ChessAI::result(const State& state, const Action& action) {
    static const auto zeroBitboard = Bitboard(0);
    static const auto fourthFifthRank = Bitboard(0xffff000000);
    static const auto secondSeventhRank = Bitboard(0xff00000000ff00);

    auto piece = action.piece;
    auto pieceBefore = action.pieceBefore;
    auto pieceAfter = action.pieceAfter;

    auto wasCapture = action.wasCaptured;
    auto capturedPiece = action.pieceCaptured;

    auto oldColorAtPlay = state.colorAtPlay;
    auto newColorAtPlay = static_cast<Color>((state.colorAtPlay + 1) % 2);

    auto whites = state.whites;
    auto blacks = state.blacks;

    auto wasEnPassant = action.wasEnPassant;
    auto wasCastling = action.wasCastling;

    auto enPassantSquares = zeroBitboard;
    auto castlingSquares  = state.castlingSquares;

    // These two do the same thing, just for different colors
    if (oldColorAtPlay == white) {
        // Remove the piece from the board
        whites[MoveEngine::pieceToInt(piece)] ^= pieceBefore;
        // And place it in the appropriate place
        whites[MoveEngine::pieceToInt(piece)] |= pieceAfter;

        // If it was a capture, update the enemy board
        if (wasCapture) {
            blacks[MoveEngine::pieceToInt(capturedPiece)] ^= pieceAfter;
        }

        // If it was an enpassant capture, remove the enemy piece
        if (wasEnPassant) {
            blacks[MoveEngine::pieceToInt(pawn)] ^= state.enPassantSquares;
        }

        // If this was a castling move, update our new King location as well
        if (wasCastling) {
            whites[MoveEngine::pieceToInt(king)] = kingLocationAfterCastling(pieceAfter);
        }

    } else {
        // Remove the piece from the board
        blacks[MoveEngine::pieceToInt(piece)] ^= pieceBefore;
        // And place it in the appropriate place
        blacks[MoveEngine::pieceToInt(piece)] |= pieceAfter;

        // If it was a capture, update the enemy board
        if (wasCapture) {
            whites[MoveEngine::pieceToInt(capturedPiece)] ^= pieceAfter;
        }

        // If it was an enpassant capture, remove the enemy piece
        if (wasEnPassant) {
            whites[MoveEngine::pieceToInt(pawn)] ^= state.enPassantSquares;
        }

        // If this was a castling move, update our new King location as well
        if (wasCastling) {
            whites[MoveEngine::pieceToInt(king)] = kingLocationAfterCastling(pieceAfter);
        }
    }

    // If this was a rook, we want to make sure he no longer can castle.
    if (piece == rook) {
        castlingSquares ^= pieceBefore;

    // If this was a pawn and it moved up two, we want it to reflect that it's eligible for enpassant
    } else if (piece == pawn) {
        if ((pieceBefore & secondSeventhRank) != zeroBitboard && (pieceAfter & fourthFifthRank) != zeroBitboard) {
            enPassantSquares |= pieceAfter;
        }
    }

    auto allWhites = MoveEngine::allBitboardsInOneBoard(whites);
    auto allBlacks = MoveEngine::allBitboardsInOneBoard(blacks);


    return State(newColorAtPlay, allWhites, allBlacks, whites, blacks, enPassantSquares, castlingSquares);
}

ChessOutcome ChessAI::terminalTest(const State& state, const PerceptSequence& history) {
    static const auto zeroBitboard = Bitboard(0);

    std::vector<Action> actions;

    // Dirty enum flip
    const auto& friendlyColor = state.colorAtPlay;
    const auto& enemyColor    = static_cast<Color>((friendlyColor + 1) % 2);

    const auto& friendly = friendlyColor == white ? state.whites : state.blacks;
    const auto& enemy    = enemyColor    == white ? state.whites : state.blacks;

    const auto& allFriendly = friendlyColor == white ? state.allWhites : state.allBlacks;
    const auto& allEnemy    = enemyColor    == white ? state.allWhites : state.allBlacks;

    auto friendlyState = state, enemyState = state;
    enemyState.colorAtPlay = static_cast<Color>((state.colorAtPlay + 1) % 2);

    auto allEnemyMoves = MoveEngine::allStandardMovesInOneBitboard(enemy, allEnemy, allFriendly, enemyColor);

    if (ChessAI::actions(friendlyState).size() == 0) {
        if ((friendly[MoveEngine::pieceToInt(king)] & allEnemyMoves) == zeroBitboard) {
            return draw;
        } else {
            return loss;
        }
    } else if (isEightfoldRepitionRule(history)) {
        return draw;
    }

    // TODO: Insuffiient material

    return nonterminal;
}

float ChessAI::utilityFunction(const State& state, const Color& friendlyColor, const PerceptSequence& history) {
    auto terminalResult = terminalTest(state, history);
    ChessOutcome outcome;

    if (state.colorAtPlay == friendlyColor) {
        outcome = terminalResult;
    } else {
        if (terminalResult == nonterminal) {
            outcome = terminalResult;
        } else if (terminalResult == win) {
            outcome = loss;
        } else {
            outcome = win;
        }
    }

    if (outcome == win) {
        return std::numeric_limits<float>::infinity();
    } else if (outcome == loss) {
        return -std::numeric_limits<float>::infinity();
    } else {
        return 0;
    }
}

float ChessAI::utilityHeurisitic(const State& state, const Color& playerColor) {
    return ChessAIHeuristic<float>::materialAdvantage(state, playerColor);
}

void ChessAI::updateTimer(const double& timeRemainingInSeconds) {
    timeRemaining = timeRemainingInSeconds;
}

Action ChessAI::move() {
    moveTimer.start();

    auto timeLimit = timeCalculator(halfMoveNumber, timeRemaining);
    auto move = minimax(timeLimit, currentState, history);

    history.add(currentState, move);
    currentState = result(currentState, move);

    halfMoveNumber += 2;
    timeRemaining -= moveTimer.elapsed();

    moveTimer.stop();

    return move;
}

Action ChessAI::minimax(const double& timeLimit, const State& state, const PerceptSequence& history) {
    static Timer localTimer;

    int depthLimit = 1;

    Action lastMove = actions(state)[0];
    std::shared_ptr<Action> move;

    do {
        localTimer.start();
        move = depthLimitedMinimax(depthLimit++, timeLimit, state, history);
        localTimer.stop();

        if (move != nullptr) {
            lastMove = *move;
        }
    } while (moveTimer.elapsed() + localTimer.elapsed() < timeLimit);

    return lastMove;
}


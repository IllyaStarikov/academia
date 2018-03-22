//
//  chess-heuristic.h
//  src
//
//  Created by Illya Starikov on 03/18/18.
//  Copyright 2018. Illya Starikov. All rights reserved.
//

#ifndef chess_heuristic_h
#define chess_heuristic_h

#include "chess-engine.h"
#include "chess-pieces.h"
#include "color.h"
#include "state.h"

#include <map>


template <class T>
class ChessAIHeuristic {
    public:
        static T materialAdvantage(const State& state, const Color& playerColor);
};

template <class T>
T ChessAIHeuristic<T>::materialAdvantage(const State& state, const Color& playerColor) {
    static std::map<Piece, int> pieceWeights = {
        {pawn,   1},
        {knight, 3},
        {bishop, 3},
        {rook,   5},
        {queen,  9}
    };

    T value = 0;
    for (const auto& element : pieceWeights) {
        auto piece = element.first;
        auto pieceWeight = element.second;

        auto numberOfFriendlyPieces = playerColor == white ? state.whites[ChessEngine::pieceToInt(piece)].numberOfBits() : state.blacks[ChessEngine::pieceToInt(piece)].numberOfBits();
        auto numberOfEnemyPieces = playerColor == white ? state.blacks[ChessEngine::pieceToInt(piece)].numberOfBits() : state.whites[ChessEngine::pieceToInt(piece)].numberOfBits();

        auto difference = static_cast<T>(pieceWeight) * (numberOfFriendlyPieces - numberOfEnemyPieces);
        value += difference;
    }

    return value;
}

#endif /* chess-heuristic_h */


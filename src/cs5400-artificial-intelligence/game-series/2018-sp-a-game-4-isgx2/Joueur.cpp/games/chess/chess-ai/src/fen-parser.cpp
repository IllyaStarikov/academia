//
//  fen-parser.cpp
//  src
//
//  Created by Illya Starikov on 03/08/18.
//  Copyright 2018. Illya Starikov. All rights reserved.
//

#include "fen-parser.h"
using namespace ChessEngine;

std::string FenParser::getToken(const FenToken& token) {
    // lol sorry
    const auto regexString = R"((([pPnNbBrRqQkK0-8]{1,8}/?){8})\s*(w|b)\s*([KQkq-]{0,4})\s*([a-hA-H0-8\-]{1,2})\s*(\d+)\s*(\d+)*)";
    auto regexExpression = std::regex(regexString);
    auto match = std::smatch();

    if (std::regex_search(fenString, match, regexExpression)) {
        switch (token) {
            case board:       return match[1];
            case colorAtPlay: return match[3]; // don't ask why it's off by one, regex error
            case castling:    return match[4];
            case enPassant:   return match[5];
            case halfTurns:   return match[6];
            case fullTurns:   return match[7];
            default:          throw std::logic_error("Fen String is fucking broke");
        }
    } else {
        std::cout << fenString;

        throw std::logic_error("Fen String is fucking broke");
    }
}

void FenParser::parseBoard(std::vector<Bitboard>& whiteBitboard, std::vector<Bitboard>& blackBitboard) {
    auto token = getToken(board);
    token.erase(std::remove(token.begin(), token.end(), '/'), token.end());

    std::map<char, std::pair<Color, Piece>> pieces = {
        {'P', std::make_pair(white, pawn)},
        {'N', std::make_pair(white, knight)},
        {'B', std::make_pair(white, bishop)},
        {'R', std::make_pair(white, rook)},
        {'Q', std::make_pair(white, queen)},
        {'K', std::make_pair(white, king)},
        {'p', std::make_pair(black, pawn)},
        {'n', std::make_pair(black, knight)},
        {'b', std::make_pair(black, bishop)},
        {'r', std::make_pair(black, rook)},
        {'q', std::make_pair(black, queen)},
        {'k', std::make_pair(black, king)}
    };

    // A temporary counter to keep of the index on the bitboard
    int i = 0;
    // Go through all the characters
    for (const auto& characterAtIndex : token) {
        // Because the Fen string starts at top left and my bitboard starts at the bottom left
        // I have to do this sort of translation to make sure my indices line up
        int bitboardIndex = (8*((63 - i) / 8) + (i % 8));

        if (isdigit(characterAtIndex)) {
            i += static_cast<int>(characterAtIndex) - 48 - 1;
        } else if (pieces.find(characterAtIndex) != pieces.end()) {
            auto result = pieces[characterAtIndex];

            if (result.first == white) {
                whiteBitboard[MoveEngine::pieceToInt(result.second)] |= Bitboard().fromIndex(bitboardIndex);
            } else if (result.first == black) {
                blackBitboard[MoveEngine::pieceToInt(result.second)] |= Bitboard().fromIndex(bitboardIndex);
            } else {
                throw std::logic_error("Fen Parser color is not white or black");
            }
        } else {
            throw std::logic_error("Illegal Character In Fen String");
        }

        i++;
    }
}

Color FenParser::parseColorAtPlay() {
    auto token = getToken(colorAtPlay);

    if (token == "w") {
        return white;
    } else {
        return black;
    }
}

Bitboard FenParser::parseCastling() {
    static const Bitboard whiteShortSide = 0x80, whiteLongSide = 0x01;
    static const Bitboard blackShortSide = 0x8000000000000000, blackLongSide = 0x100000000000000;

    static const auto zeroBitboard = Bitboard(0);

    auto token = getToken(castling);
    auto result = zeroBitboard;

    if (token.find("Q") != std::string::npos) {
        result |= whiteLongSide;
    }

    if (token.find("K") != std::string::npos) {
        result |= whiteShortSide;
    }

    if (token.find("q") != std::string::npos) {
        result |= blackLongSide;
    }

    if (token.find("k") != std::string::npos) {
        result |= blackShortSide;
    }

    return result;
}

Bitboard FenParser::parseEnPassant() {
    auto token = getToken(enPassant);
    static const auto zeroBitboard = Bitboard(0);

    if (token == "-") {
        return zeroBitboard;
    } else {
        // These two are identical, just one is for a lowercase `a` and uppercase `A`
        if (token[0] <= 'z' and token[0] >= 'a') {
            auto fileWeight = static_cast<int>(token[0]) - static_cast<int>('a');
            auto rankWeight = 8 * (static_cast<int>(token[1]) - 1 - 48);

            return Bitboard().fromIndex(rankWeight + fileWeight);
        } else {
            auto fileWeight = static_cast<int>(token[0]) - static_cast<int>('A');
            auto rankWeight = 8 * (static_cast<int>(token[1]) - 1 - 48);

            return Bitboard().fromIndex(rankWeight + fileWeight);
        }
    }
}

short FenParser::parseHalfMoves() {
    auto token = getToken(halfTurns);
    return stoi(token);
}

short FenParser::parseFullMoves() {
    auto token = getToken(fullTurns);
    return stoi(token);
}

State FenParser::operator()(const std::string &string) {
    this -> fenString = string;

    auto whiteBitboards = std::vector<Bitboard>(6), blackBitboards = std::vector<Bitboard>(6);
    parseBoard(whiteBitboards, blackBitboards);

    auto allWhites = MoveEngine::allBitboardsInOneBoard(whiteBitboards), allBlacks = MoveEngine::allBitboardsInOneBoard(blackBitboards);

    auto colorAtPlay = parseColorAtPlay();
    auto enpassant = parseEnPassant();
    auto castling = parseCastling();

    return State(colorAtPlay, allWhites, allBlacks, whiteBitboards, blackBitboards, enpassant, castling);
}

short FenParser::halfMoves(const std::string &string) {
    this -> fenString = string;

    return parseHalfMoves();
}

short FenParser::fullMoves(const std::string &string) {
    this -> fenString = string;

    return parseFullMoves();
}

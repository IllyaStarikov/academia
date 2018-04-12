//
//  AI.cpp
//  src
//
//  Created by Illya Starikov on 02/26/18.
//  Copyright 2018. Illya Starikov. All rights reserved.
//


#include "chess-engine.h"
using namespace ChessEngine;

// MARK: Private Methods
Bitboard MoveEngine::northMovesWithBlockers(Bitboard board, const Bitboard& blockerInverse) {
    auto result = board;

    // Move the board north until you reach a blocker. The blockers are inversed, so the blocking squares will be zero.
    // Because this a bitwise & (and), as soon as it reaches the blocker, it won't go to that spot. We keep shifting
    // 7 times because that's the length of the board minus the current piece on it.
    //
    // Reference `moving` to see why the board is shifted this way.
    result |= board = (board << 8) & blockerInverse;
    result |= board = (board << 8) & blockerInverse;
    result |= board = (board << 8) & blockerInverse;
    result |= board = (board << 8) & blockerInverse;
    result |= board = (board << 8) & blockerInverse;
    result |= board = (board << 8) & blockerInverse;
    result |= board = (board << 8) & blockerInverse;

    return result;
}

Bitboard MoveEngine::southMovesWithBlockers(Bitboard board, const Bitboard& blockerInverse) {
    auto result = board;

    // Move the board south until you reach a blocker. The blockers are inversed, so the blocking squares will be zero.
    // Because this a bitwise & (and), as soon as it reaches the blocker, it won't go to that spot. We keep shifting
    // 7 times because that's the length of the board minus the current piece on it.
    //
    // Reference `moving` to see why the board is shifted this way.
    result |= board = (board >> 8) & blockerInverse;
    result |= board = (board >> 8) & blockerInverse;
    result |= board = (board >> 8) & blockerInverse;
    result |= board = (board >> 8) & blockerInverse;
    result |= board = (board >> 8) & blockerInverse;
    result |= board = (board >> 8) & blockerInverse;
    result |= board = (board >> 8) & blockerInverse;

    return result;
}

Bitboard MoveEngine::eastMovesWithBlockers(Bitboard board, const Bitboard& blockerInverse) {
    const static Bitboard aFileInverse = 0xfefefefefefefefe;

    // We have to consider wraparound for east/west movement, so to prevent that, we don't allow squares to go bast that file.
    auto result = board;
    auto blockerAndFileInverse = blockerInverse & aFileInverse;

    // Move the board east until you reach a blocker. The blockers are inversed, so the blocking squares will be zero.
    // Because this a bitwise & (and), as soon as it reaches the blocker, it won't go to that spot. We keep shifting
    // 7 times because that's the length of the board minus the current piece on it.
    //
    // Reference `moving` to see why the board is shifted this way.
    result |= board = (board << 1) & blockerAndFileInverse;
    result |= board = (board << 1) & blockerAndFileInverse;
    result |= board = (board << 1) & blockerAndFileInverse;
    result |= board = (board << 1) & blockerAndFileInverse;
    result |= board = (board << 1) & blockerAndFileInverse;
    result |= board = (board << 1) & blockerAndFileInverse;
    result |= board = (board << 1) & blockerInverse;

    return result;
}

Bitboard MoveEngine::westMovesWithBlockers(Bitboard board, const Bitboard& blockerInverse) {
    const static Bitboard hFileInverse = 0x7f7f7f7f7f7f7f7f;

    // We have to consider wraparound for east/west movement, so to prevent that, we don't allow squares to go bast that file.
    auto result = board;
    auto blockerAndFileInverse = blockerInverse & hFileInverse;

    // Move the board west until you reach a blocker. The blockers are inversed, so the blocking squares will be zero.
    // Because this a bitwise & (and), as soon as it reaches the blocker, it won't go to that spot. We keep shifting
    // 7 times because that's the length of the board minus the current piece on it.
    //
    // Reference `moving` to see why the board is shifted this way.
    result |= board = (board >> 1) & blockerAndFileInverse;
    result |= board = (board >> 1) & blockerAndFileInverse;
    result |= board = (board >> 1) & blockerAndFileInverse;
    result |= board = (board >> 1) & blockerAndFileInverse;
    result |= board = (board >> 1) & blockerAndFileInverse;
    result |= board = (board >> 1) & blockerAndFileInverse;
    result |= board = (board >> 1) & blockerInverse;

    return result;
}


Bitboard MoveEngine::northeastMovesWithBlockers(Bitboard board, const Bitboard& blockerInverse) {
    const static Bitboard aFileInverse = 0xfefefefefefefefe;

    // We have to consider wraparound for east/west movement, so to prevent that, we don't allow squares to go bast that file.
    auto result = board;
    auto blockerAndFileInverse = blockerInverse & aFileInverse;

    // Move the board west until you reach a blocker. The blockers are inversed, so the blocking squares will be zero.
    // Because this a bitwise & (and), as soon as it reaches the blocker, it won't go to that spot. We keep shifting
    // 7 times because that's the length of the board minus the current piece on it.
    //
    // Reference `moving` to see why the board is shifted this way.
    result |= board = (board << 9) & blockerAndFileInverse;
    result |= board = (board << 9) & blockerAndFileInverse;
    result |= board = (board << 9) & blockerAndFileInverse;
    result |= board = (board << 9) & blockerAndFileInverse;
    result |= board = (board << 9) & blockerAndFileInverse;
    result |= board = (board << 9) & blockerAndFileInverse;
    result |= board = (board << 9) & blockerInverse;

    return result;
}

Bitboard MoveEngine::northwestMovesWithBlockers(Bitboard board, const Bitboard& blockerInverse) {
    const static Bitboard hFileInverse = 0x7f7f7f7f7f7f7f7f;

    // We have to consider wraparound for east/west movement, so to prevent that, we don't allow squares to go bast that file.
    auto result = board;
    auto blockerAndFileInverse = blockerInverse & hFileInverse;

    // Move the board northwest west until you reach a blocker. The blockers are inversed, so the blocking squares will be zero.
    // Because this a bitwise & (and), as soon as it reaches the blocker, it won't go to that spot. We keep shifting
    // 7 times because that's the length of the board minus the current piece on it.
    //
    // Reference `moving` to see why the board is shifted this way.
    result |= board = (board << 7) & blockerAndFileInverse;
    result |= board = (board << 7) & blockerAndFileInverse;
    result |= board = (board << 7) & blockerAndFileInverse;
    result |= board = (board << 7) & blockerAndFileInverse;
    result |= board = (board << 7) & blockerAndFileInverse;
    result |= board = (board << 7) & blockerAndFileInverse;
    result |= board = (board << 7) & blockerInverse;

    return result;
}

Bitboard MoveEngine::southeastMovesWithBlockers(Bitboard board, const Bitboard& blockerInverse) {
    const static Bitboard aFileInverse = 0xfefefefefefefefe;

    // We have to consider wraparound for east/west movement, so to prevent that, we don't allow squares to go bast that file.
    auto result = board;
    auto blockerAndFileInverse = blockerInverse & aFileInverse;

    // Move the board southeast until you reach a blocker. The blockers are inversed, so the blocking squares will be zero.
    // Because this a bitwise & (and), as soon as it reaches the blocker, it won't go to that spot. We keep shifting
    // 7 times because that's the length of the board minus the current piece on it.
    //
    // Reference `moving` to see why the board is shifted this way.
    result |= board = (board >> 7) & blockerAndFileInverse;
    result |= board = (board >> 7) & blockerAndFileInverse;
    result |= board = (board >> 7) & blockerAndFileInverse;
    result |= board = (board >> 7) & blockerAndFileInverse;
    result |= board = (board >> 7) & blockerAndFileInverse;
    result |= board = (board >> 7) & blockerAndFileInverse;
    result |= board = (board >> 7) & blockerInverse;

    return result;
}

Bitboard MoveEngine::southwestMovesWithBlockers(Bitboard board, const Bitboard& blockerInverse) {
    const static Bitboard hFileInverse = 0x7f7f7f7f7f7f7f7f;

    // We have to consider wraparound for east/west movement, so to prevent that, we don't allow squares to go bast that file.
    auto result = board;
    auto blockerAndFileInverse = blockerInverse & hFileInverse;

    // Move the board south west until you reach a blocker. The blockers are inversed, so the blocking squares will be zero.
    // Because this a bitwise & (and), as soon as it reaches the blocker, it won't go to that spot. We keep shifting
    // 7 times because that's the length of the board minus the current piece on it.
    //
    // Reference `moving` to see why the board is shifted this way.
    result |= board = (board >> 9) & blockerAndFileInverse;
    result |= board = (board >> 9) & blockerAndFileInverse;
    result |= board = (board >> 9) & blockerAndFileInverse;
    result |= board = (board >> 9) & blockerAndFileInverse;
    result |= board = (board >> 9) & blockerAndFileInverse;
    result |= board = (board >> 9) & blockerAndFileInverse;
    result |= board = (board >> 9) & blockerInverse;

    return result;
}

Bitboard MoveEngine::pawnNorthMovesWithBlockers(Bitboard board, const Bitboard& blockerInverse) {
    auto result = board;

    // Move the board north by one until you reach a blocker. The blockers are inversed, so the blocking squares will be zero.
    // Because this a bitwise & (and), as soon as it reaches the blocker, it won't go to that spot. We keep shifting
    // 7 times because that's the length of the board minus the current piece on it.
    //
    // Reference `moving` to see why the board is shifted this way.
    result |= board = (board << 8) & blockerInverse;

    return result;
}

Bitboard MoveEngine::pawnNorthNorthMovesWithBlockers(Bitboard board, const Bitboard& blockerInverse) {
    auto result = board;

    // Move the board north by two until you reach a blocker. The blockers are inversed, so the blocking squares will be zero.
    // Because this a bitwise & (and), as soon as it reaches the blocker, it won't go to that spot. We keep shifting
    // 7 times because that's the length of the board minus the current piece on it.
    //
    // Reference `moving` to see why the board is shifted this way.
    result |= board = (board << 8) & blockerInverse;
    result |= board = (board << 8) & blockerInverse;

    return result;
}

Bitboard MoveEngine::pawnSouthMovesWithBlockers(Bitboard board, const Bitboard& blockerInverse) {
    auto result = board;

    // Move the board south by one until you reach a blocker. The blockers are inversed, so the blocking squares will be zero.
    // Because this a bitwise & (and), as soon as it reaches the blocker, it won't go to that spot. We keep shifting
    // 7 times because that's the length of the board minus the current piece on it.
    //
    // Reference `moving` to see why the board is shifted this way.
    result |= board = (board >> 8) & blockerInverse;

    return result;
}

Bitboard MoveEngine::pawnSouthSouthMovesWithBlockers(Bitboard board, const Bitboard& blockerInverse) {
    auto result = board;

    // Move the board south by two until you reach a blocker. The blockers are inversed, so the blocking squares will be zero.
    // Because this a bitwise & (and), as soon as it reaches the blocker, it won't go to that spot. We keep shifting
    // 7 times because that's the length of the board minus the current piece on it.
    //
    // Reference `moving` to see why the board is shifted this way.
    result |= board = (board >> 8) & blockerInverse;
    result |= board = (board >> 8) & blockerInverse;

    return result;
}

std::vector<std::pair<char, int>> MoveEngine::bitStringToDescription(Bitboard board) {
    std::vector<int> indices = board.toIndices();
    auto solution = std::vector<std::pair<char, int>>();

    char file;
    int rank;

    for (const auto& index : indices) {
        // This is just a simple formula to turn an index into a file and rank
        //
        // The file lies on the horizontal strip, but resets, so we mod by eight,
        // and add 65 because that's where the `a` starts.
        //
        // The rank increases much more drastically. Just do
        file = static_cast<char>(static_cast<int>(index % 8) + 65);
        rank = static_cast<int>(index / 8.0 + 1.0);

        solution.push_back(std::make_pair(file, rank));
    }


    return solution;
}

int MoveEngine::pieceToInt(const Piece piece) {
    // Just a rapper for a static cast
    return static_cast<int>(piece);
}

Piece MoveEngine::intToPiece(const int integer) {
    // Just a rapper for a static cast
    return static_cast<Piece>(integer);
}

void MoveEngine::generateInitialState(std::vector<Bitboard>& white, std::vector<Bitboard>& black) {
    // Ugly, but these values are hand-calculated to be the initial state
    white[pieceToInt(king)]   = Bitboard().fromIndex(4);
    white[pieceToInt(queen)]  = Bitboard().fromIndex(3);
    white[pieceToInt(rook)]   = Bitboard().fromIndex(0) | Bitboard().fromIndex(7);
    white[pieceToInt(bishop)] = Bitboard().fromIndex(2) | Bitboard().fromIndex(5);
    white[pieceToInt(knight)] = Bitboard().fromIndex(1) | Bitboard().fromIndex(6);
    white[pieceToInt(pawn)]   = Bitboard().fromIndex(8) | Bitboard().fromIndex(9) | Bitboard().fromIndex(10) | Bitboard().fromIndex(11) | Bitboard().fromIndex(12) | Bitboard().fromIndex(13) | Bitboard().fromIndex(14) | Bitboard().fromIndex(15);

    black[pieceToInt(king)]   = Bitboard().fromIndex(60);
    black[pieceToInt(queen)]  = Bitboard().fromIndex(59);
    black[pieceToInt(rook)]   = Bitboard().fromIndex(56) | Bitboard().fromIndex(63);
    black[pieceToInt(bishop)] = Bitboard().fromIndex(58) | Bitboard().fromIndex(61);
    black[pieceToInt(knight)] = Bitboard().fromIndex(57) | Bitboard().fromIndex(62);
    black[pieceToInt(pawn)]   = Bitboard().fromIndex(48) | Bitboard().fromIndex(49) | Bitboard().fromIndex(50) | Bitboard().fromIndex(51) | Bitboard().fromIndex(52) | Bitboard().fromIndex(53) | Bitboard().fromIndex(54) | Bitboard().fromIndex(55);
}


Bitboard MoveEngine::allBitboardsInOneBoard(const std::vector<Bitboard> boards) {
    return boards[static_cast<int>(king)]
         | boards[static_cast<int>(queen)]
         | boards[static_cast<int>(rook)]
         | boards[static_cast<int>(bishop)]
         | boards[static_cast<int>(knight)]
         | boards[static_cast<int>(pawn)];
}


Bitboard MoveEngine::moving(const Bitboard& board, const Direction& direction) {
    // these are to prevent wraps when bit shifting (i.e., 1H can't move into the 2A spot just by moving right)
    const static Bitboard aFileInverse = 0xfefefefefefefefe;
    const static Bitboard hFileInverse = 0x7f7f7f7f7f7f7f7f;

    // So this is.. Neat. Indexing starts at the bottom left (A1) and goes right, until there's a wrap around.
    // After that, the next level is one above the leftmost piece. So, the board's looks like this:
    // 9.......
    // 12345678
    // So to move up, just do a bit shift of eight to the left (because LSB is on the right of binary strings).
    // West is more difficult, because there's the possibility of moving at a cell to wrap up above or below in the
    // bit string, we have to and with the leftmost and rightmost files.
    switch (direction) {
        case north:     return  board << 8;
        case south:     return  board >> 8;
        case east:      return (board << 1) & aFileInverse;
        case west:      return (board >> 1) & hFileInverse;
        case northeast: return (board << 9) & aFileInverse;
        case northwest: return (board << 7) & hFileInverse;
        case southeast: return (board >> 7) & aFileInverse;
        case southwest: return (board >> 9) & hFileInverse;
        default:        return Bitboard();
    }
}

Bitboard MoveEngine::kingMoves(const Bitboard& king, const Bitboard& self) {
    // The ~self is to make sure we don't move over our own piece.
    return (moving(king, north    )
          | moving(king, south    )
          | moving(king, east     )
          | moving(king, west     )
          | moving(king, northeast)
          | moving(king, northwest)
          | moving(king, southeast)
          | moving(king, southwest))
          & (~self);
}

Bitboard MoveEngine::knightMoves(const Bitboard& knight, const Bitboard& self) {
    // So, this is ugly, inlined math. But it's better than moving a piece
    // five times.

    const static Bitboard aFileInverse  = 0xfefefefefefefefe;
    const static Bitboard hFileInverse  = 0x7f7f7f7f7f7f7f7f;
    const static Bitboard abFileInverse = 0xfcfcfcfcfcfcfcfc;
    const static Bitboard ghFileInverse = 0x3f3f3f3f3f3f3f3f;

    // The ~self is to make sure we don't move over our own piece.
    return (((knight << 17) & aFileInverse )
          | ((knight >> 15) & aFileInverse )
          | ((knight << 15) & hFileInverse )
          | ((knight >> 17) & hFileInverse )
          | ((knight << 10) & abFileInverse)
          | ((knight >> 6 ) & abFileInverse)
          | ((knight >> 10) & ghFileInverse)
          | ((knight << 6 ) & ghFileInverse))
          & (~self);
}


Bitboard MoveEngine::rookMoves(const Bitboard& rook, Bitboard self, Bitboard enemy) {
    self = ~self;
    enemy = ~enemy;

    // The ~self is to make sure our own piece isn't staying still (because the
    // ...WithBlockers attacks do return the piece in the same location.
    return (northMovesWithBlockers(rook, self & moving(enemy, north))
          | southMovesWithBlockers(rook, self & moving(enemy, south))
          | westMovesWithBlockers (rook, self & moving(enemy, west))
          | eastMovesWithBlockers (rook, self & moving(enemy, east)))
          ^ rook;
}

Bitboard MoveEngine::bishopMoves(const Bitboard& bishop, Bitboard self, Bitboard enemy) {
    self = ~self;
    enemy = ~enemy;

    // The ~self is to make sure our own piece isn't staying still (because the
    // ...WithBlockers attacks do return the piece in the same location.
    return (northeastMovesWithBlockers(bishop, self & moving(enemy, northeast))
          | northwestMovesWithBlockers(bishop, self & moving(enemy, northwest))
          | southeastMovesWithBlockers(bishop, self & moving(enemy, southeast))
          | southwestMovesWithBlockers(bishop, self & moving(enemy, southwest)))
          ^ bishop;
}

Bitboard MoveEngine::queenMoves(const Bitboard& queen, Bitboard self, Bitboard enemy) {
    self = ~self;
    enemy = ~enemy;

    // The ~self is to make sure our own piece isn't staying still (because the
    // ...WithBlockers attacks do return the piece in the same location.
    return (northMovesWithBlockers    (queen, self & moving(enemy, north))
          | southMovesWithBlockers    (queen, self & moving(enemy, south))
          | westMovesWithBlockers     (queen, self & moving(enemy, west))
          | eastMovesWithBlockers     (queen, self & moving(enemy, east))
          | northeastMovesWithBlockers(queen, self & moving(enemy, northeast))
          | northwestMovesWithBlockers(queen, self & moving(enemy, northwest))
          | southeastMovesWithBlockers(queen, self & moving(enemy, southeast))
          | southwestMovesWithBlockers(queen, self & moving(enemy, southwest)))
          ^ queen;
}

Bitboard MoveEngine::pawnMoves(const Bitboard& pawn, Bitboard self, Bitboard enemy, const Color& selfColor) {
    const auto enemyOriginal = enemy;

    self = ~self;
    enemy = ~enemy;

    static Bitboard secondRank = 0xff00;
    static Bitboard seventhRank = 0xff000000000000;

    // The ~self is to make sure our own piece isn't staying still (because the
    // ...WithBlockers attacks do return the piece in the same location.
    if (selfColor == white) {
        return (pawnNorthMovesWithBlockers(pawn, self & enemy)
              | pawnNorthNorthMovesWithBlockers(pawn & secondRank, self & enemy)
              | (moving(pawn, northeast) & enemyOriginal)
              | (moving(pawn, northwest) & enemyOriginal))
              ^ pawn;
    } else {
        return (pawnSouthMovesWithBlockers(pawn, self & enemy)
              | pawnSouthSouthMovesWithBlockers(pawn & seventhRank, self & enemy)
              | (moving(pawn, southeast) & enemyOriginal)
              | (moving(pawn, southwest) & enemyOriginal))
              ^ pawn;
    }
}

Bitboard MoveEngine::castlingMoves(const Bitboard& castlingSquares, const Bitboard& allWhite, const Bitboard& allBlacks) {
    const static Bitboard longCastling = 0x01, shortCastling = 0x08;
    const static Bitboard longCastlingObstacleSquares = 0x0e, shortCastlingObstacleSquares = 0x60;

    Bitboard obstacles = allBlacks | allWhite;
    Bitboard shortCastlingFromSquares =  castlingSquares & shortCastling, longCastlingFromSquares = castlingSquares & longCastling;

    Bitboard result;

    // this will calculate *every* castling square, whites and blacks included, so just two move generators
    if ((obstacles & longCastlingObstacleSquares) == 0 && (longCastlingFromSquares & longCastling) != 0) {
        result |= longCastling;
    }

    if ((obstacles & shortCastlingObstacleSquares) == 0 && (shortCastlingFromSquares & shortCastling) != 0) {
        result |= shortCastling;
    }

    return result;
}

Bitboard MoveEngine::enpassantMoves(const Bitboard& enemyEnpassantSquares, const Bitboard& selfPawns) {
    // Simple check to see if an enpassant square is next to one of our own
    return (moving(enemyEnpassantSquares, east) & selfPawns) | (moving(enemyEnpassantSquares, west) & selfPawns);
}

//
//  bitboard.cpp
//  src
//
//  Created by Illya Starikov on 03/01/18.
//  Copyright 2018. Illya Starikov. All rights reserved.
//

#include "bitboard.h"

// MARK: Constructors
Bitboard::Bitboard(): board(0) {}

Bitboard::Bitboard(const uint64_t board): board(board) {}

// MARK: Assignment
Bitboard& Bitboard::operator=(const Bitboard& right) {
    if (this != &right) {
        this -> board = right.board;
    }

    return *this;
}

Bitboard& Bitboard::operator=(Bitboard&& right) {
    if (this != &right) {
        this -> board = right.board;
    }

    return *this;
}

Bitboard Bitboard::operator~() const noexcept {
    return Bitboard(~(this -> board));
}


// Mark: Operators
bool Bitboard::operator==(const Bitboard& right) const noexcept {
    return this -> board == right.board;
}

bool Bitboard::operator!=(const Bitboard& right) const noexcept {
    return !(*this == right);
}

Bitboard Bitboard::operator>>(const int shift) const noexcept {
    return Bitboard(this -> board >> shift);
}

Bitboard Bitboard::operator<<(const int shift) const noexcept {
    return Bitboard(this -> board << shift);
}

Bitboard Bitboard::operator|(const Bitboard& right) const noexcept {
    return Bitboard(this -> board | right.board);
}

Bitboard Bitboard::operator&(const Bitboard& right) const noexcept {
    return Bitboard(this -> board & right.board);
}

Bitboard Bitboard::operator^(const Bitboard& right) const noexcept {
    return Bitboard(this -> board ^ right.board);
}

Bitboard& Bitboard::operator|=(const Bitboard& right) noexcept {
    this -> board = this -> board | right.board;
    return *this;
}

Bitboard& Bitboard::operator&=(const Bitboard& right) noexcept {
    this -> board = this -> board & right.board;
    return *this;
}

Bitboard& Bitboard::operator^=(const Bitboard& right) noexcept {
    this -> board = this -> board ^ right.board;
    return *this;
}



// MARK: Properties
std::vector<int> Bitboard::toIndices() {
    auto solution = std::vector<int>();
    auto index = 0;

    auto temporaryBoard = this -> board;

    while (temporaryBoard) {
        if ((temporaryBoard & 1) == 1) {
            solution.push_back(index);
        }

        index += 1;
        temporaryBoard = temporaryBoard >> 1;
    }

    return solution;
}

// MARK: Properties
std::vector<Bitboard> Bitboard::seperated() const {
    // If it is a power of two, it means it's a single index
    // If so, we can do a single lookup
    if ((this -> board & (this -> board - 1)) == 0) {
        return { Bitboard(this -> board) };
    } else {
        auto solution = std::vector<Bitboard>();

        uint64_t board = 1;
        uint64_t temporaryBoard = this -> board;

        while (temporaryBoard) {
            if ((temporaryBoard & 1) == 1) {
                solution.push_back(board);
            }

            temporaryBoard = temporaryBoard >> 1;
            board = board << 1;
        }

        return solution;
    }
}

Bitboard& Bitboard::fromIndex(const int index) {
    static constexpr uint64_t indexes[] =  {0x1, 0x2, 0x4, 0x8, 0x10, 0x20, 0x40, 0x80, 0x100, 0x200, 0x400, 0x800, 0x1000, 0x2000, 0x4000, 0x8000, 0x10000, 0x20000, 0x40000, 0x80000, 0x100000, 0x200000, 0x400000, 0x800000, 0x1000000, 0x2000000, 0x4000000, 0x8000000, 0x10000000, 0x20000000, 0x40000000, 0x80000000, 0x100000000, 0x200000000, 0x400000000, 0x800000000, 0x1000000000, 0x2000000000, 0x4000000000, 0x8000000000, 0x10000000000, 0x20000000000, 0x40000000000, 0x80000000000, 0x100000000000, 0x200000000000, 0x400000000000, 0x800000000000, 0x1000000000000, 0x2000000000000, 0x4000000000000, 0x8000000000000, 0x10000000000000, 0x20000000000000, 0x40000000000000, 0x80000000000000, 0x100000000000000, 0x200000000000000, 0x400000000000000, 0x800000000000000, 0x1000000000000000, 0x2000000000000000, 0x4000000000000000, 0x8000000000000000};

    this -> board = indexes[index];
    return *this;
}

std::ostream& operator<<(std::ostream& os, const Bitboard& object) {
    os << object.getRawBinary().to_string();

    return os;
}


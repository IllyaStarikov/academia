//
//  bitboard.h
//  src
//
//  Created by Illya Starikov on 03/01/18.
//  Copyright 2018. Illya Starikov. All rights reserved.
//

#ifndef bitboard_h
#define bitboard_h

#include <inttypes.h>
#include <ostream>
#include <vector>
#include <bitset>

class Bitboard {
    uint64_t board;

public:

    // MARK: Constructors
    Bitboard();
    Bitboard(const uint64_t board);
    Bitboard(const Bitboard& board) = default;
    Bitboard(Bitboard&& board) = default;

    // MARK: Assignment
    Bitboard& operator=(const Bitboard& right);
    Bitboard& operator=(Bitboard&& right);

    // MARK: Operators
    bool operator==(const Bitboard& right) const noexcept;
    bool operator!=(const Bitboard& right) const noexcept;
    Bitboard operator>>(const int shift) const noexcept;
    Bitboard operator<<(const int shift) const noexcept;

    Bitboard operator~() const noexcept;
    Bitboard operator|(const Bitboard& right) const noexcept;
    Bitboard operator&(const Bitboard& right) const noexcept;
    Bitboard operator^(const Bitboard& right) const noexcept;

    Bitboard& operator|=(const Bitboard& right) noexcept;
    Bitboard& operator&=(const Bitboard& right) noexcept;
    Bitboard& operator^=(const Bitboard& right) noexcept;

    // MARK: Properties
    std::vector<int> toIndices();
    Bitboard& fromIndex(const int index);

    std::vector<Bitboard> seperated() const;
    int numberOfBits() const noexcept;

    std::bitset<64> getRawBinary() const noexcept { return std::bitset<64>(this -> board); }

    // MARK: Friend
    friend std::ostream& operator<<(std::ostream& os, const Bitboard& object);
};

#endif /* bitboard_h */


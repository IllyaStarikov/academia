
#include "functions.hpp"
#include "board.hpp"

#include <iostream>
#include <vector>
#include <tuple>


// Simply checks to see if the x, y are in bounds of the gameboard
bool inBounds(const int x, const int y) {
    return y < 3 && y >= 0 && x < 3 && x >= 0;
}

// Returns a tuple that defines the player coordinates
// The order is row, column
std::tuple<int, int> getPlayerMove(const char player, const Board board) {
	int x, y;
	
    std::cout << "\n" << player << "'s Move\n";
	
    do {
        std::cout << "Row: ";
        std::cin >> x;
            
        std::cout << "Column: ";
        std::cin >> y;
        
        // Because most people think 1st row, 2nd row, accept the input as so
        // but then decrement
        x -= 1;
        y -= 1;
        
        // Some C++ fun, normally board[x][y] would cause a segfault if the input
        // was bad, but since the first thing we do is check the input, 
        // we can safely assume that x and y will always be in range
        if (!inBounds(x, y)) {
            std::cout << "Invalid Input!\n\n";
        } else if (board[x][y] != blank) {
            std::cout << "Nice Try! ;)\n\n";
        }

        // Same reasoning as before why this works, because C++ short-circuits
        // or does a lazy evaluation, meaning if it's not in bounds, it'll 
        // never evaluate the board (because of the or, it only takes 1 being true)
        // if it is bounds, THEN check to see if it's a blank
    } while (!inBounds(x, y) || board[x][y] != blank);

    return std::make_tuple(x, y);
}


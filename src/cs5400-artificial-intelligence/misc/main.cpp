
#include "timer.h"
#include "move-time-calculator.h"

#include <iostream>
#include <thread>
using namespace std;
int main() {
    auto timer = Timer();
    auto moveTimeCalculator = MoveTimeCalculator();

    double timeRemaining = 900.0;
    auto moveNumber = 0;

    for (int i = 0; i < 60; i++) {
        timer.start();

        auto timeToMakeMove = moveTimeCalculator(moveNumber, timeRemaining);
        std::cout << "Time to make move: " << timeToMakeMove << "\n";

        while (timer.elapsed() < timeToMakeMove) {}

        timeRemaining -= timer.elapsed();
        moveNumber += 2;

        std::cout << "Move: " << moveNumber << "\n";
        std::cout << "Time remaining: " << timeRemaining << "\n\n";
    }
}

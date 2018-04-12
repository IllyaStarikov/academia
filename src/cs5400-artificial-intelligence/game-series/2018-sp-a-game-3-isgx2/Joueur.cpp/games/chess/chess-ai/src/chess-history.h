//
//  history-tracker.h
//  src
//
//  Created by Illya Starikov on 03/20/18.
//  Copyright 2018. Illya Starikov. All rights reserved.
//

#ifndef history_tracker_h
#define history_tracker_h

#include "state.h"
#include "constants.h"

#include <deque>

namespace ChessEngine {
    class PerceptSequence {
    private:
        std::deque<State> stateHistory;
        int _movesSenseCapture = 0, _movesSensePawnMovement = 0;

    public:
        void add(const State& state) {
            if (stateHistory.size() > MAX_HISTORY) {
                stateHistory.pop_front();
            }

            stateHistory.push_back(state);
        }

        void add(const Action& action) {
            _movesSenseCapture = action.wasCapture() ? _movesSenseCapture + 1 : 0;
            _movesSensePawnMovement = action.piece() == pawn ? _movesSensePawnMovement + 1 : 0;
        }

        const State operator[](const int index) const {
            return stateHistory[index];
        }

        int movesSincePawnMovement() const noexcept {
            return _movesSensePawnMovement;
        }

        int movesSinceCapture() const noexcept {
            return _movesSenseCapture;
        }

        int size() const noexcept {
            return stateHistory.size();
        }
    };
}

#endif /* history-tracker_h */


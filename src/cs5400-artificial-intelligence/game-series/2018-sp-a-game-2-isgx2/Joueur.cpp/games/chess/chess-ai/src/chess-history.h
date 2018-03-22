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


class PerceptSequence {
private:
    std::deque<State> stateHistory;
    int _movesSenseCapture = 0, _movesSensePawnMovement = 0;

public:
    void add(const State& state, const Action& action) {
        if (stateHistory.size() > MAX_HISTORY) {
            stateHistory.pop_front();
        }

        _movesSenseCapture = action.wasCaptured ? _movesSenseCapture + 1 : 0;
        _movesSensePawnMovement = action.piece == pawn ? _movesSensePawnMovement + 1 : 0;

        stateHistory.push_back(state);
    }

    const State operator[](const int index) const {
        return stateHistory[index];
    }

    int movesSensePawnMovement() const noexcept {
        return _movesSensePawnMovement;
    }

    int movesSenseCapture() const noexcept {
        return _movesSenseCapture;
    }

    int size() const noexcept {
        return stateHistory.size();
    }
};


#endif /* history-tracker_h */


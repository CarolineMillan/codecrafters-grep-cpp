#pragma once

#include <vector>
#include "state.h"

using std::vector;

class NFA {
public:
    // default constructor
    NFA() = default;
    // construct from values
    NFA(State* start, State* accept, vector<State> states);
    // default deconstructor
    ~NFA() = default;
private:
    // NFA internals (each transition is stored in a state)
    State* start_state = nullptr;
    vector<State> states;
    State* accept_state = nullptr;
};
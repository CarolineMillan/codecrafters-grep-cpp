#pragma once

#include <vector>
#include "token.h"
#include "state.h"

class NFA {
public:
    // default constructor
    NFA() = default;
    // constructor that builds from regex
    explicit NFA(const std::string &pattern);
    // default deconstructor
    ~NFA() = default;
private:
    // NFA internals (each transition is stored in a state)
    State* start_state = nullptr;
    std::vector<State> states;
    State* accept_state = nullptr;

    // misc
    std::vector<Token> tokens;

    // helper functions
    void build_from_regex(const std::string &pattern);
    void tokenize(const std::string &pattern);
    void to_postfix();
    void construct();
};
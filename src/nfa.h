#pragma once

#include <vector>
#include "token.h"
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

    // misc
    //std::vector<Token> tokens;
    //std::vector<Token> concat_tokens;
    //std::vector<Token> postfix_tokens;

    // helper functions
    //void build_from_regex(const std::string &pattern);
/*
    void tokenize(const std::string &pattern);
    void parse_escaped(const char ch);
    int parse_char_class(const std::string &pattern, int i);
    void add_concats();
    static bool should_concat(const Token& previous, const Token& current);

    void to_postfix();
    void construct();
*/
};
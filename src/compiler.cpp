//
// Created by Caroline Millan on 16/09/2025.
//

#include "compiler.h"
#include "nfa_fragment.h"

#include <stack>

using std::stack;

NFA Compiler::compile(vector<Token> tokens) {
    // Thompson's construction
    stack<NFAFragment> fragments;

    // final fragment on stack will be the start and accept states for the NFA
}

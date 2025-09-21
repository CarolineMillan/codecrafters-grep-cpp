//
// Created by Caroline Millan on 16/09/2025.
//

#include "compiler.h"
#include "nfa_fragment.h"

#include <stack>

using std::stack;

NFA Compiler::compile(vector<Token>& tokens) {
    // Thompson's construction
    stack<NFAFragment> fragments;
    vector<State> states;

    for (Token& token : tokens) {

        // add start state to states
        states.emplace_back(false);
        State* start = &states.back();

        // add accept state to states
        states.emplace_back(true);
        State* accept = &states.back();

        // rules go here
        switch (token.kind) {
        case Token::KIND::Literal: {
                // add transition to start state
                start->transitions.emplace_back(token.ch, accept);

                // add fragment to fragments stack
                fragments.push(NFAFragment(start, accept));

                break;
            }
        case Token::KIND::CharClass: {
                // add transition to start state for each char
                for (int c=0; c<256; c++) {
                    if (token.bitmap[c]) {
                        start->transitions.emplace_back(static_cast<unsigned char>(c), accept);
                    }
                }

                // add fragment to fragments stack
                fragments.push(NFAFragment(start, accept));

                break;
            }
        case Token::KIND::Concat: {
                // our to_postfix means that we're in postfix notation, so the operator comes AFTER both operands
                // so pop two fragments off the stack for our operands

                // TODO should there be an error if stack is empty?
                if (fragments.empty()) continue;

                NFAFragment b = fragments.top();
                fragments.pop();
                NFAFragment a = fragments.top();
                fragments.pop();

                // now we concat them to get a new fragment

                // we want an epsilon transition between a's accept state and b's start state
                a.accept->transitions.emplace_back(EPSILON, b.start);

                // add the new fragment to fragments
                fragments.push(NFAFragment(a.start, b.accept));

                break;
            }
        case Token::KIND::Alt: {
                // TODO should there be an error if stack is empty?
                if (fragments.empty()) continue;

                NFAFragment b = fragments.top();
                fragments.pop();
                NFAFragment a = fragments.top();
                fragments.pop();

                // add epsilon transitions from start to a.start and b.start
                start->transitions.emplace_back(EPSILON, a.start);
                start->transitions.emplace_back(EPSILON, b.start);

                // add epsilon transitions from a.accept and b.accept to accept
                a.accept->transitions.emplace_back(EPSILON, accept);
                b.accept->transitions.emplace_back(EPSILON, accept);

                // add fragment to fragments stack
                fragments.push(NFAFragment(start, accept));

                break;
            }
        case Token::KIND::Star: {
                break;
            }
        case Token::KIND::Question: {
                break;
            }
        case Token::KIND::Plus: {
                break;
            }
            break;
        default: {break;}
        }


    }

    // final fragment on stack will be the start and accept states for the NFA
    NFAFragment final;
    return {final.start, final.accept, states};
}

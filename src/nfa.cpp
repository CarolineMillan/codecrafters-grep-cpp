#include "nfa.h"

NFA::NFA(const std::string &pattern) {
    build_from_regex(pattern);
};

void NFA::build_from_regex(const std::string &pattern) {
    // builds an NFA from a regex pattern string
    tokenize(pattern);
    to_postfix();
    construct();
};

void NFA::tokenize(const std::string &pattern) {
    // tokenizes the pattern string

    // loop through pattern char by char and use a switch statement to match the token if you can, 
    // if you end up with a long string then it's a string literal i.e. break it up into char literals

};

void NFA::to_postfix() {
    // gets tokens into postfix format using shunting-yard algorithm
};

void NFA::construct() {
    // consrtuct the NFA from postfix token list using Thompson's NFA construction algorithm
};
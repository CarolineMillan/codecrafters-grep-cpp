#include "nfa.h"
#include "nfa_fragment.h"
#include "parser.h"

NFA::NFA(State* start, State* accept, vector<State> states_vec) {
    start_state = start;
    accept_state = accept;
    states = states_vec;
}
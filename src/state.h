#pragma once
#include "transition.h"

struct State {
    int id;
    Transition* transitions;
};
#pragma once

// Token is a POD-like type (Plain Old Data)
struct Token {
    // kind of token will be set via an enum for all possible tokens
    enum class KIND { Literal, Star};
    // set default to the literal character
    KIND kind = KIND::Literal;

    // payloads (some kinds need data, so this is where you store it)
    char ch = 0;

    bool is_operator() const {
        switch (kind) {
            case KIND::Star:
                return true;
            default:
                return false;
        }
    };
    bool is_operand() const {
        return !is_operator();
    };
};
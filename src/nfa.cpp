#include "nfa.h"
#include <stack>

NFA::NFA(const std::string &pattern) {
    build_from_regex(pattern);
};

void NFA::build_from_regex(const std::string &pattern) {
    // builds an NFA from a regex pattern string
    tokenize(pattern);
    add_concats();
    to_postfix();
    construct();
};

/* -------------------- TOKENIZE ---------------------- */

void NFA::tokenize(const std::string &pattern) {
    // tokenizes the pattern string
    
    // make sure we're starting with an empty list of tokens
    tokens.clear();

    // loop through the pattern
    for (int i = 0 ; i < pattern.size() ; i++) {
        char ch = pattern[i];

        if (ch == '\\') {
            // look at the next char that's being escaped, that will give you the token::KIND
            // maybe do this in a separate parse_escaped() method
            if (i+1 == pattern.size()-1) {
                // then it's the last char and it's not escaping anything, so just add the literal
                Token t;
                t.ch = ch;
                t.kind = Token::KIND::Literal;
                tokens.push_back(t);
                continue;
            }
            else {
                parse_escaped(pattern[i+1]);
                // need to skip the escaped character, so add one to i
                i++;
                continue;
            }
        }
        else if (ch == '[') {
            if (i+1 == pattern.size()-1) {
                // then it's the last char and it's not escaping anything, so just add the literal
                Token t;
                t.ch = ch;
                t.kind = Token::KIND::Literal;
                tokens.push_back(t);
                continue;
            }
            else {
                int new_i = parse_char_class(pattern, i+1);
                i = new_i;
            }
        }
        else {
            Token t;
            t.ch = ch;
            t.kind = Token::KIND::Literal;
            tokens.push_back(t);
        }
        // check for [abc] and [^abc]
        // also check for single character tokens (do this last)

    }
};

void NFA::parse_escaped(const char ch) {
    // want to match ch to any of the regex things we support, else just save the literal
    Token t;
    switch (ch) {
        case 'd':
            // matches all digits ascii 48-57
            t.kind = Token::KIND::CharClass;
            t.add_range_to_char_class('0','9');
        case 'w':
            // matches all alphanumeric chars
            t.kind = Token::KIND::CharClass;
            t.add_range_to_char_class('0','9');
            t.add_range_to_char_class('a','z');
            t.add_range_to_char_class('A','Z');
            t.add_to_char_class('_');
        default:
            t.ch = ch;
            t.kind = Token::KIND::Literal;
    }
    tokens.push_back(t);
};

int NFA::parse_char_class(const std::string &pattern, int i) {
    // create a token for char class [] or [^] starting at pattern[i]
    // two passes -- first one to find the ], second one if you don't find it and need to use a literal instead
    // for now take everything in the character class as a literal character, no escapes or anything
    Token t;
    bool closed = false;
    int original_index = i;
    
    // check for a negaetive character class
    if (pattern[i] == '^') {
        t.set_neg_char_class();
    }

    // loop through pattern until you find the ]
    for (i; i < pattern.size(); i++) {
        if (pattern[i] == ']') {
            closed = true;
            t.kind = Token::KIND::CharClass;
            tokens.push_back(t);
            break;
        }
        else {
            t.add_to_char_class(pattern[i]);
        }
    }
    if (!closed) {
        // second pass to add a literal instead
        for (int j = original_index; j < pattern.size(); j++) {
            Token t_lit;
            t_lit.kind = Token::KIND::Literal;
            t_lit.ch = pattern[i];
            tokens.push_back(t_lit);
        }
    }
    return i;
};

void NFA::add_concats() {
    // adds concats to tokens
    Token previous;
    bool first = true;
    for (Token current : tokens) {
        if (!first && should_concat(previous, current)) {
            Token t;
            t.kind = Token::KIND::Concat;
            concat_tokens.push_back(t);
        }
        concat_tokens.push_back(current);
        previous = current;
        first = false;
    }
};

bool NFA::should_concat(Token previous, Token current) {
    return (previous.is_operand() || previous.kind == Token::KIND::RParen || (previous.kind == Token::KIND::Star || previous.kind == Token::KIND::Plus || previous.kind == Token::KIND::Question) )
    && (current.is_operand() || current.kind == Token::KIND::LParen);
}

/* --------------------- TO POSTFIX -------------------- */

void NFA::to_postfix() {
    // gets tokens into postfix format using shunting-yard algorithm

    //make sure we have a fresh postfix_tokens
    postfix_tokens.clear();

    // make a stack to store the operands on
    std::stack<Token> st;

    for (Token token : concat_tokens) {
        if (token.is_operand()) {
            postfix_tokens.push_back(token);
            continue;
        }
        else if (token.is_operator()) {
            // check prescendence of operator
            // if the last thing on the stack is of prescendence greater than or equal to the current operator, pop it off before adding this operator to the stack
            //st.push(token);
            // TODO check this bit does associativity properly
            if (Token::get_presedence(st.top().kind) >= Token::get_presedence(token.kind)) {
                Token t = st.top();
                st.pop();
                postfix_tokens.push_back(t);
            }
        }
        else if (token.kind == Token::KIND::LParen) {
            st.push(token);
        }
        else if (token.kind == Token::KIND::RParen) {
            // pop everything until you reach an LParen, then discard both parens
            while (st.top().kind != Token::KIND::LParen) {
                Token el = st.top();
                st.pop();
                postfix_tokens.push_back(el);
            }
            if (st.top().kind != Token::KIND::LParen) {
                // TODO error message
            }
            st.pop();
        }
    }
};

/* --------------------- CONSTRUCT --------------------- */

void NFA::construct() {
    // consrtuct the NFA from postfix token list using Thompson's NFA construction algorithm
};
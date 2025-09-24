/* #include <iostream>
#include <string>

bool match_pattern(const std::string& input_line, const std::string& pattern) {

    // need to break up pattern into it's smallest regex components in order so you can match them
    // or read the article they recommended. It's strcture is like this project, only it uses recursion and an extra helper function
    if (pattern.length() == 1) {
        return input_line.find(pattern) != std::string::npos;
    }
    else if (pattern == std::string("\\d")) {
        // check for a digit
        for (char ch : input_line) {
            if (isdigit(ch)) {
                return true;
            }
        }
        return false;
    }
    else if (pattern == std::string("\\w")) {
        // check for a 'word', i.e. anything that contains at least one alphanumeric char or an underscore
        for (char ch : input_line) {
            if (isalnum(ch) || ch == '_') {
                return true;
            }
        }
        return false;
    }
    else if (pattern.front() == '[' && pattern[1] == '^' && pattern.back() == ']') {
        // negative character group check
        // check for any char • in pattern=[*] in input_string, return true if we don't find any
        for (char ch : pattern.substr(2, pattern.length()-3)) {
            if (input_line.find(ch) == std::string::npos) {
                return true;
            }
        }
        return false;
    }
    else if (pattern.front() == '[' && pattern.back() == ']') {
        // positive character group check
        // check for any char • in pattern=[*] in input_string
        for (char ch : pattern.substr(1, pattern.length()-2)) {
            if (input_line.find(ch) != std::string::npos) {
                return true;
            }
        }
        return false;
    }
    else {
        throw std::runtime_error("Unhandled pattern " + pattern);
    }

}

int main(int argc, char* argv[]) {
    // Flush after every std::cout / std::cerr
    std::cout << std::unitbuf;
    std::cerr << std::unitbuf;

    // You can use print statements as follows for debugging, they'll be visible when running tests.
    std::cerr << "Logs from your program will appear here" << std::endl;

    if (argc != 3) {
        std::cerr << "Expected two arguments" << std::endl;
        return 1;
    }

    std::string flag = argv[1];
    std::string pattern = argv[2];

    if (flag != "-E") {
        std::cerr << "Expected first argument to be '-E'" << std::endl;
        return 1;
    }

    // Uncomment this block to pass the first stage
   
    std::string input_line;
    std::getline(std::cin, input_line);
   
    try {
        if (match_pattern(input_line, pattern)) {
            return 0;
        } else {
            return 1;
        }
    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
}
*/

#include <iostream>
#include <string>

#include "grape/compiler.h"
#include "grape/nfa.h"
#include "grape/parser.h"
#include "grape/token.h"

//throw std::runtime_error("Unhandled pattern " + pattern);

int main(int argc, char* argv[]) {
    // Flush after every std::cout / std::cerr
    std::cout << std::unitbuf;
    std::cerr << std::unitbuf;

    // You can use print statements as follows for debugging, they'll be visible when running tests.
    // std::cerr << "Logs from your program will appear here" << std::endl;

    if (argc != 3) {
        std::cerr << "Expected two arguments" << std::endl;
        return 1;
    }

    std::string flag = argv[1];
    std::string pattern = argv[2];

    // do i really need this? I don't think I need a flag
    // what I do need is to figure out how to make this a cli tool that you can use by calling grape
    if (flag != "-E") {
        std::cerr << "Expected first argument to be '-E'" << std::endl;
        return 1;
    }

    std::string input_line;
    std::getline(std::cin, input_line);

    try {
        // create nfa here
        // don't need a parser and a compiler, it's a waste ju have one engie to create the nfa
        Parser parser;
        Compiler compiler;
        vector<Token> tokens = parser.parse(pattern);
        NFA nfa = compiler.compile(tokens);

        if (nfa.run(input_line)) {
            std::cout << "true" << std::endl;
            return 0;
        } else {
            std::cout << "false" << std::endl;
            return 1;
        }
    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
}

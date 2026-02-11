#pragma once

#include <vector>
#include <string>

namespace lexer {
    enum TokenType {
        NUMBER,
        IDENTIFIER,
        PLUS,
        MINUS,
        MULTIPLY,
        DIVIDE,
        LPAREN,
        RPAREN,
        EQUAL
    };

    struct Token {
        TokenType type;
        std::string value;
    };

    std::vector<Token> tokenize(const std::string& input);
    std::string get_tokttype(TokenType type);
}

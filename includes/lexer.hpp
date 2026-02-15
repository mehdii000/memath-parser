#pragma once

#include <string_view>
#include <vector>
#include <cctype> // for isdigit, isalpha

enum class TokenType {
    NUMBER,   // 1, 3.14
    LITERAL, // x, y, sin, pi
    PLUS, MINUS, STAR, SLASH, PERCENT,
    LPAREN, RPAREN, EQUAL,
};

struct Token {
    TokenType type;
    std::string_view value;
};

struct Lexer {
    std::string_view source;
    size_t start = 0;
    size_t current = 0;

    Lexer(std::string_view source) : source(source) {};

    // The main engine
    std::vector<Token> tokenize();

private:
    // Core Navigation
    bool isAtEnd() const { return current >= source.length(); }
    char advance() { return source[current++]; }
    char peek() const { return isAtEnd() ? '\0' : source[current]; }
};

#pragma once

#include <vector>
#include <memory>
#include <string>
#include <unordered_map>
#include <cstdint> // Preferred over <stdint.h> in C++

namespace lexer {

    enum class TokenType {
        NUMBER,
        IDENTIFIER,
        FUNCTION,
        PLUS,
        MINUS,
        MULTIPLY,
        DIVIDE,
        LPAREN,
        RPAREN,
        EQUAL
    };

    // Higher value = Higher precedence (processed first)
    const std::unordered_map<TokenType, uint8_t> operationPriority =
    {
        {TokenType::MULTIPLY, 2},
        {TokenType::DIVIDE,   2},
        {TokenType::PLUS,     1},
        {TokenType::MINUS,    1}
    };

    struct Token {
        TokenType type;
        std::string value;
        std::vector<std::unique_ptr<Token>> sub_tokens = {};
    };

    std::vector<Token> tokenize(const std::string& input);
    void preprocess(std::vector<Token>& tokens);
    std::string get_tokttype(TokenType type);
}

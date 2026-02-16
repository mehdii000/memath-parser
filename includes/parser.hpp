#pragma once

#include <string_view>
#include <vector>
#include <cctype> // for isdigit, isalpha
#include <memory>
#include "lexer.hpp"

enum class NodeType {
    BINARY_OP,
    UNARY_OP,
    LITERAL,
    NUMBER
};

struct Node {
    NodeType type;
    std::string_view value;
    std::vector<std::unique_ptr<Node>> children;

    // Helper to make adding children easier
    void addChild(std::unique_ptr<Node> child) {
        children.push_back(std::move(child));
    }
};

struct Parser {
    Parser(const std::vector<Token>& tokens) : tokens(tokens) {}
    
    // Main entry point
    std::unique_ptr<Node> parse();

private:
    const std::vector<Token>& tokens;
    size_t current = 0;

    // Math Precedence Levels
    std::unique_ptr<Node> expression();   // Equality (=)
    std::unique_ptr<Node> term();         // Addition and Subtraction (+, -)
    std::unique_ptr<Node> factor();       // Multiplication and Division (*, /)
    std::unique_ptr<Node> primary();      // Numbers, Variables, and Parentheses

    // Helper: Checks if the current token matches any of the given types
    bool match(std::initializer_list<TokenType> types) {
        for (auto type : types) {
            if (check(type)) {
                advance();
                return true;
            }
        }
        return false;
    }

    bool check(TokenType type) const {
        if (isAtEnd()) return false;
        return peek().type == type;
    }

    // Existing helpers...
    const Token& peek() const { return tokens[current]; }
    const Token& previous() const { return tokens[current - 1]; }
    bool isAtEnd() const { return current >= tokens.size(); }
    const Token& advance() {
        if (!isAtEnd()) return tokens[current++];
    }
};

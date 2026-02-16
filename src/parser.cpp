#include "parser.hpp"
#include <stdexcept>

// Entry point: Handles the lowest precedence (Equality)
std::unique_ptr<Node> Parser::parse() {
    return expression();
}

// expression -> term ( "=" term )*
std::unique_ptr<Node> Parser::expression() {
    auto node = term();

    while (match({TokenType::EQUAL})) {
        Token op = previous();
        auto right = term();

        auto binaryNode = std::make_unique<Node>();
        binaryNode->type = NodeType::BINARY_OP;
        binaryNode->value = op.value;
        binaryNode->children.push_back(std::move(node));
        binaryNode->children.push_back(std::move(right));
        node = std::move(binaryNode);
    }
    return node;
}

// term -> factor ( ( "+" | "-" ) factor )*
std::unique_ptr<Node> Parser::term() {
    auto node = factor();

    while (match({TokenType::PLUS, TokenType::MINUS})) {
        Token op = previous();
        auto right = factor();

        auto binaryNode = std::make_unique<Node>();
        binaryNode->type = NodeType::BINARY_OP;
        binaryNode->value = op.value;
        binaryNode->children.push_back(std::move(node));
        binaryNode->children.push_back(std::move(right));
        node = std::move(binaryNode);
    }
    return node;
}

// factor -> primary ( ( "*" | "/" ) primary )*
std::unique_ptr<Node> Parser::factor() {
    auto node = primary();

    while (match({TokenType::STAR, TokenType::SLASH})) {
        Token op = previous();
        auto right = primary();

        auto binaryNode = std::make_unique<Node>();
        binaryNode->type = NodeType::BINARY_OP;
        binaryNode->value = op.value;
        binaryNode->children.push_back(std::move(node));
        binaryNode->children.push_back(std::move(right));
        node = std::move(binaryNode);
    }
    return node;
}

// primary -> NUMBER | LITERAL | "(" expression ")"
std::unique_ptr<Node> Parser::primary() {
    if (match({TokenType::NUMBER})) {
        auto node = std::make_unique<Node>();
        node->type = NodeType::NUMBER;
        node->value = previous().value;
        return node;
    }

    if (match({TokenType::LITERAL})) {
        auto node = std::make_unique<Node>();
        node->type = NodeType::LITERAL;
        node->value = previous().value;
        return node;
    }

    if (match({TokenType::LPAREN})) {
        auto node = expression();
        if (!match({TokenType::RPAREN})) {
            throw std::runtime_error("Expected ')' after expression.");
        }
        return node;
    }

    throw std::runtime_error("Unexpected token in expression.");
}

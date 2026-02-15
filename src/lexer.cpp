#include "lexer.hpp"
#include <vector>
#include <cctype>

std::vector<Token> Lexer::tokenize() {
    std::vector<Token> tokens;

    while (!isAtEnd()) {
        start = current; // Reset start to the beginning of the next token
        char c = peek();

        switch (c) {
            // Single character tokens
            case '(': tokens.push_back({TokenType::LPAREN, source.substr(start, 1)}); current++; break;
            case ')': tokens.push_back({TokenType::RPAREN, source.substr(start, 1)}); current++; break;
            case '+': tokens.push_back({TokenType::PLUS,   source.substr(start, 1)}); current++; break;
            case '-': tokens.push_back({TokenType::MINUS,  source.substr(start, 1)}); current++; break;
            case '*': tokens.push_back({TokenType::STAR,   source.substr(start, 1)}); current++; break;
            case '/': tokens.push_back({TokenType::SLASH,  source.substr(start, 1)}); current++; break;
            case '=': tokens.push_back({TokenType::EQUAL,  source.substr(start, 1)}); current++; break;
            
            // Skip whitespace
            case ' ':
            case '\r':
            case '\t':
            case '\n':
                current++;
                break;

            default:
                if (std::isdigit(c)) {
                    // Handle numbers (including decimals for math)
                    while (!isAtEnd() && std::isdigit(peek())) {
                        current++;
                    }
                    // Optional: handle decimal point
                    if (peek() == '.') {
                        current++;
                        while (!isAtEnd() && std::isdigit(peek())) current++;
                    }
                    tokens.push_back({TokenType::NUMBER, source.substr(start, current - start)});
                } 
                else if (std::isalpha(c)) {
                    // Handle variables/functions (x, y, sin, etc)
                    while (!isAtEnd() && std::isalnum(peek())) {
                        current++;
                    }
                    tokens.push_back({TokenType::LITERAL, source.substr(start, current - start)});
                }
                else {
                    // Ignore or handle unknown characters
                    current++; 
                }
                break;
        }
    }
    
    return tokens;
}

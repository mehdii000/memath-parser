#include "lexer.hpp"

namespace lexer {

    std::string get_tokttype(TokenType type) {
        switch (type) {
            case TokenType::NUMBER:     return "NUMBER";
            case TokenType::IDENTIFIER: return "IDENTIFIER";
            case TokenType::PLUS:       return "PLUS";
            case TokenType::MINUS:      return "MINUS";
            case TokenType::MULTIPLY:   return "MULTIPLY";
            case TokenType::DIVIDE:     return "DIVIDE";
            case TokenType::LPAREN:     return "LPAREN";
            case TokenType::RPAREN:     return "RPAREN";
            case TokenType::EQUAL:      return "EQUAL";
            default:                    return "UNKNOWN";
        }
    }

    std::vector<Token> tokenize(const std::string& input) {
        std::vector<Token> tokens;
        
        int i = 0;
        while (i < input.length()) {
            char current = input[i];

            if (std::isspace(current)) {
                i++;
                continue;
            }

            if (std::isdigit(current)) {
                std::string value;
                while (i < input.length() && (std::isdigit(input[i]) || input[i] == '.')) {
                    value += input[i++];
                }
                tokens.push_back({ TokenType::NUMBER, value });
                continue;
            }

            if (std::isalpha(current)) {
                std::string value;
                while (i < input.length() && std::isalnum(input[i])) {
                    value += input[i++];
                }
                tokens.push_back({ TokenType::IDENTIFIER, value });
                continue;
            }

            switch (current) {
                case '+': tokens.push_back({ TokenType::PLUS, "+" });       break;
                case '-': tokens.push_back({ TokenType::MINUS, "-" });      break;
                case '*': tokens.push_back({ TokenType::MULTIPLY, "*" });   break;
                case '/': tokens.push_back({ TokenType::DIVIDE, "/" });     break;
                case '(': tokens.push_back({ TokenType::LPAREN, "(" });     break;
                case ')': tokens.push_back({ TokenType::RPAREN, ")" });     break;
                case '=': tokens.push_back({ TokenType::EQUAL, "="});       break;
                default: break; 
            }
            i++;
        }

        return tokens;
    }

}

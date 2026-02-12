#include "lexer.hpp"

namespace lexer {

    namespace {
        int getPrecedence(TokenType type) {
            auto it = operationPriority.find(type);
            return (it != operationPriority.end()) ? it->second : 2;
        }
        
        bool isArithOp(TokenType type) {
            return type == TokenType::DIVIDE || type == TokenType::MULTIPLY || type == TokenType::PLUS || type == TokenType::MINUS;
        }

        size_t parseLeft(const std::vector<Token>& tokens, size_t index) {
            // If it's not a parenthesis, the boundary is just this token
            if (tokens.at(index).type != TokenType::RPAREN) return index;

            int balance = 0;
            for (int i = static_cast<int>(index); i >= 0; --i) {
                if (tokens.at(i).type == TokenType::RPAREN) balance++;
                if (tokens.at(i).type == TokenType::LPAREN) balance--;
                if (balance == 0) return static_cast<size_t>(i);
            }
            return 0;
        }

        size_t parseRight(const std::vector<Token>& tokens, size_t index) {
            if (tokens.at(index).type != TokenType::LPAREN) return index;

            int balance = 0;
            for (size_t i = index; i < tokens.size(); ++i) {
                if (tokens.at(i).type == TokenType::LPAREN) balance++;
                if (tokens.at(i).type == TokenType::RPAREN) balance--;
                if (balance == 0) return i;
            }
            return tokens.size() - 1;
        }

    }

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
        while (i < static_cast<int>(input.length())) {
            char current = input[i];

            if (std::isspace(current)) {
                i++;
                continue;
            }

            if (std::isdigit(current)) {
                std::string value;
                while (i < static_cast<int>(input.length()) && (std::isdigit(input[i]) || input[i] == '.')) {
                    value += input[i++];
                }
                tokens.push_back({ TokenType::NUMBER, value });
                continue;
            }

            if (std::isalpha(current)) {
                std::string value;
                while (i < static_cast<int>(input.length()) && std::isalnum(input[i])) {
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

    void preprocess(std::vector<Token>& tokens) {
        for (int prec = 2; prec >= 1; --prec) {
            for (size_t i = 0; i < tokens.size(); ++i) {
                if (isArithOp(tokens[i].type) && getPrecedence(tokens[i].type) == prec) {
                    
                    size_t lb = parseLeft(tokens, i - 1);
                    size_t rb = parseRight(tokens, i + 1);

                    // OPTIMIZATION: Check if this range is already wrapped in parens
                    if (lb > 0 && rb < tokens.size() - 1) {
                        if (tokens[lb-1].type == TokenType::LPAREN && 
                            tokens[rb+1].type == TokenType::RPAREN) {
                            // skipping
                            continue; 
                        }
                    }

                    tokens.insert(tokens.begin() + rb + 1, { TokenType::RPAREN, ")" });
                    tokens.insert(tokens.begin() + lb, { TokenType::LPAREN, "(" });

                    i += 2; 
                }
            }
        }
    }

}

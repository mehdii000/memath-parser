#include <print>
#include <string>
#include <string_view>
#include <numeric>
#include <vector>
#include "fatal.hpp"
#include "lexer.hpp"
#include "parser.hpp"
#include <iostream>
#include <memory>

void printRecursively(const Node* node, int depth = 0) {
    if (!node) return;

    // 1. Create indentation (2 spaces per depth level)
    for (int i = 0; i < depth; ++i) {
        std::cout << "  ";
    }

    // 2. Print the current node's info
    std::string typeStr;
    switch (node->type) {
        case NodeType::BINARY_OP: typeStr = "[Binary Op]"; break;
        case NodeType::UNARY_OP:  typeStr = "[Unary Op]";  break;
        case NodeType::LITERAL:   typeStr = "[Variable]";  break;
        case NodeType::NUMBER:    typeStr = "[Number]";    break;
    }

    std::cout << typeStr << ": " << node->value << "\n";

    // 3. Recursively print children
    for (const auto& child : node->children) {
        printRecursively(child.get(), depth + 1);
    }
}

int main(int argc, char const *argv[]) {
    if (argc < 2) fatal::exit("Invalid argument <input>. memath \"<input>\"");
    std::string input{ argv[1] };

    Lexer lexer = Lexer(input);
    std::vector<Token> tokens = lexer.tokenize();

    Parser parser = Parser(tokens);
    std::unique_ptr<Node> astRoot = parser.parse();

    printRecursively(astRoot.get());

    return 0;
}

#include <print>
#include <string>
#include <string_view>
#include <numeric>
#include <vector>
#include "fatal.hpp"
#include "lexer.hpp"

int main(int argc, char const *argv[]) {
    if (argc < 2) fatal::exit("Invalid argument <input>. memath \"<input>\"");
    std::string input{ argv[1] };

    std::vector<lexer::Token> tokens { lexer::tokenize(input) };
    lexer::preprocess(tokens); // by ref
    std::print("Raw: ");    
    for (auto& token : tokens) {
        std::print("{}", token.value);
    }
    std::print("\n");

    return 0;
}

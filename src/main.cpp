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

    Lexer lexer = Lexer(input);
    std::vector<Token> tokens = lexer.tokenize();

    for (auto& token : tokens) {
        std::print("{} ", token.value);
    }
    std::print("\n");

    return 0;
}

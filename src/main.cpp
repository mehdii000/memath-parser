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

    std::println("Lexing: {}", input);
    std::vector<lexer::Token> tokens { lexer::tokenize(input) };
    
    for (auto& token : tokens) {
        std::println("{}->{}", lexer::get_tokttype(token.type), token.value);
    }

    return 0;
}

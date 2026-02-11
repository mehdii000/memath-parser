#pragma once
#include <print>
#include <cstdlib>
#include <string_view>

namespace fatal {
    inline void err(std::string_view message) {
        std::println(stderr, "[ERR]: {}", message);
    }

    inline void exit(std::string_view message) {
        std::println(stderr, "[FATAL]: {}", message);
        std::exit(EXIT_FAILURE);
    }
}

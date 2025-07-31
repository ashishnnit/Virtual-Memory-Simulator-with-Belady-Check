#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <string>
#include <sstream>

namespace Color {
    constexpr const char* RED    = "";  // Color stripped
    constexpr const char* GREEN  = "";
    constexpr const char* YELLOW = "";
    constexpr const char* BLUE   = "";
    constexpr const char* RESET  = "";
}

// Replaces emojis with simple text like "Fault", "Hit", etc.
inline std::vector<int> parsePages(const std::string& line) {
    std::istringstream iss(line);
    std::vector<int> pages;
    int x;
    while (iss >> x) pages.push_back(x);
    return pages;
}

#endif // UTILS_H

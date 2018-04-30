#ifndef CS222_UTILITY_H
#define CS222_UTILITY_H

#include <string>

namespace cs222 {
    std::string toUpper(const std::string& str);
    bool isOperation(const std::string& str);
    bool isDirective(const std::string& str);
}

#endif

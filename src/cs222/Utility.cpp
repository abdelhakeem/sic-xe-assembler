#include <algorithm>
#include <cs222/OpTable.h>
#include <cs222/Utility.h>

namespace cs222 {
    std::string toUpper(const std::string& str)
    {
        std::string upper(str);
        std::transform(str.begin(), str.end(), upper.begin(), toupper);
        return upper;
    }

    bool isOperation(const std::string& str)
    {
        return OpTable.find(toUpper(str)) != OpTable.end();
    }

    bool isDirective(const std::string& str)
    {
        return std::binary_search(
                DIRECTIVES.begin(),
                DIRECTIVES.end(),
                toUpper(str));
    }
}

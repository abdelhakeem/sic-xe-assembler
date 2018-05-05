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

    template<class T, size_t size>
    bool arrayContains(const T (&arr)[size], const T& key)
    {
        return std::find(
                std::begin(arr),
                std::end(arr),
                key) != std::end(arr);
    }

    bool isOperation(const std::string& str)
    {
        return OpTable.find(toUpper(str)) != OpTable.end();
    }

    bool isDirective(const std::string& str)
    {
        return arrayContains(DIRECTIVES, toUpper(str));
    }

    bool isRegister(const std::string& str)
    {
        return REGISTERS.find(toUpper(str)) != REGISTERS.end();
    }
}

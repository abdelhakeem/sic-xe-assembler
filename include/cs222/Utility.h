#ifndef CS222_UTILITY_H
#define CS222_UTILITY_H

#include <string>
#include <unordered_map>

namespace cs222 {
    // Directives
    constexpr auto DIR_BASE   = "BASE";
    constexpr auto DIR_BYTE   = "BYTE";
    constexpr auto DIR_END    = "END";
    constexpr auto DIR_EQU    = "EQU";
    constexpr auto DIR_LTORG  = "LTORG";
    constexpr auto DIR_NOBASE = "NOBASE";
    constexpr auto DIR_ORG    = "ORG";
    constexpr auto DIR_RESB   = "RESB";
    constexpr auto DIR_RESW   = "RESW";
    constexpr auto DIR_START  = "START";
    constexpr auto DIR_WORD   = "WORD";

    const std::string DIRECTIVES[] {
        DIR_BASE,
        DIR_BYTE,
        DIR_END,
        DIR_EQU,
        DIR_LTORG,
        DIR_NOBASE,
        DIR_ORG,
        DIR_RESB,
        DIR_RESW,
        DIR_START,
        DIR_WORD
    };

    // Registers
    constexpr auto REG_A  = "A";
    constexpr auto REG_X  = "X";
    constexpr auto REG_L  = "L";
    constexpr auto REG_B  = "B";
    constexpr auto REG_S  = "S";
    constexpr auto REG_T  = "T";
    constexpr auto REG_F  = "F";
    constexpr auto REG_PC = "PC";
    constexpr auto REG_SW = "SW";

    const std::unordered_map<std::string, char> REGISTERS {
        { REG_A,  0 },
        { REG_X,  1 },
        { REG_L,  2 },
        { REG_B,  3 },
        { REG_S,  4 },
        { REG_T,  5 },
        { REG_F,  6 },
        { REG_PC, 8 },
        { REG_SW, 9 }
    };

    std::string toUpper(const std::string& str);
    template<class T, size_t size>
    bool arrayContains(const T (&arr)[size], const T& key);
    bool isOperation(const std::string& str);
    bool isDirective(const std::string& str);
    bool isRegister(const std::string& str);
}

#endif

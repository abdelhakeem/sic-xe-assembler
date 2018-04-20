#ifndef CS222_DIRECTIVES_H
#define CS222_DIRECTIVES_H

#include <unordered_map>

namespace cs222 {
    using std::string;
    using std::unordered_map;

    enum Directive {
        DIR_START,
        DIR_END,
        DIR_BYTE,
        DIR_WORD,
        DIR_RESB,
        DIR_RESW
    };

    const unordered_map<Directive, string> DIR_MNEMONIC {
        {DIR_START, "START"},
        {DIR_END,   "END"},
        {DIR_BYTE,  "BYTE"},
        {DIR_WORD,  "WORD"},
        {DIR_RESB,  "RESB"},
        {DIR_RESW,  "RESW"},
    };
}

#endif

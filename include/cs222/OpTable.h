#ifndef CS222_OPTABLE_H
#define CS222_OPTABLE_H

#include <unordered_map>
#include "Operation.h"

namespace cs222 {
    using std::unordered_map;

    // TODO add remaining operations

    constexpr auto OP_ADD = "ADD";
    constexpr auto OP_ADDF = "ADDF";
    constexpr auto OP_ADDR = "ADDR";
    constexpr auto OP_AND = "AND";
    constexpr auto OP_CLEAR = "CLEAR";
    constexpr auto OP_COMP = "COMP";
    constexpr auto OP_COMPF = "COMPF";
    constexpr auto OP_COMPR = "COMPR";

    const unordered_map<string, Operation> OPTAB {
        {OP_ADD,    Operation(OP_ADD,   0x18, Operation::FORMAT_3_4)},
        {OP_ADDF,   Operation(OP_ADDF,  0x58, Operation::FORMAT_3_4)},
        {OP_ADDR,   Operation(OP_ADDR,  0x90, Operation::FORMAT_2)},
        {OP_AND,    Operation(OP_AND,   0x40, Operation::FORMAT_3_4)},
        {OP_CLEAR,  Operation(OP_CLEAR, 0xB4, Operation::FORMAT_2)},
        {OP_COMP,   Operation(OP_COMP,  0x28, Operation::FORMAT_3_4)},
        {OP_COMPF,  Operation(OP_COMPF, 0x88, Operation::FORMAT_3_4)},
        {OP_COMPR,  Operation(OP_COMPF, 0xA0, Operation::FORMAT_2)},
    };
}

#endif

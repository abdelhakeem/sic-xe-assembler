#ifndef CS222_OPTABLE_H
#define CS222_OPTABLE_H

#include <unordered_map>
#include "Instruction.h"

namespace cs222 {
    using std::unordered_map;

    // TODO add remaining instructions

    constexpr auto OP_ADD = "ADD";
    constexpr auto OP_ADDF = "ADDF";
    constexpr auto OP_ADDR = "ADDR";
    constexpr auto OP_AND = "AND";
    constexpr auto OP_CLEAR = "CLEAR";
    constexpr auto OP_COMP = "COMP";
    constexpr auto OP_COMPF = "COMPF";
    constexpr auto OP_COMPR = "COMPR";

    const unordered_map<string, Instruction> OPTAB {
        {OP_ADD,    Instruction(OP_ADD,   0x18, Instruction::FORMAT_3_4)},
        {OP_ADDF,   Instruction(OP_ADDF,  0x58, Instruction::FORMAT_3_4)},
        {OP_ADDR,   Instruction(OP_ADDR,  0x90, Instruction::FORMAT_2)},
        {OP_AND,    Instruction(OP_AND,   0x40, Instruction::FORMAT_3_4)},
        {OP_CLEAR,  Instruction(OP_CLEAR, 0xB4, Instruction::FORMAT_2)},
        {OP_COMP,   Instruction(OP_COMP,  0x28, Instruction::FORMAT_3_4)},
        {OP_COMPF,  Instruction(OP_COMPF, 0x88, Instruction::FORMAT_3_4)},
        {OP_COMPR,  Instruction(OP_COMPF, 0xA0, Instruction::FORMAT_2)},
    };
}

#endif

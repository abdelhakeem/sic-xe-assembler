#ifndef CS222_OPTABLE_H
#define CS222_OPTABLE_H

#include <vector>
#include <cs222/Operation.h>

namespace cs222 {
    constexpr auto OP_ADD       =       "ADD";
    constexpr auto OP_ADDF      =       "ADDF";
    constexpr auto OP_ADDR      =       "ADDR";
    constexpr auto OP_AND       =       "AND";
    constexpr auto OP_CLEAR     =       "CLEAR";
    constexpr auto OP_COMP      =       "COMP";
    constexpr auto OP_COMPF     =       "COMPF";
    constexpr auto OP_COMPR     =       "COMPR";
    constexpr auto OP_DIV       =       "DIV";
    constexpr auto OP_DIVF      =       "DIVF";
    constexpr auto OP_DIVR      =       "DIVR";
    constexpr auto OP_FIX       =       "FIX";
    constexpr auto OP_FLOAT     =       "FLOAT";
    constexpr auto OP_HIO       =       "HIO";
    constexpr auto OP_J         =       "J";
    constexpr auto OP_JEQ       =       "JEQ";
    constexpr auto OP_JGT       =       "JGT";
    constexpr auto OP_JLT       =       "JLT";
    constexpr auto OP_JSUB      =       "JSUB";
    constexpr auto OP_LDA       =       "LDA";
    constexpr auto OP_LDB       =       "LDB";
    constexpr auto OP_LDCH      =       "LDCH";
    constexpr auto OP_LDF       =       "LDF";
    constexpr auto OP_LDL       =       "LDL";
    constexpr auto OP_LDS       =       "LDS";
    constexpr auto OP_LDT       =       "LDT";
    constexpr auto OP_LDX       =       "LDX";
    constexpr auto OP_LPS       =       "LPS";
    constexpr auto OP_MUL       =       "MUL";
    constexpr auto OP_MULF      =       "MULF";
    constexpr auto OP_MULR      =       "MULR";
    constexpr auto OP_NORM      =       "NORM";
    constexpr auto OP_OR        =       "OR";
    constexpr auto OP_RD        =       "RD";
    constexpr auto OP_RMO       =       "RMO";
    constexpr auto OP_RSUB      =       "RSUB";
    constexpr auto OP_SHIFTL    =       "SHIFTL";
    constexpr auto OP_SHIFTR    =       "SHIFTR";
    constexpr auto OP_SIO       =       "SIO";
    constexpr auto OP_SSK       =       "SSK";
    constexpr auto OP_STA       =       "STA";
    constexpr auto OP_STB       =       "STB";
    constexpr auto OP_STCH      =       "STCH";
    constexpr auto OP_STF       =       "STF";
    constexpr auto OP_STI       =       "STI";
    constexpr auto OP_STL       =       "STL";
    constexpr auto OP_STS       =       "STS";
    constexpr auto OP_STSW      =       "STSW";
    constexpr auto OP_STT       =       "STT";
    constexpr auto OP_STX       =       "STX";
    constexpr auto OP_SUB       =       "SUB";
    constexpr auto OP_SUBF      =       "SUBF";
    constexpr auto OP_SUBR      =       "SUBR";
    constexpr auto OP_SVC       =       "SVC";
    constexpr auto OP_TD        =       "TD";
    constexpr auto OP_TIO       =       "TIO";
    constexpr auto OP_TIX       =       "TIX";
    constexpr auto OP_TIXR      =       "TIXR";
    constexpr auto OP_WD        =       "WD";

    const std::unordered_map<std::string, Operation> OpTable {
        {OP_ADD,    Operation(OP_ADD,   0x18, Instruction::FORMAT_3_4)},
        {OP_ADDF,   Operation(OP_ADDF,  0x58, Instruction::FORMAT_3_4)},
        {OP_ADDR,   Operation(OP_ADDR,  0x90, Instruction::FORMAT_2)},
        {OP_AND,    Operation(OP_AND,   0x40, Instruction::FORMAT_3_4)},
        {OP_CLEAR,  Operation(OP_CLEAR, 0xB4, Instruction::FORMAT_2)},
        {OP_COMP,   Operation(OP_COMP,  0x28, Instruction::FORMAT_3_4)},
        {OP_COMPF,  Operation(OP_COMPF, 0x88, Instruction::FORMAT_3_4)},
        {OP_COMPR,  Operation(OP_COMPR, 0xA0, Instruction::FORMAT_2)},
        {OP_DIV,    Operation(OP_DIV,   0x24, Instruction::FORMAT_3_4)},
        {OP_DIVF,   Operation(OP_DIVF,  0x64, Instruction::FORMAT_3_4)},
        {OP_DIVR,   Operation(OP_DIVR,  0x9C, Instruction::FORMAT_2)},
        {OP_FIX,    Operation(OP_FIX,   0xC4, Instruction::FORMAT_1)},
        {OP_FLOAT,  Operation(OP_FLOAT, 0xC0, Instruction::FORMAT_1)},
        {OP_HIO,    Operation(OP_HIO,   0xF4, Instruction::FORMAT_1)},
        {OP_J,      Operation(OP_J,     0x3C, Instruction::FORMAT_3_4)},
        {OP_JEQ,    Operation(OP_JEQ,   0x30, Instruction::FORMAT_3_4)},
        {OP_JGT,    Operation(OP_JGT,   0x34, Instruction::FORMAT_3_4)},
        {OP_JLT,    Operation(OP_JLT,   0x38, Instruction::FORMAT_3_4)},
        {OP_JSUB,   Operation(OP_JSUB,  0x48, Instruction::FORMAT_3_4)},
        {OP_LDA,    Operation(OP_LDA,   0x00, Instruction::FORMAT_3_4)},
        {OP_LDB,    Operation(OP_LDB,   0x68, Instruction::FORMAT_3_4)},
        {OP_LDCH,   Operation(OP_LDCH,  0x50, Instruction::FORMAT_3_4)},
        {OP_LDF,    Operation(OP_LDF,   0x70, Instruction::FORMAT_3_4)},
        {OP_LDL,    Operation(OP_LDL,   0x08, Instruction::FORMAT_3_4)},
        {OP_LDS,    Operation(OP_LDS,   0x6C, Instruction::FORMAT_3_4)},
        {OP_LDT,    Operation(OP_LDT,   0x74, Instruction::FORMAT_3_4)},
        {OP_LDX,    Operation(OP_LDX,   0x04, Instruction::FORMAT_3_4)},
        {OP_LPS,    Operation(OP_LPS,   0xD0, Instruction::FORMAT_3_4)},
        {OP_MUL,    Operation(OP_MUL,   0x20, Instruction::FORMAT_3_4)},
        {OP_MULF,   Operation(OP_MULF,  0x60, Instruction::FORMAT_3_4)},
        {OP_MULR,   Operation(OP_MULR,  0x98, Instruction::FORMAT_2)},
        {OP_NORM,   Operation(OP_NORM,  0xC8, Instruction::FORMAT_1)},
        {OP_OR,     Operation(OP_OR,    0x44, Instruction::FORMAT_3_4)},
        {OP_RD,     Operation(OP_RD,    0xD8, Instruction::FORMAT_3_4)},
        {OP_RMO,    Operation(OP_RMO,   0xAC, Instruction::FORMAT_2)},
        {OP_RSUB,   Operation(OP_RSUB,  0x4C, Instruction::FORMAT_3_4)},
        {OP_SHIFTL, Operation(OP_SHIFTL,0xA4, Instruction::FORMAT_2)},
        {OP_SHIFTR, Operation(OP_SHIFTR,0xA8, Instruction::FORMAT_2)},
        {OP_SIO,    Operation(OP_SIO,   0xF0, Instruction::FORMAT_1)},
        {OP_SSK,    Operation(OP_SSK,   0xEC, Instruction::FORMAT_3_4)},
        {OP_STA,    Operation(OP_STA,   0x0C, Instruction::FORMAT_3_4)},
        {OP_STB,    Operation(OP_STB,   0x78, Instruction::FORMAT_3_4)},
        {OP_STCH,   Operation(OP_STCH,  0x54, Instruction::FORMAT_3_4)},
        {OP_STF,    Operation(OP_STF,   0x80, Instruction::FORMAT_3_4)},
        {OP_STI,    Operation(OP_STI,   0xD4, Instruction::FORMAT_3_4)},
        {OP_STL,    Operation(OP_STL,   0x14, Instruction::FORMAT_3_4)},
        {OP_STS,    Operation(OP_STS,   0x7C, Instruction::FORMAT_3_4)},
        {OP_STSW,   Operation(OP_STSW,  0xE8, Instruction::FORMAT_3_4)},
        {OP_STT,    Operation(OP_STT,   0x84, Instruction::FORMAT_3_4)},
        {OP_STX,    Operation(OP_STX,   0x10, Instruction::FORMAT_3_4)},
        {OP_SUB,    Operation(OP_SUB,   0x1C, Instruction::FORMAT_3_4)},
        {OP_SUBF,   Operation(OP_SUBF,  0x5C, Instruction::FORMAT_3_4)},
        {OP_SUBR,   Operation(OP_SUBR,  0x94, Instruction::FORMAT_2)},
        {OP_SVC,    Operation(OP_SVC,   0xB0, Instruction::FORMAT_2)},
        {OP_TD,     Operation(OP_TD,    0xE0, Instruction::FORMAT_3_4)},
        {OP_TIO,    Operation(OP_TIO,   0xF8, Instruction::FORMAT_1)},
        {OP_TIX,    Operation(OP_TIX,   0x2C, Instruction::FORMAT_3_4)},
        {OP_TIXR,   Operation(OP_TIXR,  0xB8, Instruction::FORMAT_2)},
        {OP_WD,     Operation(OP_WD,    0xDC, Instruction::FORMAT_3_4)}
    };
}

#endif

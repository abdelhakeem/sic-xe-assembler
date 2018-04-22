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
	
	constexpr auto OP_DIV = "DIV";
    constexpr auto OP_DIVF = "DIVF";
    constexpr auto OP_DIVR = "DIVR";
    constexpr auto OP_FIX = "FIX";
    constexpr auto OP_FLOAT = "FLOAT";
    constexpr auto OP_HIO = "HIO";
    constexpr auto OP_J = "J";
    constexpr auto OP_JEQ = "JEQ";
	
	constexpr auto OP_JGT = "JGT";
    constexpr auto OP_JLT = "JLT";
    constexpr auto OP_JSUB = "JSUB";
    constexpr auto OP_LDA = "LDA";
    constexpr auto OP_LDB = "LDB";
    constexpr auto OP_LDCH = "LDCH";
    constexpr auto OP_LDF = "LDF";
    constexpr auto OP_LDL = "LDL";
	
	constexpr auto OP_LDS = "LDS";
    constexpr auto OP_LDT = "LDT";
    constexpr auto OP_LDX = "LDX";
    constexpr auto OP_LPS = "LPS";
    constexpr auto OP_MUL = "MUL";
    constexpr auto OP_MULF = "MULF";
    constexpr auto OP_MULR = "MULR";
    constexpr auto OP_NORM = "NORM";	

	constexpr auto OP_OR = "OR";
    constexpr auto OP_RD = "RD";
    constexpr auto OP_RMO = "RMO";
    constexpr auto OP_RSUB = "RSUB";
    constexpr auto OP_SHIFTL = "SHIFTL";
    constexpr auto OP_SHIFTR = "SHIFTR";
    constexpr auto OP_SIO = "SIO";
    constexpr auto OP_SSK = "SSK";
	
	constexpr auto OP_STA = "STA";
    constexpr auto OP_STB = "STB";
    constexpr auto OP_STCH = "STCH";
    constexpr auto OP_STF = "STF";
    constexpr auto OP_STI = "STI";
    constexpr auto OP_STL = "STL";
    constexpr auto OP_STS = "STS";
    constexpr auto OP_STSW = "STSW";
	
	constexpr auto OP_STT = "STT";
    constexpr auto OP_STX = "STX";
    constexpr auto OP_SUB = "SUB";
    constexpr auto OP_SUBF = "SUBF";
    constexpr auto OP_SUBR = "SUBR";
    constexpr auto OP_SVC = "SVC";
    constexpr auto OP_TD = "TD";
    constexpr auto OP_TIO = "TIO";
    constexpr auto OP_TIX = "TIX";
    constexpr auto OP_TIXR = "TIXR";
    constexpr auto OP_WD = "WD";	
	
    const unordered_map<string, Instruction> OPTAB {
        {OP_ADD,    Instruction(OP_ADD,   0x18, Instruction::FORMAT_3_4)},
        {OP_ADDF,   Instruction(OP_ADDF,  0x58, Instruction::FORMAT_3_4)},
        {OP_ADDR,   Instruction(OP_ADDR,  0x90, Instruction::FORMAT_2)},
        {OP_AND,    Instruction(OP_AND,   0x40, Instruction::FORMAT_3_4)},
        {OP_CLEAR,  Instruction(OP_CLEAR, 0xB4, Instruction::FORMAT_2)},
        {OP_COMP,   Instruction(OP_COMP,  0x28, Instruction::FORMAT_3_4)},
        {OP_COMPF,  Instruction(OP_COMPF, 0x88, Instruction::FORMAT_3_4)},
        {OP_COMPR,  Instruction(OP_COMPR, 0xA0, Instruction::FORMAT_2)},
		
		{OP_DIV,    Instruction(OP_DIV,   0x24, Instruction::FORMAT_3_4)},
        {OP_DIVF,   Instruction(OP_DIVF,  0x64, Instruction::FORMAT_3_4)},
        {OP_DIVR,   Instruction(OP_DIVR,  0x9C, Instruction::FORMAT_2)},
        {OP_FIX,    Instruction(OP_FIX,   0xC4, Instruction::FORMAT_1)},
        {OP_FLOAT,  Instruction(OP_FLOAT, 0xC0, Instruction::FORMAT_1)},
        {OP_HIO,    Instruction(OP_HIO,   0xF4, Instruction::FORMAT_1)},
        {OP_J,      Instruction(OP_J,     0x3C, Instruction::FORMAT_3_4)},
        {OP_JEQ,    Instruction(OP_JEQ,   0x30, Instruction::FORMAT_3_4)},
		
		{OP_JGT,    Instruction(OP_JGT,   0x34, Instruction::FORMAT_3_4)},
        {OP_JLT,    Instruction(OP_JLT,   0x38, Instruction::FORMAT_3_4)},
        {OP_JSUB,   Instruction(OP_JSUB,  0x48, Instruction::FORMAT_3_4)},
        {OP_LDA,    Instruction(OP_LDA,   0x00, Instruction::FORMAT_3_4)},
        {OP_LDB,    Instruction(OP_LDB,   0x68, Instruction::FORMAT_3_4)},
        {OP_LDCH,   Instruction(OP_LDCH,  0x50, Instruction::FORMAT_3_4)},
        {OP_LDF,    Instruction(OP_LDF,   0x70, Instruction::FORMAT_3_4)},
        {OP_LDL,    Instruction(OP_LDL,   0x08, Instruction::FORMAT_3_4)},
		
		{OP_LDS,    Instruction(OP_LDS,   0x6C, Instruction::FORMAT_3_4)},
        {OP_LDT,    Instruction(OP_LDT,   0x74, Instruction::FORMAT_3_4)},
        {OP_LDX,    Instruction(OP_LDX,   0x04, Instruction::FORMAT_3_4)},
        {OP_LPS,    Instruction(OP_LPS,   0xD0, Instruction::FORMAT_3_4)},
        {OP_MUL,    Instruction(OP_MUL,   0x20, Instruction::FORMAT_3_4)},
        {OP_MULF,   Instruction(OP_MULF,  0x60, Instruction::FORMAT_3_4)},
        {OP_MULR,   Instruction(OP_MULR,  0x98, Instruction::FORMAT_2)},
        {OP_NORM,   Instruction(OP_NORM,  0xC8, Instruction::FORMAT_1)},
		
		{OP_OR,     Instruction(OP_OR,    0x44, Instruction::FORMAT_3_4)},
        {OP_RD,     Instruction(OP_RD,    0xD8, Instruction::FORMAT_3_4)},
        {OP_RMO,    Instruction(OP_RMO,   0xAC, Instruction::FORMAT_2)},
        {OP_RSUB,   Instruction(OP_RSUB,  0x4C, Instruction::FORMAT_3_4)},
        {OP_SHIFTL, Instruction(OP_SHIFTL,0xA4, Instruction::FORMAT_2)},
        {OP_SHIFTR, Instruction(OP_SHIFTR,0xA8, Instruction::FORMAT_2)},
        {OP_SIO,    Instruction(OP_SIO,   0xF0, Instruction::FORMAT_1)},
        {OP_SSK,    Instruction(OP_SSK,   0xEC, Instruction::FORMAT_3_4)},
		
		{OP_STA,    Instruction(OP_STA,   0x0C, Instruction::FORMAT_3_4)},
        {OP_STB,    Instruction(OP_STB,   0x78, Instruction::FORMAT_3_4)},
        {OP_STCH,   Instruction(OP_STCH,  0x54, Instruction::FORMAT_3_4)},
        {OP_STF,    Instruction(OP_STF,   0x80, Instruction::FORMAT_3_4)},
        {OP_STI,    Instruction(OP_STI,   0xD4, Instruction::FORMAT_3_4)},
        {OP_STL,    Instruction(OP_STL,   0x14, Instruction::FORMAT_3_4)},
        {OP_STS,    Instruction(OP_STS,   0x7C, Instruction::FORMAT_3_4)},
        {OP_STSW,   Instruction(OP_STSW,  0xE8, Instruction::FORMAT_3_4)},
		
		{OP_STT,    Instruction(OP_STT,   0x84, Instruction::FORMAT_3_4)},
        {OP_STX,    Instruction(OP_STX,   0x10, Instruction::FORMAT_3_4)},
        {OP_SUB,    Instruction(OP_SUB,   0x1C, Instruction::FORMAT_3_4)},
        {OP_SUBF,   Instruction(OP_SUBF,  0x5C, Instruction::FORMAT_3_4)},
        {OP_SUBR,   Instruction(OP_SUBR,  0x94, Instruction::FORMAT_2)},
        {OP_SVC,    Instruction(OP_SVC,   0xB0, Instruction::FORMAT_2)},
        {OP_TD,     Instruction(OP_TD,    0xE0, Instruction::FORMAT_3_4)},
        {OP_TIO,    Instruction(OP_TIO,   0xF8, Instruction::FORMAT_1)},
        {OP_TIX,    Instruction(OP_TIX,   0x2C, Instruction::FORMAT_3_4)},
        {OP_TIXR,   Instruction(OP_TIXR,  0xB8, Instruction::FORMAT_2)},
        {OP_WD,     Instruction(OP_WD,    0xDC, Instruction::FORMAT_3_4)},
    };
}

#endif

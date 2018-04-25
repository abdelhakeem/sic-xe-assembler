#ifndef SIC_XE_ASSEMBLER_OPERANDTYPE_H
#define SIC_XE_ASSEMBLER_OPERANDTYPE_H

#include <string>

enum Type { REGISTER, SYMBOL, LITERAL };
enum Addressing { DIRECT, INDIRECT, IMMEDIATE, XE };
enum Format {
    FORMAT_1,
    FORMAT_2,
    FORMAT_3_4,
};
static const std::string registers[] = { "A", "X", "L", "B", "S", "T", "F" };
#endif //SIC_XE_ASSEMBLER_OPERANDTYPE_H

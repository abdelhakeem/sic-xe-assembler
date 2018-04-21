#ifndef SIC_XE_ASSEMBLER_PARSER_H
#define SIC_XE_ASSEMBLER_PARSER_H

#include "Instruction.h"

namespace cs222 {
    class Parser {
    public:
        Parser();

        Instruction parseLine(string line);
        void setLineNumber(int lineNumber);

    private:
        int lineNumber;// For line numbers.

        void makeOperands();
    };
}
#endif //SIC_XE_ASSEMBLER_PARSER_H

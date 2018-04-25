#ifndef SIC_XE_ASSEMBLER_PARSER_H
#define SIC_XE_ASSEMBLER_PARSER_H

#include "Instruction.h"
#include "IO.h"

namespace cs222 {
    class Parser {
    public:
        Parser(IO io);

        Instruction parseLine(string line);

        int lineNumber;
    private:
        IO io;

        void printInstructionFormatted();
        void makeOperands();
    };
}
#endif //SIC_XE_ASSEMBLER_PARSER_H

#ifndef SIC_XE_ASSEMBLER_ASSEMBLER_H
#define SIC_XE_ASSEMBLER_ASSEMBLER_H

#include "IO.h"
#include "Parser.h"
#include "InstructionChecker.h"

namespace cs222 {
    class Assembler {
    public:
        Assembler(string inputFileName, string outputFileName);

        void pass1();
        void pass2();
        void printSymbolTable();

    private:
        IO io;
        Parser parser;
        int programCounter;
        InstructionChecker checker;

    };
}

#endif //SIC_XE_ASSEMBLER_ASSEMBLER_H

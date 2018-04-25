#ifndef SIC_XE_ASSEMBLER_SYNTAXCHECKER_H
#define SIC_XE_ASSEMBLER_SYNTAXCHECKER_H

#include "IO.h"
#include "Instruction.h"

namespace cs222 {
    class InstructionChecker {
    public:
        InstructionChecker(IO io);

        void analyzeInstruction(Instruction);// Checks instruction correctness and consistency with its operands.

    private:
        IO io;
    };
}

#endif //SIC_XE_ASSEMBLER_SYNTAXCHECKER_H

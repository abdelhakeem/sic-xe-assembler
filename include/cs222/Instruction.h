#ifndef CS222_INSTRUCTION_H
#define CS222_INSTRUCTION_H

#include <string>
#include <vector>
#include "Operand.h"
#include "enums.h"

namespace cs222 {
    using std::string;

    class Instruction {
        public:

            Instruction(
                    const string& mnemonic,
                    const char& opcode,
                    const Format& format,
                    const std::vector<Operand> operands
            );
            const string& getMnemonic() const;
            const char& getOpcode() const;
            const Format& getFormat() const;
            const std::vector<Operand>& getOperands() const;
            const bool isIndexable() const;
            const bool isOperandsConsistent() const;

        private:
            const string mnemonic;
            const char opcode;
            const Format format;
            std::vector<Operand> operands;
            int registers;
            bool indexable;
            bool operandsConsistent;

            void analyzeOperands();
    };
}

#endif

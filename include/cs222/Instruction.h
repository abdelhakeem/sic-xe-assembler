#ifndef CS222_INSTRUCTION_H
#define CS222_INSTRUCTION_H

#include <string>
#include <vector>
#include "Operand.h"

namespace cs222 {
    using std::string;

    class Instruction {
        public:

            enum Addressing { DIRECT, INDIRECT, IMMEDIATE, XE };
            enum Format {
                FORMAT_1,
                FORMAT_2,
                FORMAT_3_4,
            };
            Instruction(
                    const string& mnemonic,
                    const char& opcode,
                    const Format& format,
                    const std::vector<Operand> operands
            );
            const string& getMnemonic() const;
            const char& getOpcode() const;
            const Format& getFormat() const;

        private:
            string mnemonic;
            char opcode;
            Format format;
            std::vector<Operand> operands;
            int registers;
            bool indexable;
            bool operandsConsistent;

            void analyzeOperands();
    };
}

#endif

#ifndef CS222_OPERATION_H
#define CS222_OPERATION_H

#include <cs222/Instruction.h>

namespace cs222 {
    class Operation {
        public:
            Operation(
                    const std::string& mnemonic,
                    const char& opcode,
                    const Instruction::Format& validFormat);
            std::string getMnemonic() const;
            char getOpcode() const;
            bool isValidFormat(const Instruction::Format& format) const;
        private:
            const std::string mnemonic;
            const char opcode;
            const Instruction::Format validFormat;
    };
}

#endif

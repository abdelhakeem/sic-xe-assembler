#ifndef CS222_INSTRUCTION_H
#define CS222_INSTRUCTION_H

#include <unordered_map>
#include <Operand.h>

namespace cs222 {
    class Instruction {
        public:
            enum Format {
                FORMAT_1 = 1,
                FORMAT_2 = 2,
                FORMAT_3 = 4,
                FORMAT_4 = 8,
                FORMAT_3_4 = 12
            };
            Instruction(
                    const std::string& label,
                    const std::string& operation,
                    const Operand& firstOperand,
                    const Operand& secondOperand,
                    const std::string& comment);
            std::string getLabel() const;
            std::string getOperation() const;
            Operand getFirstOperand() const;
            Operand getSecondOperand() const;
            std::string getComment() const;
            const static std::unordered_map<Format, size_t> Length;
        private:
            const std::string label;
            const std::string operation;
            const Operand firstOperand;
            const Operand secondOperand;
            const std::string comment;
    };
}

#endif

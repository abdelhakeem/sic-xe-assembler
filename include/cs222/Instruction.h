#ifndef CS222_INSTRUCTION_H
#define CS222_INSTRUCTION_H

#include <bitset>
#include <unordered_map>
#include <cs222/Operand.h>

namespace cs222 {
    class Instruction {
        public:
            enum Format {
                FORMAT_1 = 1 << 0,
                FORMAT_2 = 1 << 1,
                FORMAT_3 = 1 << 2,
                FORMAT_4 = 1 << 3,
                FORMAT_3_4 = FORMAT_3 | FORMAT_4
            };
            enum Flag {
                FLAG_INDIRECT       =   5,
                FLAG_IMMEDIATE      =   4,
                FLAG_INDEXED        =   3,
                FLAG_BASE_RELATIVE  =   2,
                FLAG_PC_RELATIVE    =   1,
                FLAG_EXTENDED       =   0
            };
            Instruction(
                    const std::string& label,
                    const std::string& operation,
                    const Operand& firstOperand,
                    const Operand& secondOperand,
                    const std::string& comment,
                    const std::bitset<6>& flags);
            std::string getLabel() const;
            std::string getOperation() const;
            Operand getFirstOperand() const;
            Operand getSecondOperand() const;
            std::string getComment() const;
            bool isSet(const Flag& f) const;
            const static std::unordered_map<Format, size_t> Length;
        private:
            const std::string label;
            const std::string operation;
            const Operand firstOperand;
            const Operand secondOperand;
            const std::string comment;
            const std::bitset<6> flags;
    };
}

#endif

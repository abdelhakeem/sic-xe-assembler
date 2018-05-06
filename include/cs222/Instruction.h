#ifndef CS222_INSTRUCTION_H
#define CS222_INSTRUCTION_H

#include <bitset>
#include <unordered_map>
#include <vector>
#include <cs222/Operand.h>

namespace cs222 {
    typedef std::pair<Operand, Operand> Operand_pair;

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
                    const size_t& lineNumber,
                    const std::string& line);
            Instruction(
                    const size_t& lineNumber,
                    const std::string& line,
                    const std::string& label,
                    const std::string& operation,
                    const Operand& firstOperand,
                    const Operand& secondOperand,
                    const std::string& operandsToken,
                    const std::string& comment,
                    const std::bitset<6>& flags);
            size_t getLineNumber() const;
            std::string getLine() const;
            bool isCommentLine() const;
            std::string getLabel() const;
            std::string getOperation() const;
            Operand getFirstOperand() const;
            Operand getSecondOperand() const;
            std::string getOperandsToken() const;
            std::string getComment() const;
            std::bitset<6> getFlags() const;
            bool isSet(const Flag& f) const;
            void addError(const std::string& error);
            std::vector<std::string> getErrors() const;
            void clearErrors();
            void addWarning(const std::string& warning);
            std::vector<std::string> getWarnings() const;
            void clearWarnings();
            size_t getAddress() const;
            void setAddress(const size_t addr);
            const static std::unordered_map<Format, size_t> Length;
        private:
            const size_t lineNumber;
            const std::string line;
            const bool commentLine;
            const std::string label;
            const std::string operation;
            const Operand_pair operands;
            const std::string operandsToken;
            const std::string comment;
            const std::bitset<6> flags;
            size_t address;
            std::vector<std::string> errors;
            std::vector<std::string> warnings;
    };
}

#endif

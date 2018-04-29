#include <cs222/Instruction.h>

namespace cs222 {
    Instruction::Instruction(
            const size_t& lineNumber,
            const std::string& line) :
        lineNumber(lineNumber), line(line), comment(line) { }

    Instruction::Instruction(
            const size_t& lineNumber,
            const std::string& line,
            const std::string& label,
            const std::string& operation,
            const Operand& firstOperand,
            const Operand& secondOperand,
            const std::string& comment,
            const std::bitset<6>& flags) :
        lineNumber(lineNumber), line(line), label(label),
        operation(operation), firstOperand(firstOperand),
        secondOperand(secondOperand), comment(comment), flags(flags) { }

    size_t Instruction::getLineNumber() const
    {
        return lineNumber;
    }

    std::string Instruction::getLine() const
    {
        return line;
    }

    std::string Instruction::getLabel() const
    {
        return label;
    }

    std::string Instruction::getOperation() const
    {
        return operation;
    }

    Operand Instruction::getFirstOperand() const
    {
        return firstOperand;
    }

    Operand Instruction::getSecondOperand() const
    {
        return secondOperand;
    }

    std::string Instruction::getComment() const
    {
        return comment;
    }

    std::bitset<6> Instruction::getFlags() const
    {
        return flags;
    }

    bool Instruction::isSet(const Flag& f) const
    {
        return flags.test(f);
    }

    const std::unordered_map<Instruction::Format, size_t> Instruction::Length {
        { Instruction::FORMAT_1, 1 },
        { Instruction::FORMAT_2, 2 },
        { Instruction::FORMAT_3, 3 },
        { Instruction::FORMAT_4, 4 }
    };
}

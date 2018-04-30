#include <cs222/Instruction.h>

namespace cs222 {
    Instruction::Instruction(
            const size_t& lineNumber,
            const std::string& line) :
        lineNumber(lineNumber), line(line),
        commentLine(true), comment(line) { }

    Instruction::Instruction(
            const size_t& lineNumber,
            const std::string& line,
            const std::string& label,
            const std::string& operation,
            const Operand& firstOperand,
            const Operand& secondOperand,
            const std::string& comment,
            const std::bitset<6>& flags) :
        lineNumber(lineNumber), line(line), commentLine(false),
        label(label), operation(operation),
        operands(Operand_pair(firstOperand, secondOperand)),
        comment(comment), flags(flags) { }

    size_t Instruction::getLineNumber() const
    {
        return lineNumber;
    }

    std::string Instruction::getLine() const
    {
        return line;
    }

    bool Instruction::isCommentLine() const
    {
        return commentLine;
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
        return operands.first;
    }

    Operand Instruction::getSecondOperand() const
    {
        return operands.second;
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

    void Instruction::addError(const std::string& error)
    {
        errors.push_back(error);
    }

    std::vector<std::string> Instruction::getErrors() const
    {
        return errors;
    }

    void Instruction::clearErrors()
    {
        errors.clear();
    }

    const std::unordered_map<Instruction::Format, size_t> Instruction::Length {
        { Instruction::FORMAT_1, 1 },
        { Instruction::FORMAT_2, 2 },
        { Instruction::FORMAT_3, 3 },
        { Instruction::FORMAT_4, 4 }
    };
}

#include <Instruction.h>

namespace cs222 {
    Instruction::Instruction(
            const std::string& label,
            const std::string& operation,
            const Operand& firstOperand,
            const Operand& secondOperand,
            const std::string& comment) :
        label(label), operation(operation), firstOperand(firstOperand),
        secondOperand(secondOperand), comment(comment) { }

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

    const std::unordered_map<Instruction::Format, size_t> Instruction::Length {
        { Instruction::FORMAT_1, 1 },
        { Instruction::FORMAT_2, 2 },
        { Instruction::FORMAT_3, 3 },
        { Instruction::FORMAT_4, 4 }
    };
}

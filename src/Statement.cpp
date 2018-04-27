#include <Statement.h>

namespace cs222 {
    Statement::Statement(
            const std::string& label,
            const std::string& operation,
            const Operand& firstOperand,
            const Operand& secondOperand,
            const std::string& comment) :
        label(label), operation(operation), firstOperand(firstOperand),
        secondOperand(secondOperand), comment(comment) { }

    std::string Statement::getLabel() const
    {
        return label;
    }

    std::string Statement::getOperation() const
    {
        return operation;
    }

    Operand Statement::getFirstOperand() const
    {
        return firstOperand;
    }

    Operand Statement::getSecondOperand() const
    {
        return secondOperand;
    }

    std::string Statement::getComment() const
    {
        return comment;
    }
}

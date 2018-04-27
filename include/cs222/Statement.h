#ifndef CS222_STATEMENT_H
#define CS222_STATEMENT_H

#include <Operand.h>
#include <Operation.h>

namespace cs222 {
    class Statement {
        public:
            Statement(
                    const std::string& label,
                    const Operation& operation,
                    const Operand& firstOperand,
                    const Operand& secondOperand,
                    const std::string& comment);
            std::string getLabel() const;
            Operation getOperation() const;
            Operand getFirstOperand() const;
            Operand getSecondOperand() const;
            std::string getComment() const;
        private:
            const std::string label;
            const Operation operation;
            const Operand firstOperand;
            const Operand secondOperand;
            const std::string comment;
    };
}

#endif

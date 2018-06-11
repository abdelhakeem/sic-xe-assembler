#include <cs222/Instruction.h>
#include <cs222/OpTable.h>
#include <cs222/Utility.h>

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
            const std::string& operandsToken,
            const std::string& comment,
            const std::bitset<6>& flags) :
        lineNumber(lineNumber), line(line), commentLine(false),
        label(label), operation(operation),
        operands(Operand_pair(firstOperand, secondOperand)),
        operandsToken(operandsToken), comment(comment), flags(flags) { }

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

    std::string Instruction::getOperandsToken() const
    {
        return operandsToken;
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

    void Instruction::addWarning(const std::string& warning)
    {
        warnings.push_back(warning);
    }

    std::vector<std::string> Instruction::getWarnings() const
    {
        return warnings;
    }

    void Instruction::clearWarnings()
    {
        warnings.clear();
    }

    size_t Instruction::getAddress() const
    {
        return address;
    }

    void Instruction::setAddress(const size_t addr)
    {
        address = addr;
    }

    Instruction::Format Instruction::getFormat() const
    {
        std::string op = operation;
        if (op[0] == '+')
            op = op.substr(1);

        if (isOperation(op))
        {
            Format fmt = OpTable.find(op)->second.getValidFormat();
            if (fmt == Instruction::FORMAT_3_4)
            {
                fmt = Instruction::FORMAT_3;
                if (isSet(Instruction::FLAG_EXTENDED))
                {
                    fmt = Instruction::FORMAT_4;
                }
            }

            return fmt;
        }

        return static_cast<Instruction::Format>(0);
    }

    size_t Instruction::getLength() const
    {
        size_t length = 0;
        std::string op = operation;
        if (op[0] == '+')
            op = op.substr(1);

        if (isOperation(op))
        {
            length = Length.find(getFormat())->second;
        }
        else if (op == DIR_WORD)
        {
            length = 3;
        }
        else if (op == DIR_RESW)
        {
            length = 3 * std::stoul(operands.first.getValue());
        }
        else if (op == DIR_RESB)
        {
            length = std::stoul(operands.first.getValue());
        }
        else if (op == DIR_BYTE)
        {
            length = operands.first.getValue().length();
            if (operands.first.getType() == Operand::HEX_CONSTANT)
            {
                length /= 2;
            }
        }
        else if (label == "*") {
            length = operation.length();
            if (operands.first.getType() == Operand::HEX_LITERAL)
            {
                length /= 2;
            }
        }

        return length;
    }

    const std::unordered_map<Instruction::Format, size_t> Instruction::Length {
        { Instruction::FORMAT_1, 1 },
        { Instruction::FORMAT_2, 2 },
        { Instruction::FORMAT_3, 3 },
        { Instruction::FORMAT_4, 4 }
    };
}

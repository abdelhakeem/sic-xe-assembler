#include <algorithm>
#include <cs222/OpTable.h>
#include <cs222/Utility.h>
#include <cs222/Validator.h>

namespace cs222 {
    bool Validator::validate(Instruction& inst) const
    {
        if (inst.isCommentLine())
        {
            return true;
        }

        bool result = validateOperandTypes(inst);
        result &= validateFormat(inst);
        return result;
    }

    bool Validator::validateOperandTypes(Instruction& inst) const
    {
        std::string op = inst.getOperation();
        Operand::Type firstOpType = inst.getFirstOperand().getType();
        Operand::Type secondOpType = inst.getSecondOperand().getType();
        if (is_mOp(op))
        {
            if (isMemType(firstOpType) && secondOpType == Operand::NONE)
            {
                return true;
            }
            else
            {
                inst.addError(
                        std::string("Expected symbol or address after ") +
                        op);
                return false;
            }
        }
        else if (is_r1Op(op))
        {
            if (
                    firstOpType == Operand::REGISTER &&
                    secondOpType == Operand::NONE)
            {
                return true;
            }
            else
            {
                inst.addError(
                        std::string("Expected register symbol after ") +
                        op);
                return false;
            }
        }
        else if (is_r1r2Op(op))
        {
            if (
                    firstOpType == Operand::REGISTER &&
                    secondOpType == Operand::REGISTER)
            {
                return true;
            }
            else
            {
                inst.addError(
                        std::string("Expected two register symbols after ") +
                        op);
                return false;
            }
        }
        else if (is_noneOp(op))
        {
            if (firstOpType == Operand::NONE)
            {
                return true;
            }
            else
            {
                inst.addWarning(
                        std::string("Expected no operands after ") +
                        op);
                return true; // Ignored
            }
        }
        else if (toUpper(op) == "START")
        {
            if (
                    firstOpType == Operand::INT_CONSTANT &&
                    secondOpType == Operand::NONE &&
                    inst.getFirstOperand().getValue()[0] != '-')
            {
                return true;
            }
            inst.addError("Expected absolute address after START");
            return false;
        }
        else if (toUpper(op) == "END")
        {
            if (
                    firstOpType == Operand::NONE ||
                    (firstOpType == Operand::SYMBOL &&
                    secondOpType == Operand::NONE))
            {
                return true;
            }
            inst.addError("Expected symbol or nothing after END");
            return false;
        }
        else if (is_storageDir(op))
        {
            if (inst.getLabel().empty())
            {
                inst.addError(
                        std::string("Expected label before ")
                        + op);
            }
            if (op == "RESB" || op == "RESW")
            {
                if (
                        firstOpType == Operand::INT_CONSTANT &&
                        secondOpType == Operand::NONE)
                {
                    if (inst.getFirstOperand().getValue()[0] == '-')
                    {
                        inst.addError(
                                std::string("Expected unsigned integer with ")
                                + op);
                        return false;
                    }
                    return true;
                }
                else
                {
                    inst.addError(
                            std::string("Expected integer constant after ")
                            + op);
                    return false;
                }
            }
            else if (op == "BYTE")
            {
                if (
                        firstOpType == Operand::CHAR_CONSTANT &&
                        secondOpType == Operand::NONE)
                {
                    return true;
                }
                if (
                        firstOpType == Operand::HEX_CONSTANT &&
                        secondOpType == Operand::NONE)
                {
                    return true;
                }
                inst.addError(
                        std::string("Expected char or hex constant after ")
                        + op);
                return false;
            }
            else if (op == "WORD")
            {
                if(
                    firstOpType == Operand::INT_CONSTANT &&
                    secondOpType == Operand::NONE)
                {
                    return true;
                }
                else
                {
                    inst.addError(
                            std::string("Expected int constant after ")
                            + op);
                    return false;
                }
            }
        }
        inst.addWarning(
                std::string("Unsupported directive or operation: ") + op);
        return false;
    }

    bool Validator::validateFormat(Instruction& inst) const
    {
        std::string op = inst.getOperation();
        if (isDirective(op))
        {
            if (inst.getFlags().any())
            {
                inst.addError(
                        std::string("Directive should not have ") +
                        "addressing parameters: " + op);
                return false;
            }
            return true;
        }
        Instruction::Format format = Instruction::FORMAT_3;
        if (inst.isSet(Instruction::FLAG_EXTENDED))
        {
            format = Instruction::FORMAT_4;
        }
        else if (is_r1Op(op) || is_r1r2Op(op))
        {
            format = Instruction::FORMAT_2;
            if (inst.getFlags().any())
            {
                inst.addError(std::string("Invalid format used with ") + op);
                return false;
            }
        }
        else if (is_noneOp(op))
        {
            format = Instruction::FORMAT_1;
            if (inst.getFlags().any())
            {
                inst.addError(std::string("Invalid format used with ") + op);
                return false;
            }
        }

        if (isOperation(op))
        {
            if (OpTable.find(toUpper(op))->second.isValidFormat(format))
            {
                return true;
            }
        }

        inst.addError(std::string("Invalid format used with ") + op);
        return false;
    }

    bool Validator::contains(
            const std::vector<std::string>& vec,
            const std::string& key)
    {
        return std::binary_search(
                vec.begin(),
                vec.end(),
                toUpper(key));
    }

    bool Validator::is_mOp(const std::string& op)
    {
        return contains(mOps, op);
    }

    bool Validator::is_r1Op(const std::string& op)
    {
        return contains(r1Ops, op);
    }

    bool Validator::is_r1r2Op(const std::string& op)
    {
        return contains(r1r2Ops, op);
    }

    bool Validator::is_noneOp(const std::string& op)
    {
        return contains(noneOps, op);
    }

    bool Validator::is_storageDir(const std::string& op)
    {
        return contains(storageDirs, op);
    }

    bool Validator::isMemType(const Operand::Type& type)
    {
        switch (type)
        {
            case Operand::SYMBOL:
            case Operand::INT_CONSTANT:
                return true;
            default:
                return false;
        }
    }

    const std::vector<std::string> Validator::mOps {
        "ADD", "ADDF", "AND", "COMP", "COMPF", "DIV", "DIVF",
        "J", "JEQ", "JGT", "JLT", "JSUB", "LDA", "LDB", "LDCH",
        "LDF", "LDL", "LDS", "LDT", "LDX", "MUL", "MULF",
        "OR", "RD", "STA", "STB", "STCH", "STF", "STI",
        "STL", "STF", "STSW", "STT", "STX", "SUB", "SUBF", "TD",
        "TIX", "WD"
    };

    const std::vector<std::string> Validator::r1Ops {
        "CLEAR", "TIXR"
    };

    const std::vector<std::string> Validator::r1r2Ops {
        "ADDR", "COMPR", "DIVR", "MULR", "RMO", "SUBR"
    };

    const std::vector<std::string> Validator::noneOps {
        "RSUB"
    };

    const std::vector<std::string> Validator::storageDirs {
        "BYTE", "RESB", "RESW", "WORD"
    };
}

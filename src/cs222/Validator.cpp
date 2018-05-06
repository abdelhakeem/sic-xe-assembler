#include <cs222/OpTable.h>
#include <cs222/Utility.h>
#include <cs222/Validator.h>

namespace cs222 {
    bool Validator::validate(Instruction& inst)
    {
        if (inst.isCommentLine())
        {
            return true;
        }

        bool result = validateOperandTypes(inst);
        result &= validateFormat(inst);
        return result;
    }

    bool Validator::validateOperandTypes(Instruction& inst)
    {
        std::string op = inst.getOperation();
        if (op[0] == '+')
        {
            op = op.substr(1);
        }
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
                        std::string("Expected symbol or address after ") + op);
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
                        std::string("Expected register symbol after ") + op);
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
            if (secondOpType == Operand::NONE)
            {
                switch (firstOpType)
                {
                    case Operand::NONE:
                    case Operand::SYMBOL:
                    case Operand::INT_CONSTANT:
                        if (inst.getFirstOperand().getValue()[0] != '-')
                        {
                            return true;
                        }
                }
            }
            inst.addError(
                    "Expected symbol, absolute address, or nothing after END");
            return false;
        }
        else if (is_storageDir(op))
        {
            if (inst.getLabel().empty())
            {
                inst.addError(
                        std::string("Expected label before ") + op);
            }
            if (op == "RESB" || op == "RESW")
            {
                if (
                        firstOpType == Operand::INT_CONSTANT &&
                        secondOpType == Operand::NONE &&
                        inst.getFirstOperand().getValue()[0] != '-')
                {
                    return true;
                }
                inst.addError(
                        std::string("Expected unsigned integer after ") + op);
                return false;
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
                            std::string("Expected int constant after ") + op);
                    return false;
                }
            }
        }
        inst.addError(
                std::string("Unsupported directive or operation: ") + op);
        return false;
    }

    bool Validator::validateFormat(Instruction& inst)
    {
        std::string op = inst.getOperation();
        if (op[0] == '+')
        {
            op = op.substr(1);
        }
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

    const std::string Validator::mOps[] {
        OP_ADD, OP_ADDF, OP_AND, OP_COMP, OP_COMPF, OP_DIV, OP_DIVF,
        OP_J, OP_JEQ, OP_JGT, OP_JLT, OP_JSUB, OP_LDA, OP_LDB,
        OP_LDCH, OP_LDF, OP_LDL, OP_LDS, OP_LDT, OP_LDX, OP_MUL,
        OP_MULF, OP_OR, OP_RD, OP_STA, OP_STB, OP_STCH, OP_STF,
        OP_STI, OP_STL, OP_STF, OP_STSW, OP_STT, OP_STX, OP_SUB,
        OP_SUBF, OP_TD, OP_TIX, OP_WD
    };

    const std::string Validator::r1Ops[] { OP_CLEAR, OP_TIXR };

    const std::string Validator::r1r2Ops[] {
        OP_ADDR, OP_COMPR, OP_DIVR, OP_MULR, OP_RMO, OP_SUBR
    };

    const std::string Validator::noneOps[] { OP_RSUB };

    const std::string Validator::storageDirs[] {
        DIR_BYTE, DIR_RESB, DIR_RESW, DIR_WORD
    };

    bool Validator::is_mOp(const std::string& op)
    {
        return arrayContains(mOps, toUpper(op));
    }

    bool Validator::is_r1Op(const std::string& op)
    {
        return arrayContains(r1Ops, op);
    }

    bool Validator::is_r1r2Op(const std::string& op)
    {
        return arrayContains(r1r2Ops, op);
    }

    bool Validator::is_noneOp(const std::string& op)
    {
        return arrayContains(noneOps, op);
    }

    bool Validator::is_storageDir(const std::string& op)
    {
        return arrayContains(storageDirs, op);
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
}

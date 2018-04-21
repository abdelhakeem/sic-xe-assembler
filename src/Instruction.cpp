//
// Created by H on 4/21/18.
//

#include <string>
#include "Instruction.h"

namespace cs222 {
    Instruction::Instruction(
            const string& mnemonic,
            const char& opcode,
            const Format& format,
            const std::vector<Operand> operands
    ) : mnemonic(mnemonic), opcode(opcode), format(format), operands(operands)
    {
        registers = 0;
        analyzeOperands();
    }

    void Instruction::analyzeOperands() {
        operandsConsistent = true;
        indexable = false;
        if (operands.size() > 2) {
            operandsConsistent = false;
        } else {
            if (!operands.empty()) {
                Operand firstOperand = operands[0];
                if (firstOperand.isRegister()) {
                    registers++;
                }
                if (operands.size() == 2) {
                    Operand secondOperand = operands[1];
                    if (!firstOperand.isRegister() && secondOperand.getToken() == "X") {
                        indexable = true;
                    }
                    if (secondOperand.isRegister()) {
                        if (!firstOperand.isRegister()) {
                            operandsConsistent = false;
                        }
                        registers++;
                    }
                }
            }
        }
    }

    const string& Instruction::getMnemonic() const { return mnemonic; }
    const char& Instruction::getOpcode() const { return opcode; }
    const Format& Instruction::getFormat() const { return format; }
    const std::vector<Operand>& Instruction::getOperands() const { return operands; }
    const bool Instruction::isIndexable() const { return indexable; }
    const bool Instruction::isOperandsConsistent() const { operandsConsistent; }
}
//
// Created by H on 4/21/18.
//

#include <string>
#include "constants.h"
#include "Operand.h"

namespace cs222 {

    Operand::Operand(
            const std::string& token,
            const Type& type) :
    token(token), type(type) {
        registerOperand = false;
        if (token.length() == 1) {
            for (string c : registers) {
                if (token.compare(c) == 0) {
                    registerOperand = true;
                }
            }
        }
    }
    const std::string& Operand::getToken() const { return token; }
    const Type& Operand::getType() const { return type; }
    const bool Operand::isRegister() const { return registerOperand; }

}
#include <cs222/Operand.h>

namespace cs222 {
    Operand::Operand() : type(Operand::NONE) { }

    Operand::Operand(const Type& type, const std::string& token) :
        type(type), token(token) { }

    bool Operand::isNone() const
    {
        return type == Operand::NONE;
    }

    bool Operand::isAddress() const
    {
        return type == Operand::ADDRESS;
    }

    bool Operand::isRegister() const
    {
        return type == Operand::REGISTER;
    }

    bool Operand::isLiteral() const
    {
        return type == Operand::LITERAL;
    }

    std::string Operand::getToken() const
    {
        return token;
    }
}

#include <cs222/Operand.h>

namespace cs222 {
    Operand::Operand() : type(Operand::NONE) { }

    Operand::Operand(const Type& type, const std::string& value = "") :
        type(type), value(value) { }

    Operand::Type Operand::getType() const
    {
        return type;
    }

    std::string Operand::getValue() const
    {
        return value;
    }
}

#include <cs222/Symbol.h>

namespace cs222 {
    Symbol::Symbol(
            const string& name,
            const int& value,
            const Type& type) :
        name(name), value(value), type(type) { }

    string Symbol::getName() const
    {
        return name;
    }

    int Symbol::getValue() const
    {
        return value;
    }

    Symbol::Type Symbol::getType() const
    {
        return type;
    }
}

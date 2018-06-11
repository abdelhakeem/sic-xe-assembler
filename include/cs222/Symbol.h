#ifndef CS222_SYMBOL_H
#define CS222_SYMBOL_H

#include <string>

namespace cs222 {
    using std::string;

    class Symbol {
        public:
            enum Type { ABSOLUTE, RELATIVE };
            Symbol(
                    const string& name = "",
                    const int& value = 0,
                    const Type& type = ABSOLUTE);
            string getName() const;
            int getValue() const;
            Type getType() const;
        private:
            string name;
            int value;
            Type type;
    };
}

#endif

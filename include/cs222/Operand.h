#ifndef CS222_OPERAND_H
#define CS222_OPERAND_H

#include <string>

namespace cs222 {
    using std::string;

    class Operand {
        public:
            enum Type { REGISTER, SYMBOL, LITERAL };
            enum Addressing { DIRECT, INDIRECT, IMMEDIATE, XE };

            // TODO complete addressing modes

            Operand(
                    const string& token,
                    const int& value,
                    const Type& type,
                    const Addressing& addressing);
            const string& getToken() const;
            const int& getValue() const;
            const Type& getType() const;
            const Addressing& getAddressing() const;
        private:
            string token;
            int value;
            Type type;
            Addressing addressing;
    };
}

#endif

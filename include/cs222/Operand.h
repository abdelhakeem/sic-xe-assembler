#ifndef CS222_OPERAND_H
#define CS222_OPERAND_H

#include <string>

namespace cs222 {
    using std::string;

    enum Type { REGISTER, SYMBOL, LITERAL };

    class Operand {
        public:

            Operand(
                    const string& token,
                    const int& value,
                    const Type& type);
            const string& getToken() const;
            const int& getValue() const;
            const Type& getType() const;
        private:
            const string token;
            const Type type;
            const int value;
    };
}

#endif

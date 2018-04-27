#ifndef CS222_OPERAND_H
#define CS222_OPERAND_H

#include <string>

namespace cs222 {
    class Operand {
        public:
            enum Type { NONE, ADDRESS, REGISTER, LITERAL };
            Operand();
            Operand(const Type& type, const std::string& token);
            bool isNone() const;
            bool isAddress() const;
            bool isRegister() const;
            bool isLiteral() const;
            std::string getToken() const;
        private:
            const Type type;
            const std::string token;
    };
}

#endif

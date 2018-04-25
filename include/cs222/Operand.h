#ifndef CS222_OPERAND_H
#define CS222_OPERAND_H

#include <string>
#include "constants.h"

namespace cs222 {
    using std::string;

    class Operand {
        public:

            Operand(
                    const string& token,
                    const Type& type);
            const string& getToken() const;
            const Type& getType() const;
            const bool isRegister() const;
        private:
            const string token;
            const Type type;
            bool registerOperand;
    };
}

#endif

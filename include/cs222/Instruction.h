#ifndef CS222_INSTRUCTION_H
#define CS222_INSTRUCTION_H

#include <string>
#include <set>
#include "Operand.h"
#include "Operation.h"

namespace cs222 {
    using std::string;
    using std::set;

    class Instruction {
        public:
            // TODO add more error types as needed
            enum Error { ERR_DUP_SYMBOL };
            Instruction(
                    const int& line,
                    const int& address,
                    const string& label,
                    const Operation& operation,
                    const Operand operands[2],
                    const string& comment);
            const int& getLine() const;
            const int& getAddress() const;
            const string& getLabel() const;
            const Operation& getOperation() const;
            const Operand* getOperands() const;
            const string& getComment() const;
            void addError(const Error& error);
            void deleteError(const Error& error);
            bool hasError(const Error& error) const;
        private:
            int line;
            int address;
            string label;
            Operation operation;
            Operand operands[2];
            string comment;
            set<Error> errors;
    };
}

#endif

#ifndef CS222_VALIDATOR_H
#define CS222_VALIDATOR_H

#include <cs222/Instruction.h>

namespace cs222 {
    class Validator {
        public:
            static bool validate(Instruction& inst);
        private:
            static bool validateOperandTypes(Instruction& inst);
            static bool validateFormat(Instruction& inst);

            // Instructions that expect a memory operand
            static const std::string mOps[];

            // Instructions that expect a register operand
            static const std::string r1Ops[];

            // Instructions that expect two register operands
            static const std::string r1r2Ops[];

            // Instructions that expect no operands
            static const std::string noneOps[];

            // Storage directives
            static const std::string storageDirs[];

            static bool is_mOp(const std::string& op);
            static bool is_r1Op(const std::string& op);
            static bool is_r1r2Op(const std::string& op);
            static bool is_noneOp(const std::string& op);
            static bool is_storageDir(const std::string& op);
            static bool isMemType(const Operand::Type& type);
    };
}

#endif

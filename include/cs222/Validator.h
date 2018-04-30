#ifndef CS222_VALIDATOR_H
#define CS222_VALIDATOR_H

#include <cs222/Instruction.h>

namespace cs222 {
    class Validator {
        public:
            bool validate(Instruction& inst) const;
        private:
            bool validateOperandTypes(Instruction& inst) const;
            bool validateFormat(Instruction& inst) const;
            static bool contains(
                    const std::vector<std::string>& vec,
                    const std::string& key);
            static bool is_mOp(const std::string& op);
            static bool is_r1Op(const std::string& op);
            static bool is_r1r2Op(const std::string& op);
            static bool is_noneOp(const std::string& op);
            static bool is_storageDir(const std::string& op);
            static bool isMemType(const Operand::Type& type);
            // Instructions that expect a memory operand
            static const std::vector<std::string> mOps;
            // Instructions that expect a register operand
            static const std::vector<std::string> r1Ops;
            // Instructions that expect two register operands
            static const std::vector<std::string> r1r2Ops;
            // Instructions that expect no operands
            static const std::vector<std::string> noneOps;
            // Storage directives
            static const std::vector<std::string> storageDirs;
    };
}

#endif

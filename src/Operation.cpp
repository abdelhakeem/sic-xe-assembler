#include <Operation.h>

namespace cs222 {
    Operation::Operation(
            const std::string& mnemonic,
            const char& opcode,
            const Instruction::Format& validFormat) :
        mnemonic(mnemonic), opcode(opcode), validFormat(validFormat) { }

    std::string Operation::getMnemonic() const
    {
        return mnemonic;
    }

    char Operation::getOpcode() const
    {
        return opcode;
    }

    bool Operation::isValidFormat(const Instruction::Format& format) const
    {
        return validFormat & format;
    }
}

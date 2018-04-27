#include <Instruction.h>

namespace cs222 {
    const std::unordered_map<Instruction::Format, size_t> Instruction::Length {
        { Instruction::FORMAT_1, 1 },
        { Instruction::FORMAT_2, 2 },
        { Instruction::FORMAT_3, 3 },
        { Instruction::FORMAT_4, 4 }
    };
}

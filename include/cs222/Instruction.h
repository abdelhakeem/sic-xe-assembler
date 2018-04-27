#ifndef CS222_INSTRUCTION_H
#define CS222_INSTRUCTION_H

#include <unordered_map>

namespace cs222 {
    class Instruction {
        public:
            enum Format {
                FORMAT_1 = 1,
                FORMAT_2 = 2,
                FORMAT_3 = 4,
                FORMAT_4 = 8,
                FORMAT_3_4 = 12
            };
            const static std::unordered_map<Format, size_t> Length;
        private:
    };
}

#endif

#ifndef SIC_XE_ASSEMBLER_PASS2_H
#define SIC_XE_ASSEMBLER_PASS2_H

#include <string>
#include <vector>
#include <bits/unordered_map.h>
#include "Instruction.h"

namespace cs222 {
    class Pass2 {
    public:
        int main(int argc, char* argv[]);
    private:
        std::vector<std::string> modificationAddresses;
        std::unordered_map litTab;
        std::unordered_map symTab;
	int base = -1;

        std::string translate(Instruction instruction);
        void readSymbols();
        void writeObjectProgram();
    };
}

#endif //SIC_XE_ASSEMBLER_PASS2_H

#include <iostream>
#include <unordered_map>
#include <include/cs222/Instruction.h>

#include "Pass2.h"

namespace cs222 {
    int Pass2::main(int argc, char *argv[]) {
        try
        {
            if (argc < 2)
            {
                std::cout << "USAGE: Pass2 <file>" << std::endl;
                return 0;
            }

        }
        catch(const std::exception& ex)
        {
            std::cout << ex.what() << std::endl;
        }

        return 0;
    }

    std::string Pass2::translate(Instruction instruction) {
        //TODO: Anwar
    }

    void Pass2::readSymbols() {
        //TODO: Mahmoud/Shams
    }

    void Pass2::writeObjectProgram() {
        //TODO: Mahmoud/Shams
    }
}
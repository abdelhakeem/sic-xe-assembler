#include <iostream>
#include <unordered_map>
#include <cs222/Instruction.h>

#include <cs222/Pass2.h>

/*
int main(int argc, char *argv[]) {
    try
    {
        if (argc < 2)
        {
            std::cout << "USAGE: Pass2 <file>" << std::endl;
            return 0;
        }
        cs222::Pass2 assemblerPass2;
        std::cout << assemblerPass2.run(argv[1]) << std::endl;
    }
    catch(const std::exception& ex)
    {
        std::cout << ex.what() << std::endl;
    }

    return 0;
}
*/

namespace cs222 {

    std::string Pass2::run(std::string srcFileName) {
        //TODO: H
        Pass2::srcFileName = srcFileName;
        readSymbols();

        //TODO: Parse instructions and translate each.

        if (Pass2::errorReportMessage != "") {
            writeObjectProgram();
            return "Pass 2 finished successfully";
        } else {
            //TODO: Produce error report.
            return errorReportMessage;
        }
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

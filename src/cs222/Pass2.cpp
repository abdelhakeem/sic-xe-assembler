#include <iostream>
#include <unordered_map>
#include <cs222/Instruction.h>
#include <include/cs222/Instruction.h>
#include <fstream>
#include <sstream>

#include <cs222/Pass2.h>
#include <include/cs222/Utility.h>

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
        readSymbols("example.asm.symtab","example.asm.littab");

        //TODO: Parse instructions and translate each.

        if (Pass2::errorReportMessage != "") {
            writeObjectProgram("name.objprog");
            return "Pass 2 finished successfully";
        } else {
            //TODO: Produce error report.
            return errorReportMessage;
        }
    }

    std::string Pass2::translate(Instruction instruction) {
        //TODO: Anwar
    }

    void Pass2::readSymbols(const std::string& symTabPath,
                            const std::string& litTabPath) {
        //TODO: Mahmoud/Shams

        // reading from symTab
        std::ifstream ifs(symTabPath);

        if (!ifs)
            throw std::runtime_error(std::string("Cannot open file: ") + symTabPath);

        std::cout << "Reading from symbolTable file: " << symTabPath << std::endl;

        if (ifs.is_open()) {

            std::string key;
            int address;
            std::stringstream buf;

            buf << ifs.rdbuf();

            ifs.close();

            // ignoring SYMBOL & ADDRESS
            buf >> key;
            buf >> key;

            while (buf)
            {
                buf >> key;
                std::cout << key << "\t";

                buf >> std::hex >> address;
                std::cout << std::hex << address << std::endl;

                while (!(cs222::hashtableContains(symTab, key))){

                    symTab[key] = address;

                }
            }
        }

        //reading from litTab

        ifs.open(litTabPath);

        if (!ifs)
            throw std::runtime_error(std::string("Cannot open file: ") + litTabPath);

        std::cout << "Reading from litTable file: " << litTabPath << std::endl;

        if (ifs.is_open()) {

            std::string key;
            int address;
            std::stringstream buf;

            buf << ifs.rdbuf();

            ifs.close();

            // ignoring SYMBOL & ADDRESS
            buf >> key;
            buf >> key;

            while (buf)
            {
                buf >> key;
                std::cout << key << "\t";

                buf >> std::hex >> address;
                std::cout << std::hex << address << std::endl;

                while (!(cs222::hashtableContains(litTab, key))){

                    litTab[key] = address;

                }
            }
        }





    }

    void Pass2::writeObjectProgram(const  std::string& objProgPath) {
        //TODO: Mahmoud/Shams
    }
}

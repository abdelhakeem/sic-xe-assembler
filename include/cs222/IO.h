#ifndef SIC_XE_ASSEMBLER_IO_H
#define SIC_XE_ASSEMBLER_IO_H

#include <iostream>
#include <string>
#include <utility>
#include "Instruction.h"

namespace cs222 {
    class IO {
    public:
        IO(string inputFileName, string outputFileName);

        string readLine();
        void consoleOut(string line);
        void fileOut(string line);
        void printSymbolTable(std::unordered_map<string, string> & symbolTable);

        ~IO();
    private:
        string inputFileName;
        string outputFileName;
    };
}
#endif //SIC_XE_ASSEMBLER_IO_H

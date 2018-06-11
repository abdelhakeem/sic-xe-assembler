#ifndef SIC_XE_ASSEMBLER_PASS2_H
#define SIC_XE_ASSEMBLER_PASS2_H

#include <string>
#include <vector>
#include <bits/unordered_map.h>
#include <climits>
#include <deque>
#include "Instruction.h"

namespace cs222 {
    class Pass2 {
    public:
        std::string run(std::string srcFileName); // Runs the pass and returns a feedback message to console.
    private:
        std::deque<std::size_t> modificationAddresses; // Addresses to generate modification records for.
        std::deque<std::string> objectCode; // LinkedList of object code translations for all instructions in order.
        std::deque<std::size_t> correspondingAddresses;
        std::string errorReportMessage;
        std::string srcFileName;

        std::unordered_map<std::string, int> litTab; // Literal table containing addresses.
        std::unordered_map<std::string, int> symTab; // Symbol table containing addresses.

        int base = INT_MIN; // Initialised by a sentinel value indicating that the base register isn't initialised.

        std::string parseProgramName(std::ifstream& ifs);
        std::string parseProgramLength(std::ifstream& ifs);
        std::string string_to_hex(const std::string &input);   // Convert the string input to its hexa value
        std::string decimalToHex(int dec);
        std::string binaryToHex(std::string binaryValue);
        std::string charToBinStr(char hexValue);
        std::string translateLiteral(Operand &firstOperand);
        std::string calculateDisp(int address, Instruction &instruction, char flags[6]);
        std::string translateExpression(std::string expression, char arithmeticOp);

        std::string translate(Instruction instruction); // Translates one instruction and returns its object code.
        void readSymbols(); // Reads the symbol and literal tables from the files with the name in argv[1].
        void writeObjectProgram(std::string& progName,std::string& progLength); // Writes the object program to the output file.
    };
}

#endif //SIC_XE_ASSEMBLER_PASS2_H

#include <iostream>
#include <string>
#include <unordered_map>
#include <include/cs222/Instruction.h>
#include <include/cs222/Operation.h>
#include "Pass2.h"
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
        //this operations donot have object code
        string theseOperations [9] = {START,END,LTORG,RESW,RESB,USE,ORG,EQU,BASE};
        string mn_Op = instruction.getOperation();
        string operand = instruction.getOperandsToken();
        string objCode;

        for (int i = 0; i < 9; ++i) {
            //check if the two strings are equal
            if (mn_Op.compare(theseOperations[i]) == 0)
            {
                if (mn_Op.compare("BASE") == 0)
                {
                    //search for the operand address in SYMTABLE
                    //get its address and assign it into base register
                    std::unordered_map<std::string,int>::const_iterator got = symTab.find (operand);
                    int address = got->second;
                    base = address;
                }
                return nullptr;
            }
        }


        if (mn_Op.compare("BYTE") == 0)
        {
            //the operand for BYTE is in two formats
            //first one C'EOF' ---> for string
            //second  X'2A3'  ---> for constant integers

            if (instruction.getFirstOperand().HEX_CONSTANT)
            {
                objCode = operand.substr(2, operand.size()-3);
                return  objCode;
            }
            else if (instruction.getFirstOperand().CHAR_CONSTANT)
            {
                return string_to_hex(operand.substr(2, operand.size()-3));
            }
        }


        if (mn_Op.compare("WORD") == 0)
        {
            //the operand for WORD is a constant integer
            string hexValue = Decimal_to_hex(std::stoi(operand));
            //now complete the object code to be in format 000000
            //EX: hexValue = 1E  after insert below it will be 00001E
            hexValue.insert(0, 6-hexValue.size(), '0');
            objCode = hexValue;
            return objCode;
        }

        //check if the instruction is format 1
        if (instruction.getFormat() == instruction::FORMAT_1)
        {
            objCode = instruction.getOpcode();
            return objCode;
        }

        if (instruction.getFormat() == instruction::FORMAT_2)
        {
            objCode = instruction.getOpcode();
            register1 = instruction.getFirstOperand();
            register2 = instruction.getSecondOperand();
            objCode.insert(2, 1,/*register2 number*/);
            objCode.insert(2, 1,/*register1 number*/);
        }

        if (instruction.getFormat() == instruction::FORMAT_3)
        {

        }

        if (instruction.getFormat() == instruction::FORMAT_4)
        {
            short n,i,x,e;
            n = i = e = 1;
            Operand firstOperand = instruction.getFirstOperand();
            if (instruction.FLAG_INDEXED) x = 1;
            if (instruction.FLAG_INDIRECT) i = 0;
            if (instruction.FLAG_IMMEDIATE) n = 0;

            if (instruction.getFirstOperand().SYMBOL)
            {

            }else if (firstOperand.INT_CONSTANT)
            {

            }else if (firstOperand.INT_LITERAL)
            {

            }else if (firstOperand.CHAR_LITERAL)
            {

            }else if (firstOperand.HEX_LITERAL)
            {

            }else if (operand.find('+') != -1      ////for expressions
                     ||operand.find('-') != -1
                     ||operand.find('*') != -1
                     ||operand.find('/') != -1)
            {

            }
        }
    }

    void Pass2::readSymbols() {
        //TODO: Mahmoud/Shams
    }

    void Pass2::writeObjectProgram() {
        //TODO: Mahmoud/Shams
    }

    string Pass2::Decimal_to_hex(int dec)
    {
        int rem;
        string s = "";
        string hexaValue;
        while (dec > 0)   // Do this whilst the quotient is greater than 0.
        {
            rem = dec % 16; // Get the remainder.
            if (rem > 9)
            {
                // Map the character given that the remainder is greater than 9.
                switch (rem)
                {
                    case 10:
                        s = "A" + s;
                        break;
                    case 11:
                        s = "B" + s;
                        break;
                    case 12:
                        s = "C" + s;
                        break;
                    case 13:
                        s = "D" + s;
                        break;
                    case 14:
                        s = "E" + s;
                        break;
                    case 15:
                        s = "F" + s;
                        break;
                }
            }
            else
            {
                s = char(rem + 48) + s; // Converts integer (0-9) to ASCII code.
                // x + 48 is the ASCII code for x digit (if 0 <= x <= 9)
            }
            dec = dec/16;
        }
        if (s == "") // if the number was 0, the string will remain empty
            hexaValue = "0";
        else
            hexaValue = s;

        return hexaValue;
    }

    string Pass2::string_to_hex(const std::string& input)
    {
        static const char* const lut = "0123456789ABCDEF";
        size_t len = input.length();

        string output;
        output.reserve(2 * len);
        for (size_t i = 0; i < len; ++i)
        {
            const unsigned char c = input[i];
            output.push_back(lut[c >> 4]);
            output.push_back(lut[c & 15]);
        }
        return output;
    }
}
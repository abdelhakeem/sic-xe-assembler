#include <iostream>
#include <string>
#include <unordered_map>
#include <bitset>
#include <fstream>
#include <sstream>

#include <cs222/Instruction.h>
#include <cs222/Pass2.h>
#include <cs222/Utility.h>
#include <cs222/IntermediateParser.h>

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
        Pass2::srcFileName = srcFileName;

        readSymbols();

        std::ifstream ifs(srcFileName + ".listing");

        std::string progName = parseProgramName(ifs);

        cs222::IntermediateParser iParser(ifs);
        while (iParser.hasNext()) {
            std::unique_ptr<cs222::Instruction> instruction = iParser.next();
            if (instruction != nullptr) {
                Instruction i = *instruction;
                const size_t iAddress = i.getAddress();
                translate(i);
                correspondingAddresses.push_back(iAddress);
                if (i.isSet(i.FLAG_EXTENDED)) {
                    modificationAddresses.push_back(iAddress);
                }
            }
        }
        std::string progLength = parseProgramLength(ifs);
        writeObjectProgram(progName, progLength);
        if (errorReportMessage != "") {
            return "Pass 2 finished successfully";
        } else {
            return errorReportMessage;
        }
    }

    std::string Pass2::parseProgramName(std::ifstream &ifs) {
        std::string line;
        getline(ifs, line); // Skip first line (column names).
        getline(ifs, line); // Skip the second line (empty line).
        getline(ifs, line);

        // Get program name
        std::stringstream lineStream(line);
        std::string buffer;
        lineStream >> buffer; // Skip line number.
        lineStream >> buffer; // Skip address.

        std::string progName;
        lineStream >> progName;
        return progName;
    }

    std::string Pass2::parseProgramLength(std::ifstream &ifs) {
        std::string line;
        getline(ifs, line);
        std::stringstream lineStream(line);
        std::string buffer;

        lineStream >> buffer; // Skip "PROGRAM"
        lineStream >> buffer; // Skip "LENGTH:"

        std::string progLength;
        lineStream >> progLength;
        return progLength;
    }

    std::string Pass2::translate(Instruction instruction) {
        //TODO: Anwar
        //this operations donot have object code

        static std::string theseOperations [9] = {"START","END","LTORG","RESW","RESB","USE","ORG","EQU","BASE"};
        std::unordered_map<std::string,int>::const_iterator got;
        std::string mn_Op = instruction.getOperation();
        std::string operand = instruction.getOperandsToken();
        std::string objCode;

        for (int i = 0; i < 9; ++i) {
            //check if the two strings are equal
            if (mn_Op.compare(theseOperations[i]) == 0)
            {
                if (mn_Op.compare("BASE") == 0)
                {
                    //search for the operand address in SYMTABLE
                    //get its address and assign it into base register
                    got = symTab.find (operand);
                    int address = got->second;
                    base = address;
                }
            }
        }


        if (mn_Op.compare("BYTE") == 0)
        {
            //the operand for BYTE is in two formats
            //first one C'EOF' ---> for string
            //second  X'2A3'  ---> for constant integers

            if (instruction.getFirstOperand().getType() == instruction.getFirstOperand().HEX_CONSTANT)        //hakeem
            {
                objCode = operand.substr(2, operand.size()-3);
                return  objCode;
            }
            else if (instruction.getFirstOperand().getType() == instruction.getFirstOperand().CHAR_CONSTANT)
            {
                objCode = string_to_hex(operand.substr(2, operand.size()-3));
                return objCode;
            }
        }


        else if (mn_Op.compare("WORD") == 0)
        {
            //the operand for WORD is a constant integer
            std::string hexValue = decimalToHex(std::stoi(operand));
            //now complete the object code to be in format 000000
            //EX: hexValue = 1E  after insert below it will be 00001E
            hexValue.insert(0, 6-hexValue.size(), '0');
            objCode = hexValue;
            return objCode;
        }

        //check if the instruction is format 1
        else if (instruction.getFormat() == Instruction::FORMAT_1)   //hakeem
        {
            objCode = getOpcode(instruction.getOperation());

            return objCode;
        }

        else if (instruction.getFormat() == Instruction::FORMAT_2)
        {
            objCode = getOpcode(instruction.getOperation());
            std::string register1Str = instruction.getFirstOperand().getValue();
            std::string register2Str = instruction.getSecondOperand().getValue();
            objCode.insert(2, 1,REGISTERS.find(register2Str)->second - '0');
            objCode.insert(2, 1,REGISTERS.find(register1Str)->second - '0');
        }

        else if (instruction.getFormat() == Instruction::FORMAT_3)
        {
            char flags[6] = {'1','1','0','0','0','0'};      //n,i,x,b,p,e
            Operand firstOperand = instruction.getFirstOperand();
            if (instruction.FLAG_INDEXED) flags[2] = '1';
            if (instruction.FLAG_INDIRECT) flags[1] = '0';
            if (instruction.FLAG_IMMEDIATE) flags[0] = '0';

            if (instruction.getFirstOperand().SYMBOL)
            {
                int address = symTab.find (operand)->second;
                //calculated by program counter
                objCode = calculateDisp(objCode, address, instruction);
            }
            else if (firstOperand.INT_CONSTANT)
            {
                //no disp will be calculated
                objCode = decimalToHex(std::stoi(firstOperand.getValue()));
                if (objCode.length() > 3) objCode = objCode.substr(objCode.length() - 3,3);
                else if (objCode.length() < 3) objCode.insert(0,3-objCode.size(),'0');
                std::string binaryString = hexaToBinary(getOpcode(instruction.getOperation()));
                binaryString = binaryString.substr(0,6);
                for (int i = 0; i < 6; ++i) {
                    int size = binaryString.size();
                    binaryString.insert(size,1,flags[i]);
                }
                objCode = binaryToHex(binaryString) + objCode;
            }
            else if (firstOperand.INT_LITERAL)
            {
                int address = Pass2::litTab.find (firstOperand.getValue())->second;
                objCode = calculateDisp(objCode, address, instruction);

            }else if (firstOperand.CHAR_LITERAL)
            {
                int address = Pass2::litTab.find (firstOperand.getValue())->second;
                objCode = calculateDisp(objCode, address, instruction);
            }else if (firstOperand.HEX_LITERAL)
            {
                int address = Pass2::litTab.find (firstOperand.getValue())->second;
                objCode = calculateDisp(objCode, address, instruction);
            }else if (operand.find('+') != -1      ////for expressions
                      ||operand.find('-') != -1
                      ||operand.find('*') != -1
                      ||operand.find('/') != -1)
            {

            }
        }

        else if (instruction.getFormat() == instruction.FORMAT_4)
        {
            char flags[6] = {'1','1','0','0','0','1'};      //n,i,x,b,p,e
            Operand firstOperand = instruction.getFirstOperand();
            if (instruction.isSet(instruction.FLAG_INDEXED)) flags[2] = '1';
            if (instruction.isSet(instruction.FLAG_INDIRECT)) flags[1] = '0';
            if (instruction.isSet(instruction.FLAG_IMMEDIATE)) flags[0] = '0';

            if (instruction.getFirstOperand().getType() == Operand::SYMBOL)
            {
                got = symTab.find (operand);
                int address = got->second;
                objCode = decimalToHex(address);
                objCode.insert(0,5-objCode.size(),'0');
            }else if (instruction.getFirstOperand().getType() == Operand::INT_CONSTANT)
            {
                objCode = decimalToHex(std::stoi(firstOperand.getValue()));
                objCode.insert(0,5-objCode.size(),'0');
            }else if (instruction.getFirstOperand().getType() == Operand::INT_LITERAL)
            {
                Operand firstOperand = instruction.getFirstOperand();
                objCode = translateLiteral(objCode, firstOperand);
                objCode.insert(0,5-objCode.size(),'0');
            }else if (instruction.getFirstOperand().getType() == Operand::CHAR_LITERAL)
            {
                Operand firstOperand = instruction.getFirstOperand();
                objCode = translateLiteral(objCode, firstOperand);
                objCode.insert(0,5-objCode.size(),'0');
            }else if (instruction.getFirstOperand().getType() == Operand::HEX_LITERAL)
            {
                Operand firstOperand = instruction.getFirstOperand();
                objCode = translateLiteral(objCode, firstOperand);
                objCode.insert(0,5-objCode.size(),'0');
            }else if (operand.find('+') != -1      //for expressions
                     ||operand.find('-') != -1
                     ||operand.find('*') != -1
                     ||operand.find('/') != -1)
            {
                if (operand.find('+') != -1)
                {
                    objCode = objectCodefor_EXP(objCode, operand, '+');
                }
                else if (operand.find('-') != -1)
                {
                    objCode = objectCodefor_EXP(objCode, operand, '-');
                }
                else if (operand.find('*') != -1)
                {
                    objCode = objectCodefor_EXP(objCode, operand, '*');
                }
                else if (operand.find('/') != -1)
                {
                    objCode = objectCodefor_EXP(objCode, operand, '/');
                }
            }
            std::string binaryString = hexaToBinary(getOpcode(instruction.getOperation()));
            binaryString = binaryString.substr(0,6);
            for (int i = 0; i < 6; ++i) {
                int size = binaryString.size();
                binaryString.insert(size,1,flags[i]);
            }
            objCode = binaryToHex(binaryString) + objCode;
        }
        return objCode;
    }

    void Pass2::readSymbols() {
        // reading from symTab
        std::string symTabPath = srcFileName + ".symtab";
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

                symTab[key] = address;
            }
        }

        //reading from litTab
        std::string litTabPath = srcFileName + ".littab";

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

                litTab[key] = address;
            }
        }

    }

    void Pass2::writeObjectProgram(std::string& progName,std::string& progLength) {
        //TODO: Mahmoud/Shams


        std::string objProgPath = srcFileName + ".objprog";

        std::string headerRecord;
        std::deque<std::string> textRecords;
        std::deque<std::string> modRecords;
        std::string endRecord;

        headerRecord = "H" + progName;
        while(headerRecord.length() < 7)
            headerRecord += " ";

        std::deque<std::string> coAdd; //bta3tna elly hanshta8l 3leha
        for (int i = 0; i < correspondingAddresses.size(); ++i) {

            std::stringstream ss;
            std::string temp = "";
            ss << std::hex << correspondingAddresses[i];
            ss >> temp;
            coAdd.push_back(temp);

            while(coAdd.at(i).length() < 6)
                coAdd.at(i) = "0" + coAdd.at(i);

        }

        headerRecord += coAdd.at(0);

        while(progLength.length() < 6)
            progLength = "0" + progLength;

        headerRecord += progLength; // now header record is done

        // now modification record era nya nya

        for (auto it : modificationAddresses) {

            std::string modRec = "";
            std::stringstream ss;
            ss << std::hex << it + 1;
            ss >> modRec;


            while (modRec.length() < 6)
                modRec = "0" + modRec;

            modRec = "M" + modRec + "05";
            modRecords.push_back(modRec);
        }

        endRecord = "E" + coAdd.at(0);

        for (int i = 0; i < objectCode.size(); ++i) {

            std::string startAdd = coAdd.at(i);
            std::string textRecLength;
            std::string textRec = objectCode.at(i);
            ++i;

            while( (textRec.length() < 60) && (i < objectCode.size()) ){
                if((correspondingAddresses.at(i) - correspondingAddresses.at(i-1)) <= 4){
                    if (objectCode.at(i).length() + textRec.length() <= 60){
                        textRec += objectCode.at(i);
                        ++i;
                    }
                } else {
                    break;
                }
            }

            std::stringstream ss;
            ss << std::hex << textRec.length()/2;
            ss >> textRecLength;

            while (textRecLength.length() < 2){
                textRecLength = "0" + textRecLength;
            }

            textRec = "T" + startAdd + textRecLength + textRec;
            textRecords.push_back(textRec);

            --i;
        }

    }

    std::string Pass2::translateExpression(std::string obCode, std::string expression, char arithmeticOp)  //**********//
    {
        int index = expression.find(arithmeticOp);
        int address1, address2;
        std::string symbol1, symbol2;
        symbol1 = expression.substr(0,index-1);
        symbol2 = expression.substr(index+1,expression.size()-index);
        address1 = Pass2::litTab.find (symbol1)->second;
        address2 = Pass2::litTab.find(symbol2)->second;
        obCode = decimalToHex(address1 - address2);
        obCode.insert(0,5-obCode.size(),'0');
        return obCode;
    }

    std::string Pass2::translateLiteral(std::string obCode, Operand &firstOperand)
    {
        int address = Pass2::litTab.find (firstOperand.getValue())->second;
        obCode = decimalToHex(address);
        return obCode;
    }

    std::string Pass2::calculateDisp(std::string objCode, int address,Instruction &instruction)
    {
        int disp = address - (instruction.getAddress()+3);
        if (disp > 2047 || disp < -2048)
        {
            //use base relative
            if (base != INT_MIN)
            {
                disp = address - (base);
                if (disp < 0 || disp > 4096)
                {
                    errorReportMessage = "Disp is out of range";
                    return nullptr;
                }

            }else
            {
                errorReportMessage = "Base register is empty!!";
                return nullptr;
            }
        }
        objCode = decimalToHex(disp);
        if (objCode.length() > 3) objCode = objCode.substr(objCode.length() - 3,3);
        else if (objCode.length() < 3) objCode.insert(0,3-objCode.size(),'0');
        std::string binaryString = hexaToBinary(getOpcode(instruction.getOperation()));
        binaryString = binaryString.substr(0,6);
        for (int i = 0; i < 6; ++i) {
            int size = binaryString.size();
            binaryString.insert(size,1,flags[i]);
        }
        objCode = binaryToHex(binaryString) + objCode;
        return objCode;
    }

    std::string Pass2::hexaToBinary(std::string hexValue)
    {
        std::string s = hexValue;
        std::stringstream ss;
        ss << std::hex << s;
        unsigned n;
        ss >> n;
        std::bitset<8> b(n);
        s = b.to_string();
        s = s.substr(0,s.size()-2);
        return s;
    }

    std::string Pass2::binaryToHex(std::string binaryValue)
    {

        int result =0 ;
        for(size_t count = 0; count < binaryValue.length() ; ++count)
        {
            result *=2;
            result += binaryValue[count]=='1'? 1 :0;
        }

        std::stringstream ss;
        ss << std::hex  << result;

        std::string hexVal(ss.str());
        return hexVal;
    }

    std::string Pass2::decimalToHex(int dec)
    {
        int rem;
        std::string s = "";
        std::string hexaValue;
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

    std::string Pass2::string_to_hex(const std::string& input)
    {
        static const char* const lut = "0123456789ABCDEF";
        size_t len = input.length();

        std::string output;
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

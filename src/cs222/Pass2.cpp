#include <iostream>
#include <unordered_map>
#include <cs222/Instruction.h>
#include <cs222/Instruction.h>
#include <fstream>
#include <sstream>

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

        if (Pass2::errorReportMessage != "") {
            std::string progLength = parseProgramLength(ifs);
            writeObjectProgram(progName, progLength);
            return "Pass 2 finished successfully";
        } else {
            //TODO: Produce error report.
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
}

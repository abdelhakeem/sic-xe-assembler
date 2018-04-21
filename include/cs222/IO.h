#ifndef SIC_XE_ASSEMBLER_IO_H
#define SIC_XE_ASSEMBLER_IO_H

#include <iostream>
#include <string>


namespace cs222 {
    class IO {
    public:
        IO(std::string inputFileName, std::string outputFileName);

        std::string readLine();
        void consoleOut(std::string line);
        void fileOut(std::string line);

        ~IO();
    private:
        std::string inputFileName;
        std::string outputFileName;
    };
}
#endif //SIC_XE_ASSEMBLER_IO_H

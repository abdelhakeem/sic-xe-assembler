#ifndef CS222_PARSER_H
#define CS222_PARSER_H

#include <istream>
#include <memory>
#include <regex>
#include <sstream>
#include <cs222/Instruction.h>

namespace cs222 {
    class Parser {
        public:
            Parser(std::istream& inputStream);
            bool hasNext() const;
            std::shared_ptr<Instruction> next();
        private:
            std::istream& inputStream;
            size_t lineNumber;
            std::string line;
            std::istringstream isstream;
            std::string token;
            std::bitset<6> flags;
            std::shared_ptr<Instruction> lastInstruction;
            void advanceToken();
            void flushRestToToken();
            void parseLabel(std::string& label) const;
            void parseOperation(
                    const std::string& token,
                    std::string& operation) const;
            bool parseOperands(Operand_pair& operands);
            bool parseMemory(Operand& operand);
            bool parseLocation(
                    const std::string& token,
                    Operand& operand) const;
            bool parseLiteral(Operand& operand) const;
            bool parseConstant(
                    const std::string& token,
                    Operand& operand) const;
            bool parseRegister(
                    const std::string& token,
                    Operand& operand) const;
            bool parseNumber(
                    const std::string& token,
                    Operand& operand) const;
            void throwError(const std::string& error) const;
            static const std::regex label_regex;
            static const std::regex char_const_regex;
            static const std::regex hex_const_regex;
            static const std::regex int_const_regex;
            static const std::vector<std::string> REGISTERS;
            static bool isRegister(const std::string& str);
    };
}

#endif

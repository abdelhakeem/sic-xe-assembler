#ifndef CS222_PARSER_H
#define CS222_PARSER_H

#include <istream>
#include <memory>
#include <regex>
#include <cs222/Instruction.h>

namespace cs222 {
    class Parser {
        public:
            Parser(std::istream& inputStream);
            bool hasNext();
            std::unique_ptr<Instruction> next();
            static const std::regex label_regex;
            static const std::regex int_const_regex;
            static const std::regex char_const_regex;
            static const std::regex hex_const_regex;
            static const std::regex op_regex;
        protected:
            std::istream& inputStream;
            size_t lineNumber;
            std::string line;
            std::bitset<6> flags;
            std::unique_ptr<Instruction> nextInstruction;
            void parseLabel(
                    const std::string& token, std::string& label) const;
            void parseOperation(
                    const std::string& token, std::string& operation);
            bool parseOperands(
                    const std::string& token, Operand_pair& operands);
            bool parseMemory(
                    const std::string& token, Operand& operand);
            bool parseLocation(
                    const std::string& token, Operand& operand) const;
            bool parseLiteral(
                    const std::string& token, Operand& operand) const;
            bool parseConstant(
                    const std::string& token, Operand& operand) const;
            bool parseExpression(const std::string& token) const;
            bool parseTerm(const std::string& token) const;
            bool parseRegister(
                    const std::string& token, Operand& operand) const;
            bool parseNumber(
                    const std::string& token, Operand& operand) const;
            void throwError(const std::string& error) const;
            static void advanceToken(
                    std::stringstream& sstream, std::string& token);
            static void flushRestToToken(
                    std::stringstream& sstream, std::string& token);
    };
}

#endif

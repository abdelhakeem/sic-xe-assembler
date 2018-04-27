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
            bool hasNext() const;
            std::shared_ptr<Instruction> next();
        private:
            std::istream& inputStream;
            std::string line;
            size_t lineNumber;
            std::bitset<6> flags;
            std::shared_ptr<Instruction> lastInstruction;
            void throwError(const std::string& error) const;
            std::string extractLabel() const;
            std::string extractOperation();
            std::pair<Operand, Operand> extractOperands();
            std::string extractComment() const;
            static const std::regex label_regex;
            static const std::regex operation_regex;
            static bool isAllSpaces(const std::string& str);
    };
}

#endif

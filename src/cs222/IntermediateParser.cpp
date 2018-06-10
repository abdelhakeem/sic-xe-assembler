#include <cs222/Utility.h>
#include <cs222/OpTable.h>
#include "cs222/IntermediateParser.h"

namespace cs222 {

    IntermediateParser::IntermediateParser(std::istream& inputStream) :
            Parser(inputStream)
    {
        std::getline(inputStream, line);
    }

    std::unique_ptr<Instruction> IntermediateParser::next() {

        if (nextInstruction) {
            return std::move(nextInstruction);
        }

        if (std::getline(inputStream, line))
        {
            lineNumber += 1;
            flags.reset();

            // Ignore empty lines
            while (
                    std::regex_match(line, std::regex("^\\s*$")) &&
                    std::getline(inputStream, line)
                    );

            // Reached end of stream?
            if (!inputStream)
            {
                return nullptr;
            }

            std::stringstream sstream(line);
            std::string token;

            advanceToken(sstream, token);// Skipping line number.

            advanceToken(sstream, token);// Expecting address.

            if (token[0] == '.') // Comment line?
            {
                return this->next();
            }

            std::size_t address;
            address = std::stoul(token, nullptr, 16);

            advanceToken(sstream, token);

            std::string label;
            std::string operation;
            std::string operandsToken;
            Operand_pair operands;
            std::string comment;

            if (!(
                    isDirective(token) ||
                    isOperation(token) ||
                    isOperation(token.substr(1))))
            {
                parseLabel(token, label);
                advanceToken(sstream, token);
            }

            parseOperation(token, operation);

            if (isOperation(operation))
            {
                Instruction::Format fmt =
                        OpTable.find(operation)->second.getValidFormat();
                if (fmt == Instruction::FORMAT_1 || operation == "RSUB")
                {
                    advanceToken(sstream, token);
                    comment = token;
                    flushRestToToken(sstream, token);
                    comment += token;

                    std::unique_ptr<Instruction> ptr = std::make_unique<Instruction>(
                            lineNumber, line, label, operation,
                            operands.first, operands.second,
                            operandsToken, comment, flags);

                    (*ptr).setAddress(address);

                    return ptr;
                }
            }

            // Corner case: character constants
            // and literals can have spaces
            std::string lookahead;
            size_t lookahead_start = sstream.tellg();
            if (lookahead_start != -1)
            {
                lookahead = line.substr(lookahead_start);
            }
            size_t first_non_space = std::distance(
                    lookahead.begin(),
                    find_if_not(lookahead.begin(), lookahead.end(), isspace));
            lookahead = lookahead.substr(first_non_space);
            std::smatch match;
            if (std::regex_match(
                    lookahead,
                    match,
                    std::regex("^\\=?C'[A-Za-z0-9\\s]+'")))
            {
                token = match[0];
                sstream.seekg(
                        first_non_space + token.length(), std::ios_base::cur);
            }
            else
            {
                advanceToken(sstream, token);
            }

            Operand_pair temp;
            if (parseOperands(token, temp))
            {
                operandsToken = token;
                operands = temp;
                // SIC/XE Simple Addressing
                if (isOperation(operation))
                {
                    Instruction::Format fmt =
                            cs222::OpTable.find(operation)->second.getValidFormat();
                    if (fmt == Instruction::FORMAT_3_4 && !(
                            flags.test(Instruction::FLAG_INDIRECT) ||
                            flags.test(Instruction::FLAG_IMMEDIATE)))
                    {
                        flags.set(Instruction::FLAG_INDIRECT);
                        flags.set(Instruction::FLAG_IMMEDIATE);
                    }
                }
                advanceToken(sstream, token);
            }

            comment = token;
            flushRestToToken(sstream, token);
            comment += token;

            if (operation.compare("end") == 0 || operation.compare("END") == 0) {
                return nullptr;
            } else {
                std::unique_ptr<Instruction> ptr = std::make_unique<Instruction>(
                        lineNumber, line, label, operation,
                        operands.first, operands.second,
                        operandsToken, comment, flags);

                (*ptr).setAddress(address);

                return ptr;
            }
        }

        return nullptr;
    }

}

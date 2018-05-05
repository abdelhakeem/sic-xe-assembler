/*
* Assembler syntax:
* -----------------
* <instruction>: [<label>] <operation> [<operands>] [<comment>]
* <label>: [A-Za-z_][A-Za-z0-9_]*
* <operation>: <directive> | [+]<instruction>
* <operands>: <memory> | <register> | <register>,<register>
*          | <register>,<number>
* <memory>: [@#]<location> | <location>,X | <literal>
*          | <constant> | \*
* <location>: <symbol> | <address>
* <symbol>: <label>
* <address>: <number>
* <literal>: =<constant>
* <constant>: <char-constant> | <hex-constant> | <int-constant>
* <char-constant>: C'[^']+'
* <hex-constant>: X'([A-Fa-f0-9]{2})+'
* <int-constant>: -?[0-9]+
* <register>: A | X | L | PC | SW | B | S | T | F
* <number>: <int-constant>
* <comment>: .*
*/

#include <algorithm>
#include <sstream>
#include <stdexcept>
#include <cs222/OpTable.h>
#include <cs222/Parser.h>
#include <cs222/Utility.h>

namespace cs222 {
    Parser::Parser(std::istream& inputStream) :
        inputStream(inputStream), lineNumber(0)
    {
        if (!inputStream)
        {
            throw std::runtime_error("Parser: malformed input stream");
        }
    }

    bool Parser::hasNext()
    {
        if (nextInstruction) {
            return true;
        }
        nextInstruction = next();
        return nextInstruction != nullptr;
    }

    std::unique_ptr<Instruction> Parser::next()
    {
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

            advanceToken(sstream, token);
            if (token[0] == '.') // Comment line?
            {
                return std::make_unique<Instruction>(lineNumber, line);
            }

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
                    flushRestToToken(sstream, token);
                    comment = token;
                    return std::make_unique<Instruction>(
                            lineNumber, line, label, operation,
                            operands.first, operands.second,
                            operandsToken, comment, flags);
                }
            }

            // Corner case: character constants
            // and literals can have spaces
            std::string lookahead;
            if (sstream)
            {
                lookahead = line.substr(sstream.tellg());
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
                advanceToken(sstream, token);
            }

            comment = token;
            flushRestToToken(sstream, token);
            comment += token;

            return std::make_unique<Instruction>(
                    lineNumber, line, label, operation,
                    operands.first, operands.second,
                    operandsToken, comment, flags);
        }

        return nullptr;
    }

    void Parser::parseLabel(const std::string& token, std::string& label) const
    {
        if (std::regex_match(token, label_regex))
        {
            label = token;
        }
        else
        {
            throwError(std::string("illegal symbol name: ") + token);
        }
    }

    void Parser::parseOperation(
            const std::string& token, std::string& operation)
    {
        if (isDirective(token) || isOperation(token))
        {
            operation = token;
        }
        else if (token[0] == '+' && isOperation(token.substr(1)))
        {
            operation = token;
            flags.set(Instruction::FLAG_EXTENDED);
        }
        else
        {
            throwError(std::string("not a valid directive or operation: ") + token);
        }
    }

    bool Parser::parseOperands(
            const std::string& token, Operand_pair& operands)
    {
        if (parseRegister(token, operands.first))
        {
            return true;
        }

        size_t commaPosition = token.find(',');
        if (commaPosition != std::string::npos)
        {
            std::string firstOperand = token.substr(0, commaPosition);
            std::string secondOperand = token.substr(commaPosition + 1);

            if (parseRegister(firstOperand, operands.first))
            {
                if (
                        parseRegister(secondOperand, operands.second) ||
                        parseNumber(secondOperand, operands.second))
                {
                    return true;
                }
            }
        }

        if (parseMemory(token, operands.first))
        {
            return true;
        }

        return false;
    }

    bool Parser::parseMemory(const std::string& token, Operand& operand)
    {
        if (parseLocation(token, operand))
        {
            return true;
        }

        const char prefix = token[0];
        if (prefix == '@' || prefix == '#')
        {
            if (!parseLocation(token.substr(1), operand))
            {
                return false;
            }
            switch (prefix)
            {
                case '@':
                    flags.set(Instruction::FLAG_INDIRECT);
                    break;
                case '#':
                    flags.set(Instruction::FLAG_IMMEDIATE);
                    break;
            }
            return true;
        }

        size_t commaPosition = token.find(',');
        if (commaPosition != std::string::npos)
        {
            std::string location = token.substr(0, commaPosition);
            std::string indexedX = token.substr(commaPosition + 1);
            if (parseLocation(location, operand) && indexedX == "X")
            {
                flags.set(Instruction::FLAG_INDEXED);
                return true;
            }
        }

        if (parseLiteral(token, operand) || parseConstant(token, operand))
        {
            return true;
        }

        if (token == "*")
        {
            operand = Operand(Operand::LOCCTR);
            return true;
        }

        return false;
    }

    bool Parser::parseLocation(const std::string& token, Operand& operand) const
    {
        if (std::regex_match(token, label_regex))
        {
            operand = Operand(Operand::SYMBOL, token);
            return true;
        }
        if (std::regex_match(token, int_const_regex))
        {
            operand = Operand(Operand::INT_CONSTANT, token);
            return true;
        }

        return false;
    }

    bool Parser::parseLiteral(const std::string& token, Operand& operand) const
    {
        if (token[0] == '=')
        {
            if (parseConstant(token.substr(1), operand))
            {
                Operand::Type type = Operand::CHAR_LITERAL;
                if (operand.getType() == Operand::HEX_CONSTANT)
                {
                    type = Operand::HEX_LITERAL;
                }
                else if (operand.getType() == Operand::INT_CONSTANT)
                {
                    type = Operand::INT_LITERAL;
                }
                operand = Operand(type, operand.getValue());
                return true;
            }
        }

        return false;
    }

    bool Parser::parseConstant(const std::string& token, Operand& operand) const
    {
        std::smatch match;
        if (std::regex_match(token, match, char_const_regex))
        {
            operand = Operand(Operand::CHAR_CONSTANT, match[1]);
            return true;
        }
        if (std::regex_match(token, match, hex_const_regex))
        {
            operand = Operand(Operand::HEX_CONSTANT, match[1]);
            return true;
        }
        if (std::regex_match(token, match, int_const_regex))
        {
            operand = Operand(Operand::INT_CONSTANT, match[1]);
            return true;
        }
        return false;
    }

    bool Parser::parseRegister(const std::string& token, Operand& operand) const
    {
        if (isRegister(token))
        {
            operand = Operand(Operand::REGISTER, token);
            return true;
        }
        return false;
    }

    bool Parser::parseNumber(const std::string& token, Operand& operand) const
    {
        if (std::regex_match(token, int_const_regex))
        {
            operand = Operand(Operand::INT_CONSTANT, token);
            return true;
        }
        return false;
    }

    void Parser::throwError(const std::string& error) const
    {
        throw std::invalid_argument(std::string("Parser: ") +
                std::to_string(lineNumber) + ": " + error);
    }

    const std::regex Parser::label_regex("^[A-Za-z_][A-Za-z0-9_]*$");
    const std::regex Parser::int_const_regex("^(-?[0-9]+)$");
    const std::regex Parser::char_const_regex("^C'([^']+)'$");
    const std::regex Parser::hex_const_regex("^X'(([A-Fa-f0-9]{2})+)'$");

    void Parser::advanceToken(
            std::stringstream& sstream, std::string& token)
    {
        token = "";
        sstream >> token;
    }

    void Parser::flushRestToToken(
            std::stringstream& sstream, std::string& token)
    {
        token = "";
        getline(sstream, token);
    }
}

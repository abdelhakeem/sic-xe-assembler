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
* <int-constant>: [0-9]+
* <register>: A | X | L | PC | SW | B | S | T | F
* <number>: <int-constant>
* <comment>: .*
*/

#include <algorithm>
#include <stdexcept>
#include <cs222/OpTable.h>
#include <cs222/Parser.h>

namespace cs222 {
    Parser::Parser(std::istream& inputStream) :
        inputStream(inputStream), lineNumber(0)
    {
        if (!inputStream.good())
        {
            throw std::runtime_error("Parser: malformed input stream");
        }
    }

    bool Parser::hasNext() const
    {
        return inputStream.good();
    }

    std::shared_ptr<Instruction> Parser::next()
    {
        if (inputStream.good())
        {
            flags.reset();
            std::getline(inputStream, line);
            while (std::regex_match(line, std::regex("^\\s*$"))) // Empty line?
            {
                std::getline(inputStream, line);
            }
            isstream.str(line);
            isstream.clear();
            lineNumber += 1;

            advanceToken();
            if (token[0] == '.') // Comment line?
            {
                lastInstruction.reset(new Instruction(lineNumber, line));
            }
            else
            {
                std::string label;
                std::string operation;
                std::pair<Operand, Operand> operands;
                std::string comment;

                if (!(
                            isDirective(token) ||
                            isOperation(token) ||
                            isOperation(token.substr(1))))
                {
                    parseLabel(label);
                    advanceToken();
                }

                if (token[0] == '+')
                {
                    flags.set(Instruction::FLAG_EXTENDED);
                    parseOperation(token.substr(1), operation);
                }
                else
                {
                    parseOperation(token, operation);
                }

                // Corner case: character constants
                // and literals can have spaces
                std::string lookahead = line.substr(isstream.tellg());
                size_t first_non_space = 0;
                while (
                        first_non_space < lookahead.length() &&
                        isspace(lookahead[first_non_space]))
                {
                    first_non_space += 1;
                }
                lookahead = lookahead.substr(first_non_space);
                std::smatch match;
                if (std::regex_match(
                            lookahead,
                            match,
                            std::regex("^\\=?C'[A-Za-z0-9\\s]+'")))
                {
                    token = match[0];
                    isstream.seekg(
                            first_non_space + token.length(),
                            std::ios_base::cur);
                }
                else
                {
                    advanceToken();
                }

                Operand_pair temp;
                if (parseOperands(temp))
                {
                    operands = temp;
                    advanceToken();
                }

                comment = token;
                flushRestToToken();
                comment += token;

                lastInstruction.reset(new Instruction(
                            lineNumber, line, label, operation,
                            operands.first, operands.second,
                            comment, flags));
            }
        }

        return lastInstruction;
    }

    void Parser::advanceToken()
    {
        if (!(isstream >> token))
        {
            token = "";
        }
    }

    void Parser::flushRestToToken()
    {
        if (!getline(isstream, token))
        {
            token = "";
        }
    }

    void Parser::parseLabel(std::string& label) const
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
            const std::string& token,
            std::string& operation) const
    {
        if (isDirective(token) || isOperation(token))
        {
            operation = token;
        }
        else
        {
            throwError(std::string("not a valid directive or operation: ") + token);
        }
    }

    bool Parser::parseOperands(std::pair<Operand, Operand>& operands)
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

        if (parseMemory(operands.first))
        {
            return true;
        }

        return false;
    }

    bool Parser::parseMemory(Operand& operand)
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

        if (parseLiteral(operand) || parseConstant(token, operand))
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

    bool Parser::parseLiteral(Operand& operand) const
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

    bool Parser::parseConstant(
            const std::string& token,
            Operand& operand) const
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

    bool Parser::parseRegister(
            const std::string& token,
            Operand& operand) const
    {
        if (isRegister(token))
        {
            operand = Operand(Operand::REGISTER, token);
            return true;
        }
        return false;
    }

    bool Parser::parseNumber(
            const std::string& token,
            Operand& operand) const
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
    const std::regex Parser::char_const_regex("^C'([^']+)'$");
    const std::regex Parser::hex_const_regex("^X'(([A-Fa-f0-9]{2})+)'$");
    const std::regex Parser::int_const_regex("^([0-9]+)$");

    const std::vector<std::string> Parser::REGISTERS {
        "A", "B", "F", "L", "PC", "S", "SW", "T", "X"
    };

    bool Parser::isOperation(const std::string& str)
    {
        return OpTable.find(toUpper(str)) != OpTable.end();
    }

    bool Parser::isDirective(const std::string& str)
    {
        return std::binary_search(
                DIRECTIVES.begin(),
                DIRECTIVES.end(),
                toUpper(str));
    }

    bool Parser::isRegister(const std::string& str)
    {
        return std::binary_search(
                REGISTERS.begin(),
                REGISTERS.end(),
                toUpper(str));
    }

    std::string Parser::toUpper(const std::string& str)
    {
        std::string upper(str);
        std::transform(str.begin(), str.end(), upper.begin(), toupper);
        return upper;
    }
}

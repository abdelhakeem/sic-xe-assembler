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
            lineNumber += 1;

            // TODO parse comment lines
            const std::string label = extractLabel();
            const std::string operation = extractOperation();
            const std::pair<Operand, Operand> operands = extractOperands();
            const std::string comment = extractComment();

            lastInstruction.reset(new Instruction(
                        lineNumber, label, operation, operands.first,
                        operands.second, comment, flags));
        }

        return lastInstruction;
    }

    void Parser::throwError(const std::string& error) const
    {
        throw std::invalid_argument(std::string("Parser: ") +
                std::to_string(lineNumber) + ": " + error);
    }

    std::string Parser::extractLabel() const
    {
        constexpr auto LABEL_BEGIN = 0;
        constexpr auto LABEL_END = 8;
        constexpr auto LABEL_LENGTH = LABEL_END - LABEL_BEGIN;

        std::string label = line.substr(LABEL_BEGIN, LABEL_LENGTH);
        if (label.length() != LABEL_LENGTH)
        {
            throwError(std::string("expected ") +
                    std::to_string(LABEL_LENGTH) +
                    " characters for the label");
        }

        if (isAllSpaces(label))
        {
            return "";
        }

        std::smatch match;
        if (!std::regex_match(label, match, label_regex))
        {
            throwError("illegal symbol name: " + label);
        }

        return match[1];
    }

    std::string Parser::extractOperation()
    {
        constexpr auto OPERATION_BEGIN = 9;
        constexpr auto OPERATION_END = 15;
        constexpr auto OPERATION_LENGTH = OPERATION_END - OPERATION_BEGIN;

        if (!isspace(line[OPERATION_BEGIN-1]))
        {
            throwError("expected whitespace before operation");
        }

        std::string operation = line.substr(OPERATION_BEGIN, OPERATION_LENGTH);
        if (operation.length() != OPERATION_LENGTH)
        {
            throwError(std::string("expected ") +
                    std::to_string(OPERATION_LENGTH) +
                    " characters for the operation");
        }

        std::smatch match;
        if (!std::regex_match(operation, match, operation_regex))
        {
            throwError("illegal operation name: " + operation);
        }

        std::string prefix = match[1];
        operation = match[2];

        if (!(isOperation(operation) || isDirective(operation)))
        {
            throwError("invalid operation: " + operation);
        }

        if (prefix == "+")
        {
            flags.set(Instruction::FLAG_EXTENDED);
        }
        else if (!prefix.empty())
        {
            throwError("invalid operation prefix: " + prefix);
        }

        return operation;
    }

    std::pair<Operand, Operand> Parser::extractOperands()
    {
        // TODO implement function
        return std::pair<Operand, Operand>();
    }

    std::string Parser::extractComment() const
    {
        constexpr auto COMMENT_BEGIN = 35;
        constexpr auto COMMENT_END = 66;
        constexpr auto COMMENT_MAX = COMMENT_END - COMMENT_BEGIN;

        if (line.length() <= COMMENT_BEGIN)
        {
            return "";
        }

        std::string comment = line.substr(COMMENT_BEGIN);
        if (comment.length() > COMMENT_MAX)
        {
            throwError(std::string("expected no more than ") +
                    std::to_string(COMMENT_MAX) +
                    " characters for the comment");
        }

        return comment;
    }

    const std::regex Parser::label_regex("^([A-Za-z][A-Za-z0-9]*)\\s*$");

    const std::regex Parser::operation_regex(
            "^(\\+?)([A-Za-z]+)\\s*$");

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

    std::string Parser::toUpper(const std::string& str)
    {
        std::string upper(str);
        std::transform(str.begin(), str.end(), upper.begin(), toupper);
        return upper;
    }

    bool Parser::isAllSpaces(const std::string& str)
    {
        return std::all_of(str.begin(), str.end(), isspace);
    }
}

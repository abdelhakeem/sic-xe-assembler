/*
 * Parser test: a simple REPL shell for the parser
 */
#include <iostream>
#include <cs222/Parser.h>

int main()
{
    try
    {
        const std::string OPERAND_TYPE[] {
            "NONE",
            "SYMBOL",
            "ADDRESS",
            "CHAR_LITERAL",
            "HEX_LITERAL",
            "CHAR_CONSTANT",
            "HEX_CONSTANT",
            "REGISTER",
            "NUMBER",
            "LOCCTR"
        };

        std::cout << "Parser Test (enter an empty line to exit)" << std::endl;
        std::cout << "-----------------------------------------" << std::endl;

        std::string line;
        std::istringstream isstream;
        cs222::Parser parser(isstream);
        std::shared_ptr<cs222::Instruction> current;
        while (getline(std::cin, line) && !line.empty())
        {
            isstream.str(line);
            isstream.clear();
            current = parser.next();
            std::cout << "Line: " << current->getLineNumber() << std::endl;
            std::cout << "Label: " << current->getLabel() << std::endl;
            std::cout << "Operation: " << current->getOperation()
                << std::endl;
            cs222::Operand firstOp = current->getFirstOperand();
            cs222::Operand secondOp = current->getSecondOperand();
            std::cout << "First Operand: " << OPERAND_TYPE[firstOp.getType()]
                << ": \"" << firstOp.getValue() << "\"" << std::endl;
            std::cout << "Second Operand: " << OPERAND_TYPE[secondOp.getType()]
                << ": \"" << secondOp.getValue() << "\"" << std::endl;
            std::cout << "Comment: " << current->getComment() << std::endl;
            std::cout << "Flags: " << current->getFlags() << std::endl;
            std::cout << "-----------------------------------------" << std::endl;
        }
    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }

    return 0;
}

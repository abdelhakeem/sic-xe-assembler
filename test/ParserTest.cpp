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
            "INT_LITERAL",
            "CHAR_LITERAL",
            "HEX_LITERAL",
            "INT_CONSTANT",
            "CHAR_CONSTANT",
            "HEX_CONSTANT",
            "EXPRESSION",
            "REGISTER",
            "LOCCTR"
        };

        std::cout << "Parser Test (enter an empty line to exit)" << std::endl;
        std::cout << "-----------------------------------------" << std::endl;

        std::string line;
        std::istringstream isstream;
        cs222::Parser parser(isstream);
        std::unique_ptr<cs222::Instruction> current;
        while (getline(std::cin, line) && !line.empty())
        {
            isstream.str(line);
            isstream.clear();
            current = parser.next();
            std::cout << "[" << current->getLineNumber() << "] "
                << current->getLine() << std::endl;
            std::cout << "Label: " << current->getLabel() << std::endl;
            std::cout << "Operation: " << current->getOperation()
                << std::endl;
            cs222::Operand firstOp = current->getFirstOperand();
            cs222::Operand secondOp = current->getSecondOperand();
            std::cout << "First Operand: " << firstOp.getValue() << " ("
                << OPERAND_TYPE[firstOp.getType()] << ")" << std::endl;
            std::cout << "Second Operand: " << secondOp.getValue() << " ("
                << OPERAND_TYPE[secondOp.getType()] << ")" << std::endl;
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

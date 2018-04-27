/*
 * Parser test: a simple REPL shell for the parser
 */
#include <iostream>
#include <cs222/Parser.h>

int main()
{
    try
    {
        cs222::Parser parser(std::cin);
        std::shared_ptr<cs222::Instruction> current;
        while (parser.hasNext())
        {
            current = parser.next();
            std::cout << "Line: " << current->getLineNumber() << std::endl;
            std::cout << "Label: " << current->getLabel() << std::endl;
            std::cout << "Operation: " << current->getOperation()
                << std::endl;
            std::cout << "Comment: " << current->getComment() << std::endl;
            std::cout << "Flags: " << current->getFlags() << std::endl;
            std::cout << std::endl;
        }
    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }

    return 0;
}

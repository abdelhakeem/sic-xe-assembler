#include <Parser.h>

namespace cs222 {
    Parser::Parser(std::istream& inputStream) : inputStream(inputStream) { }

    bool Parser::hasNext() const
    {
        return !endOfFile;
    }

    Statement Parser::next()
    {
        // TODO parse next line from inputStream,
        // set lastStatement, and return the object
    }
}

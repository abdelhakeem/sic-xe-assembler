#ifndef CS222_PARSER_H
#define CS222_PARSER_H

#include <istream>
#include <memory>
#include <Statement.h>

namespace cs222 {
    class Parser {
        public:
            Parser(std::istream& inputStream);
            bool hasNext() const;
            Statement next();
        private:
            std::istream& inputStream;
            bool endOfFile;
            std::unique_ptr<Statement> lastStatement;
    };
}

#endif

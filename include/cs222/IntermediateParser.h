//
// Parser for the intermediate file produced by pass 1 for analysis in pass 2.
//

#ifndef SIC_XE_ASSEMBLER_INTERMEDIATEPARSER_H
#define SIC_XE_ASSEMBLER_INTERMEDIATEPARSER_H

#include "Parser.h"

namespace cs222 {
    class IntermediateParser : Parser {
    public:
        IntermediateParser(std::istream& inputStream);
        std::unique_ptr<Instruction> next();
    };
}

#endif //SIC_XE_ASSEMBLER_INTERMEDIATEPARSER_H

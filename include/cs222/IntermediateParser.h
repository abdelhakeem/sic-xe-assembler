//
// Parser for the intermediate file produced by pass 1 for analysis in pass 2.
//

#ifndef SIC_XE_ASSEMBLER_INTERMEDIATEPARSER_H
#define SIC_XE_ASSEMBLER_INTERMEDIATEPARSER_H

#include <cs222/Parser.h>

namespace cs222 {
    class IntermediateParser : public Parser {
    public:
        IntermediateParser(std::istream& inputStream); // Stream has head on first instruction.
        std::unique_ptr<Instruction> next() override;
    };
}

#endif //SIC_XE_ASSEMBLER_INTERMEDIATEPARSER_H
